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
    read_old_cost_matrix(zone) ; // Reads the Cost Function //
    cout << "Bus Cost Matrix Read "<<endl;


    vector <Flow_Data_Class>  flow;
    read_flow_data(flow);

    double  alpha =  0.0000001;
    double Imax =  0 ,amax=0; 
    ofstream fSI("../SoersenIndexData/Extended_Index.csv");
    
    for(int a = 0 ; a < 37; a++)
    {
        alpha *= 1.6 ;
        for(int i = 0; i < zone.size() ; i ++ )
        {   
            zone[i].rank_function();
            zone[i].ordered_neighbours();
            zone[i].calculate_flows_extended(zone, i, alpha);
        }

        double I = Soersen_Index(zone,flow);
        if(I > Imax){ Imax = I ; amax = alpha;}
        cout << alpha << "\t"<< I << endl;
        fSI << alpha << ","<< I << endl;
    }
    cout << "\n\n\n" << endl;
    cout << "alpha = "<<amax << "\t I =" << Imax <<endl;   

    return 0;
}

double uniform(void){
    uniform_real_distribution<> rand(0, 1); // define the range [a,b], extremes included.
    return rand(eng);
}
