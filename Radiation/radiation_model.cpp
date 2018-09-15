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
#include "functions_radiation.h"

using namespace std;


random_device rd; // obtain a random number from hardware.
mt19937 eng(rd()); // seed the generator.


double uniform(void);

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
        cout << "Bus Cost Matrix Read "<<endl;
    }
    
    if(cost == 1)
    {
        read_brt_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "BRT Cost Matrix Read "<<endl;
    }
    
    vector <Flow_Data_Class>  flow;
    read_flow_data(flow);

    cout << flow.size() << endl;

    double  alpha =  0.01;
    double Imax =  0 ,amax=0; 

    for(int i = 0; i < zone.size() ; i ++ )
    {   
        zone[i].rank_function();
        zone[i].ordered_neighbours();
        zone[i].calculate_flows_radiation(zone, i);
    }
    double I = Soersen_Index(zone,flow);
    cout <<"Soersen : " <<  I << endl;  
    


    for(int i = 0 ; i< zone.size() ; i++){
    int f = 0 ;
    for(int k = 0; k < zone.size() ; k ++ )
    {
        f += zone[i].bus_flow[k] ;
    }
    //cout << (f - zone[i].pop)/zone[i].pop <<  endl;
    }

    ofstream fI;
    if(cost == 0)
    {
        fI.open("../accessibility/accessibility_bus_radiation.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    if(cost == 1)
    {
        fI.open("../accessibility/accessibility_brt_radiation.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    for(int i = 0 ; i < zone.size() ; i ++)
    {
        zone[i].calculate_indicators(zone);
        fI<<i<<"\t"<<zone[i].Acc_1<<"\t"<<zone[i].Acc_2<<"\t"<<zone[i].Acc_3<<endl;
    }
    return 0;
}
