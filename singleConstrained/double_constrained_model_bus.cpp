    #include<iostream>
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

#include "functions_Double.h"


using namespace std;
int main()
{
    
    vector <Zone_Class> zone;
    read_population_employment(zone);
    int cost ;
    cout << "0 for bus cost matrix\n1 for BRT cost matrix "<<endl;
    cin >> cost ;
    
    if(cost == 0)
    {
        read_old_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "Bus Cost Matrix Read "<<endl;
    }
    if(cost == 1)
    {
        read_brt_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "BRT Cost Matrix Read "<<endl;
    }
    

    cout << flow.size() << endl;
    double  Beta = 0.0001  ;
    for(int b = 0 ; b < 20 ; b ++)
    {   
        Beta *= 2;

        vector <double>  A(zone.size(),1);
        vector <double>  B(zone.size(),1);

        calculate_normalisation_terms_bus(zone, A, B, Beta);

        for(int i = 0 ; i < zone.size() ; i ++ )
        {
            zone[i].calculate_flows_double_bus(zone, i, Beta, A, B);
        }
        

        double I = Soersen_Index(zone,flow);
        cout << Beta << "\t"<< I << endl;
        
    }


    
    return 0;
}

