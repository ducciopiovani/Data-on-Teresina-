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

    read_old_cost_matrix(zone) ; // Reads the Cost Function //
    cout << "Bus Cost Matrix Read "<<endl;
    
    
    vector <Flow_Data_Class> flow; 
    read_flow_data(flow);

    cout << flow.size() << endl;
    double  Beta = 0.0001  ;
    double bmax=0;
    double Imax=0;
    ofstream fI("../SoersenIndexData/Double_Soersen_Index.csv");
    for(int b = 0 ; b < 20 ; b ++)
    {   
        Beta = 0.005 + b*0.01;

        vector <double>  A(zone.size(),1);
        vector <double>  B(zone.size(),1);

        calculate_normalisation_terms(zone, A, B, Beta);

        for(int i = 0 ; i < zone.size() ; i ++ )
        {
            zone[i].calculate_flows_double_bus(zone, i, Beta, A, B);
        }
        

        double I = Soersen_Index(zone,flow);
        fI<< Beta << ","<< I << endl;
        cout << Beta << " "<< I << endl;
        if(Imax<I){Imax=I;bmax=Beta;}
    }

    cout <<bmax<<"  "<<Imax<<endl;

    
    return 0;
}

