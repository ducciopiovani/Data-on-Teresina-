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

#include "functions_Single.h"


using namespace std;

int main() 
{

    vector <Zone_Class> zone;
    read_population_employment(zone);
    vector <Flow_Data_Class>  flow;

    read_flow_data(flow);

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
    double  Beta = 0.022  ;
    vector <double>  A(zone.size());
    calculate_normalisation_terms_single(zone, A, Beta);
    
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].calculate_flows_single(zone, i,  Beta, A);
    }

    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].calculate_indicators(zone); 
    }

    
    ofstream fI;
    if(cost == 0)
    {
        fI.open("../accessibility/accessibility_bus_single_0.022.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    
    if(cost == 1)
    {
        fI.open("../accessibility/accessibility_brt_single_0.022.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    
    for(int i = 0 ; i < zone.size() ; i ++)
    {
        zone[i].calculate_indicators(zone);
        fI<<i<<"\t"<<zone[i].Acc_1<<"\t"<<zone[i].Acc_2<<"\t"<<zone[i].Acc_3<<endl;
    }
    fI.close();
    





    return 0;
}

