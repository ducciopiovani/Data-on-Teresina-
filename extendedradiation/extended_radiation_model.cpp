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
#include <random>
#include "functions_extended.h"

using namespace std;



int main()
{
    
    vector <Zone_Class> zone;
    read_population_employment(zone);
    int cost ;
    
    cout <<"I have created "<< zone.size()<<" class instances "<<endl;
    cout << "0 for bus cost matrix\n1 for BRT cost matrix "<<endl;
    cin >> cost ;
    
    if(cost == 0)
    {
        read_old_cost_matrix(zone) ; // Reads the Cost Function //
        cout << zone[0].cost_bus.size() << endl;
        cout << "Bus Cost Matrix Read "<<endl;
    }
    
    if(cost == 1)
    {
        read_brt_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "BRT Cost Matrix Read "<<endl;
    }

   
    double alpha = 0.00001;
    for(int i = 0; i < zone.size() ; i ++ )
    {   
        zone[i].rank_function() ;
        zone[i].ordered_neighbours() ;
        zone[i].calculate_flows_extended(zone, i, alpha);
        zone[i].calculate_indicators(zone); 
        
    }


    ofstream fI;
    if(cost == 0)
    {
        fI.open("../accessibility/accessibility_bus_extended.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    
    if(cost == 1)
    {
        fI.open("../accessibility/accessibility_brt_extended.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    for(int i = 0 ; i < zone.size() ; i ++)
    {
        zone[i].calculate_indicators(zone);
        fI<<i<<"\t"<<zone[i].Acc_1<<"\t"<<zone[i].Acc_2<<"\t"<<zone[i].Acc_3<<endl;
    }
    fI.close();
    

    double tot_emp = 0.;
    for(int k = 0; k < zone.size(); k++ )
    {
        tot_emp += zone[k].emp;
    }

    
    ofstream fE("employment_fraction_distribution.txt");
    for(int i = 0 ; i < zone.size() ; i++)
    {
        double frac_emp = 0.;
        for(int k = 0; k < zone.size(); k++ )
        {
            int neigh = zone[i].ord_neigh[k];
            frac_emp +=  zone[neigh].emp;
            fE <<frac_emp / tot_emp <<"\t"; 
        }
        fE << endl;
    }

    return 0;
}

