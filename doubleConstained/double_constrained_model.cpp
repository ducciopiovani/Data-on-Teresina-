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

#include "functions_Double.h"


using namespace std;
int main()
{
    
    vector <Zone_Class> zone;
    read_population_employment(zone);
    int cost ;
    cout << "0 for bus cost matrix\n1 for BRT cost matrix "<<endl;
    cin >> cost ;
    cout << cost << endl;
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
    
    double Beta = 0.026; 
    vector <double>  A(zone.size(),1);
    vector <double>  B(zone.size(),1);

    calculate_normalisation_terms(zone, A, B, Beta);
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].calculate_flows_double_bus(zone, i, Beta, A, B);
        zone[i].calculate_indicators(zone);
    }

    ofstream fI;
    if(cost == 0)
    {   
        fI.open("../accessibility/accessibility_bus_double_0.026.txt");
        //fI.open("accessibility_bus_double.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    
    if(cost == 1)
    {
        fI.open("../accessibility/accessibility_brt_double_0.026.txt");
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

