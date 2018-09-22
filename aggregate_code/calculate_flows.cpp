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

    pop_emp_path     =  "../input_data/Population_Work.txt";
    cost_matrix_path =  "../input_data/Cost_function.txt";

    
    vector <Zone_Class> zone;
    read_population_employment(zone, pop_emp_path ) ;
    read_cost_matrix(zone, cost_matrix_path) ; 


    double Beta_double = 0.026;
    double Beta_single = 0.022; 
    double alpha = 0.00001;
    
    /* Normalizaton terms for the Gravity Models */

    vector <double>  Adouble(zone.size(),1);
    vector <double>  Asingle(zone.size(),1);
    vector <double>  Bdouble(zone.size(),1);

    gravity_double_constrained_normalisation_terms(zone, Adouble, Bdouble, Beta_double); // Normalisation terms Double Constrained //
    gravity_single_constrained_normalisation_terms(zone , Asingle, Beta_single);


    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        
        /* Gravity Models */
        zone[i].calculate_flows_gravity_double(zone, i, Beta_double,  Adouble,  Bdouble);
        zone[i].calculate_flows_gravity_single(zone, i, Beta_double,  Asingle);

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

        for(int k = 0 ; k < zone.size() ; k ++ )
        {   
            zone[i].Adbl  += zone[i].double_gravity_flows[k] / zone[i].cost_matrix[k];
            zone[i].Asgl  += zone[i].single_gravity_flows[k] / zone[i].cost_matrix[k];
            zone[i].Arad  += zone[i].radiation_flows[k] / zone[i].cost_matrix[k];
            zone[i].Aext  += zone[i].extended_radiation_flows[k] / zone[i].cost_matrix[k];
        }

        zone[i].Adbl /= zone[i].pop;
        zone[i].Asgl /= zone[i].pop;
        zone[i].Arad /= zone[i].pop;
        zone[i].Aext /= zone[i].pop;
    }
    
    /* I print the accessibilities on file */

    ofstream  fdbl("accessibilities/accessibility_bus_double.txt") ; 
    ofstream  fsgl("accessibilities/accessibility_bus_single.txt") ;
    ofstream  frad("accessibilities/accessibility_bus_radiation.txt") ;
    ofstream  fext("accessibilities/accessibility_bus_extended.txt") ; 

    fdbl << "Abus" << endl;
    fsgl << "Abus"<< endl;
    frad << "Abus" << endl;
    frad << "Abus"<< endl;
    for(int i = 0 ; i < zone.size() ; i ++ )
    {   
        fdbl << zone[i].Adbl << endl;
        fsgl << zone[i].Asgl << endl;
        frad << zone[i].Arad << endl;
        frad << zone[i].Aext << endl;
    }

    fdbl.close();
    fsgl.close();
    frad.close();
    fext.close();


    return 0;
}

