
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

using namespace::std;

int main()
{
    
    string cost_matrix_path, pop_emp_path ; 
    pop_emp_path  =  "../input_data/population_employment.txt";
    cost_matrix_path =  "../input_data/BRT_travel_times.txt";
    vector <Zone_Class> zone;
    
    // ###### CHECK READ POPULATION AND EMPLOYMENT  ###### //
    read_population_employment(zone, pop_emp_path) ;
    read_cost_matrix(zone, cost_matrix_path) ; 
    double alpha = 0.00001;

    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        // Orders the neighboring zones for the radiation models
        int clean ;
        do{
            clean = zone[i].clean_travel_times();
        }while(clean == 0);
        zone[i].rank_function();
        zone[i].ordered_neighbours();
     
        // radiation models
        zone[i].calculate_flows_radiation(zone, i);
        zone[i].calculate_flows_extended_radiation(zone, i, alpha);
    }


    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        double check_radiation = 0 ;  
        double check_extended  = 0 ; 
        for(int k = 0 ; k  < zone.size() ; k ++ )
        {   
            check_radiation += zone[i].radiation_flows[k] ;
            check_extended  += zone[i].extended_radiation_flows[k] ; 
        }
        std::cout << "Zone " << i << std::endl;
        std::cout << "The Working Population is : " << zone[i].pop<<" radiation out flow : " << check_radiation<< " extended radiation out flow "<< check_extended<<std::endl ;
        std::cout << "\n" << std::endl;
    }

    return 0 ; 
}

