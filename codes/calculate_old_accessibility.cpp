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


using namespace std;


int main(int argc, char* argv[])
{
    
    string cost_matrix_path, pop_emp_path ; 
    pop_emp_path     =  "../input_data/population_employment.txt";
    cost_matrix_path =  "../input_data/OLD_travel_times.txt";
    
    vector <Zone_Class> zone;
    read_population_employment(zone, pop_emp_path ) ;
    read_cost_matrix(zone, cost_matrix_path) ; 


    double Beta_double = atof(argv[1]); // 0.065
    double Beta_single = atof(argv[2]); // 0.045
    double alpha = atof(argv[3]); // 0.0001
    
    /* Normalizaton terms for the Gravity Models */

    vector <double>  Adouble(zone.size(),1) ;
    vector <double>  Asingle(zone.size(),1) ;
    vector <double>  Bdouble(zone.size(),1) ;

    gravity_double_constrained_normalisation_terms(zone, Adouble, Bdouble, Beta_double) ; // Normalisation terms Double Constrained //
    gravity_single_constrained_normalisation_terms(zone , Asingle, Beta_single) ;


    for(int i = 0 ; i < zone.size() ; i ++ )
    {  
        int clean ;
        do{
            clean = zone[i].clean_travel_times();
        }while(clean == 0);
        
        /* Gravity Models */
        zone[i].calculate_flows_gravity_double(zone, i, Beta_double,  Adouble,  Bdouble);
        zone[i].calculate_flows_gravity_single(zone, i, Beta_single,   Asingle);

        /*Orders the neighboring zones for the radiation models*/
        zone[i].rank_function();
        zone[i].ordered_neighbours();
        
        /*radiation models*/
        zone[i].calculate_flows_radiation(zone, i);
        zone[i].calculate_flows_extended_radiation(zone, i, alpha);

    }

    /* I calculater the Accessibilities using the different models */
    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        
        zone[i].Adbl = 0;
        zone[i].Asgl = 0;
        zone[i].Arad = 0;
        zone[i].Aext = 0;
        zone[i].Atype_2 = 0;
      
        for(int k = 0 ; k < zone.size() ; k ++ )
        if(k != i)
        {   
            zone[i].Adbl  += zone[i].double_gravity_flows[k] / zone[i].cost_matrix[k];
            zone[i].Asgl  += zone[i].single_gravity_flows[k] / zone[i].cost_matrix[k];
            zone[i].Arad  += zone[i].radiation_flows[k] / zone[i].cost_matrix[k];
            zone[i].Aext  += zone[i].extended_radiation_flows[k] / zone[i].cost_matrix[k];
            
            zone[i].Atype_2 += zone[k].emp / zone[i].cost_matrix[k]; // type 2 

        }
        zone[i].Adbl /= zone[i].pop;
        zone[i].Asgl /= zone[i].pop;
        zone[i].Arad /= zone[i].pop;
        zone[i].Aext /= zone[i].pop;

        
        zone[i].Atype_2  /= zone.size() ;
    }

    /* I print the accessibilities on file */
    ofstream  fAcc("../accessibility/accessibility_old.txt") ; 
    fAcc << "Adbl\tAsngl\tArad\tAext\tA2"<< endl;
    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        fAcc << zone[i].Adbl << "\t" <<zone[i].Asgl<< "\t" << zone[i].Arad << "\t" << zone[i].Aext<<"\t"<<zone[i].Atype_2 << endl;
    }
    fAcc.close();
    return 0;
}

