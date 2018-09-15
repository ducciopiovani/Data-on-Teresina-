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
        clean_read_old_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "Bus Cost Matrix Read "<<endl;
    }
    
    if(cost == 1)
    {
        clean_read_brt_cost_matrix(zone) ; // Reads the Cost Function //
        cout << "BRT Cost Matrix Read "<<endl;
    }

    vector <Flow_Data_Class>  flow;
    read_flow_data(flow);

    double  alpha =  0.01;
    double Imax =  0 ,amax=0; 
    for(int a = 0 ; a < 40; a++)
    {
        alpha =  0.01  + a*0.005;
        for(int i = 0; i < zone.size() ; i ++ )
        {   

            zone[i].rank_function();
            zone[i].ordered_neighbours();

            zone[i].calculate_flows_extended(zone, i, alpha);
        }

        double I = Soersen_Index(zone,flow);
        if(I > Imax){ Imax = I ; amax = alpha;}
        cout << alpha << "\t"<< I << endl;
    }
    cout << "\n\n\n" << endl;
    cout << amax << "\t" << Imax <<endl;




    /*
    ofstream fI;
    if(cost == 0)
    {
        fI.open("../accessibility/folder/accessibility_bus_extended.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    
    if(cost == 1)
    {
        fI.open("../accessibility/folder/accessibility_brt_extended.txt");
        fI <<"Label\tA1\tA2\tA3\n"<<endl;
    }
    for(int i = 0 ; i < zone.size() ; i ++)
    {
        zone[i].calculate_indicators(zone);
        fI<<i<<"\t"<<zone[i].Acc_1<<"\t"<<zone[i].Acc_2<<"\t"<<zone[i].Acc_3<<endl;
    }
    */

    return 0;
}

double uniform(void){
    uniform_real_distribution<> rand(0, 1); // define the range [a,b], extremes included.
    return rand(eng);
}
