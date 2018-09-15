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
    double  Beta = 0.0001  ;
    double bmax=0;
    double Imax=0;
    ofstream fI("../SoersenIndexData/Single_Soersen_Index.csv");
    for(int b = 0; b < 20 ; b++)
    {
        double Bb = 0.005 + b*0.01;
        vector <double>  A(zone.size());
        calculate_normalisation_terms_single(zone, A, Bb);
        for(int i = 0 ; i < zone.size() ; i ++ )
        {

            zone[i].calculate_flows_single(zone, i,  Bb, A);
        }

        
        double I = Soersen_Index(zone,flow);

        fI << Bb<<","<<I<<endl;
        cout << Bb<<"  "<<I<<endl;
        if(Imax<I){Imax=I;bmax=Bb;}
    

        
    }
    fI.close();
    cout <<"\n\n y \n\n"<<bmax<<"  "<<Imax<<endl;
   


    return 0;
}

