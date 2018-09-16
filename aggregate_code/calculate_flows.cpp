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


int main()
{
    

    string cost_matrix_path, pop_emp_path ; 

    pop_emp_path = "/Users/duccio/Desktop/Data-on-Teresina-/input_data/Population_Work.txt";
    cost_matrix_path = "/Users/duccio/Desktop/Data-on-Teresina-/input_data/Cost_function.txt";

    
    vector <Zone_Class> zone;
    read_population_employment(zone, pop_emp_path ) ;
    read_cost_matrix(zone, cost_matrix_path) ; 


    double Beta_double = 0.026;
    double Beta_single = 0.022; 
    
    /* Normalizaton terms for the Gravity Models */

    vector <double>  Adouble(zone.size(),1);
    vector <double>  Asingle(zone.size(),1);
    vector <double>  Bdouble(zone.size(),1);

    gravity_double_constrained_normalisation_terms(zone, Adouble, Bdouble, Beta_double); // Normalisation terms Double Constrained //
    calculate_normalisation_terms_single(zone , Asingle, Beta_single);


    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        /*Orders the neighboring zones for the radiation models*/
        zone[i].rank_function();
        zone[i].ordered_neighbours();
        
        /* Gravity Models */
        zone[i].calculate_flows_gravity_double(zone, i, Beta_double,  Adouble,  Bdouble);
        zone[i].calculate_flows_gravity_single(zone, i, Beta_double,  Adouble);
        zone[i].calculate_flows_radiation(zone, i);

    }
    
    

    
    return 0;
}

