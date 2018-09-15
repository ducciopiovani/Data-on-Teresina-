#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
#include<vector>
#include<list>
#include<stdio.h>
#include<stdlib.h>
#include <map>
#include<algorithm>

#include "functions_Double.h"


using namespace std;

int main()
{
    vector <Zone_Class> zone;
    read_population_employment(zone);

    cout << zone.size()<<endl;
    
    read_old_cost_matrix(zone) ; // Reads the Cost Function //
    cout << "Bus Cost Matrix Read "<<endl;
    
    double cnt_p = 0 , cnt_e = 0;
    

    double bins = 5;
    int Range=100;
    int num_bins = (int) (Range / bins) ;

    
    
    vector <double> Pe ;
    char namePe[250];
    sprintf(namePe,"Pe_car_bus_%0.2f.txt",bins);
    ifstream fPe(namePe);
    double var1 , var2 ;
    while(fPe>>var1>>var2)
    {
        Pe.push_back(var2);
    }
    
  
    double Bco = 0.005 , bc_step = 0.005;
    double Bbo = 0.005, bb_step = 0.005;
    double Bc_max = 0 , Bb_max = 0,  Lmax = -5;
    
    for(int bc = 0 ; bc < 20 ; bc++)
    {
        double Beta_car = Bco + bc*bc_step ;
        cout <<  Beta_car <<endl;
        
        for(int bb = 0 ; bb < 20 ; bb++)
        {
            double Beta_bus = Bbo + bb*bb_step ;
            
            vector <double>  A(zone.size(),1);
            vector <double>  B(zone.size(),1);
            
            calculate_normalisation_terms(zone,A,B,Beta_car,Beta_bus);
           
//            for(int i = 0 ; i < zone.size() ; i ++ )
//            {
//                cout << A[i]<<"\t"<<B[i]<<endl;
//            }
//            
//            
            for(int i = 0 ; i < zone.size() ; i ++ )
            {
                zone[i].calculate_flows_double_bus(zone, i , Beta_bus,A,B);
            }
            
            vector <double> Pm ;
            histogram(zone,  Pm, Range, bins);
            double  L = Likelihood(Pe,Pm);
            cout << "\t"<< Beta_bus<<"\t"<<L<<endl;
            
            if(L > Lmax ){Lmax = L;Bc_max = Beta_car; Bb_max = Beta_bus;}
        }
    }
    
    
    cout <<"MAX : "<< Bc_max<<"\t"<<Bb_max<<"\t"<<Lmax<<endl;

    
    vector <double>  A(zone.size(),1);
    vector <double>  B(zone.size(),1);

    
    calculate_normalisation_terms_bus(zone,A,B,Bc_max,Bb_max);
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].calculate_flows_double_tot(zone, i, Bc_max, Bb_max, A, B);
    }
    

    vector <double> Pm ;
    histogram(zone,  Pm, Range, bins);
    ofstream fP("P_d_double.txt");
    fP <<"time\tP"<<endl;
    for(int i = 0 ; i < Pm.size(); i ++ )
    {
        fP << i*bins <<"\t"<<Pm[i]<<endl;
    }
    fP.close();


    
    
     return 0;
}

