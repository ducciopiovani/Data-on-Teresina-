#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <algorithm>

#include "functions_headers_class_defintion.h"

using namespace :: std;
double min(double a, double b)
{
    if(a < b) return a;
    else return b;
}

int main()
{
    
    string cost_matrix_path, pop_emp_path ; 


    pop_emp_path     =  "../input_data/population_employment.txt" ;
    cost_matrix_path =  "../input_data/OLD_travel_times.txt" ;

    vector <Zone_Class> zone;
    read_population_employment(zone, pop_emp_path ) ;
    read_cost_matrix(zone, cost_matrix_path) ; 


    /* ############ -- Print fraction of  employment per neighbours ########### */
    double emp_tot = 0; // Total Employment // 
    for(int i = 0 ; i < zone.size() ; i ++) // Calculate 
    {   
        int clean ;
        do{
            clean = zone[i].clean_travel_times();
        }while(clean == 0);
        zone[i].rank_function();
        zone[i].ordered_neighbours();
        emp_tot += zone[i].emp ;
    }
    ofstream fO("fraction_of_employmnet.txt");
    for(int i = 0 ; i < zone.size() ; i ++)
    {
        double frac_emp = 0;
        for(int k = 0 ; k < zone.size() ; k ++)
        {   
            int neigh = zone[i].ord_neigh[k];
            frac_emp += zone[neigh].emp /emp_tot ;
            fO <<  frac_emp <<"\t";
        }fO << endl;
    }



    vector <Flow_Data_Class> flow; 
    read_flow_data(flow);
    /* ############# --Calibrate Double Constrained-- ################# */
    double Beta = 0.0001 ;
    double bmax = 0 ;
    double Imax = 0 ;
    ofstream fI("../sorensen_index_data/double_sorensen_index.csv");
    double sorensen_index ; 
    
    for(int b = 0 ; b < 20 ; b ++)
    {   
        Beta = 0.005 + b*0.01;
        vector <double>  A(zone.size(),1);
        vector <double>  B(zone.size(),1);

        gravity_double_constrained_normalisation_terms(zone, A, B, Beta);
        for(int i = 0 ; i < zone.size() ; i ++ )
        {
            zone[i].calculate_flows_gravity_double(zone, i, Beta, A, B);
        }


        double num = 0 ; 
        double den = 0 ; 
        
        for(int i = 0 ; i < flow.size(); i++)
        {
            int o = flow[i].origin;
            int d = flow[i].destination;
            int tod = flow[i].flow;
            num += 2 * min(tod, zone[o].double_gravity_flows[d]);   
            den +=   tod + zone[o].double_gravity_flows[d];
        }
        
        sorensen_index = num / den ;
        fI << Beta << "," << sorensen_index << std::endl;
        
        if(Imax<sorensen_index)
        {   
            Imax = sorensen_index ;
            bmax = Beta ;
        }
    }
    std::cout <<"gravity double constrained calibration. Beta: " << bmax << " Sorensens Index :  " << Imax << std::endl;
    std::cout << "\n\n" << std::endl;
    fI.close();

    /* ############# --Calibrate Single Constrained-- ################# */


    Beta = 0.0001 ;
    bmax = 0 ;
    Imax = 0 ;
    fI.open("sorensen_index_data/single_sorensen_index.csv");
    
    for(int b = 0 ; b < 20 ; b ++)
    {   
        Beta = 0.005 + b*0.01;
        vector <double>  A(zone.size(),1);

        gravity_single_constrained_normalisation_terms(zone ,  A, Beta);
        for(int i = 0 ; i < zone.size() ; i ++ )
        {
            zone[i].calculate_flows_gravity_single(zone, i, Beta,  A);
        }

        double num = 0 ; 
        double den = 0 ; 
        
        for(int i = 0 ; i < flow.size(); i++)
        {
            int o = flow[i].origin;
            int d = flow[i].destination;
            int tod = flow[i].flow;
            num += 2 * min(tod, zone[o].single_gravity_flows[d]);   
            den +=   tod + zone[o].single_gravity_flows[d];
        }
        
        sorensen_index = num / den ;
        fI << Beta << "," << sorensen_index << std::endl;
        
        if(Imax<sorensen_index)
        {   
            Imax = sorensen_index ;
            bmax = Beta ;
        }
    }
    std::cout <<"gravity single constrained calibration. Beta: " << bmax << " Sorensens Index :  " << Imax << std::endl;
    std::cout << "\n\n" << std::endl;
    fI.close();




     /* ############# -- Calibrate Extended Radiation -- ################# */


    fI.open("sorensen_index_data/extended_radiation_sorensen_index.csv");
    Imax = 0 ; 
    double  alpha =  0.0000001, amax=0;
    for(int a = 0 ; a < 37; a++)
    {
        alpha *= 1.5 ; // The steps for the calibration //


        for(int i = 0; i < zone.size() ; i ++ )
        {   
            zone[i].rank_function();
            zone[i].ordered_neighbours();
            zone[i].calculate_flows_extended_radiation(zone, i, alpha);
        }

        double num = 0 ; 
        double den = 0 ; 
        
        for(int i = 0 ; i < flow.size(); i++)
        {
            int o = flow[i].origin;
            int d = flow[i].destination;
            int tod = flow[i].flow;

            num +=   2 * min(tod, zone[o].extended_radiation_flows[d]) ;   
            den +=   tod + zone[o].extended_radiation_flows[d] ;
        }
            
        sorensen_index =  num / den ;
        if(sorensen_index > Imax)
        { 
            Imax = sorensen_index ; 
            amax = alpha;
        }

        fI << alpha << ","<< sorensen_index << endl;   
    }
       
    std::cout <<"extended radiation calibration. alpha : " << amax << " Sorensens Index :  " << Imax << std::endl;
    std::cout << "\n\n" << std::endl;
    fI.close();


    return 0 ; 
}