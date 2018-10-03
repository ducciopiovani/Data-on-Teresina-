
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

using namespace :: std ;

int main(int argc, char* argv[])
{
    
    string cost_matrix_path, pop_emp_path ; 
    pop_emp_path     =  "../input_data/population_employment.txt";
    cost_matrix_path =  "../input_data/BRT_travel_times.txt";
    
    vector <Zone_Class> zone ;

    read_population_employment(zone, pop_emp_path) ;
    read_cost_matrix(zone, cost_matrix_path) ; 

 
    double Beta_double = atof(argv[1]); // 0.065
    double Beta_single = atof(argv[2]); // 0.045
    
    // Normalizaton terms for the Gravity Models 
    vector <double>  Adouble(zone.size(),1) ;
    vector <double>  Asingle(zone.size(),1) ;
    vector <double>  Bdouble(zone.size(),1) ;

    gravity_double_constrained_normalisation_terms(zone , Adouble, Bdouble, Beta_double) ; // Normalisation terms Double Constrained //
    gravity_single_constrained_normalisation_terms(zone , Asingle, Beta_single) ;
    
    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        
        // Gravity Models 
        zone[i].calculate_flows_gravity_double(zone, i, Beta_double,  Adouble,  Bdouble);
        zone[i].calculate_flows_gravity_single(zone, i, Beta_single,  Asingle);

    }
    

    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        double check_double_out = 0 ; 
        double check_double_in = 0 ; 
        double check_single = 0 ;
        for(int k = 0 ; k  < zone.size() ; k ++ )
        {   
            check_double_out += zone[i].double_gravity_flows[k] ; 
            check_double_in += zone[k].double_gravity_flows[i] ; 
            check_single += zone[i].single_gravity_flows[k] ;
        }
        std::cout << "Zone " << i << std::endl;
        std::cout << "The population is : " << zone[i].pop<<" single out flow : " << check_single<< " double out flow "<< check_double_out<<std::endl ;
        std::cout << "The employment is : " << zone[i].emp <<" double in flow : "<<check_double_in<< std::endl ;   
        std::cout << "\n" << std::endl;

       
    }
    
    



    return 0 ; 
}