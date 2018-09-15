#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

//
//#include <gsl/gsl_sort_float.h>
//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_vector.h>

#define M 285987 // TOT Employment for normalisation factor //

#ifndef __Class
#define __Class

using namespace std;


class Zone_Class
{
    public:
    
    
        // VARIABLES //
        int pop ;  // population
        int emp ;
    
        double Pbus, Pcar;
    
        // VECTORS
        vector<double> cost_bus ;
        vector<double> cost_car ;
        vector <double> cost_tot ;
    
        vector <int> ord_neigh ;
        vector <int> modal_code ;
    
        vector<double> tot_flow ;
        vector<double> bus_flow ;
        vector<double> car_flow ;
    
    
    
        //FUNCTIONS
        void cost_tot_dest_code();
        void bus_or_car();
        void Set_cost_tot();
    
    
        //FUNCTIONS
    
        void  calculate_indicators(vector <Zone_Class>&);
        void  calculate_flows_extended_tot(vector <Zone_Class>&,int,double);
        void  rank_function() ;
        void  ordered_neighbours() ;
    
        vector<int> rank;

};

#endif /* defined(__Class) */

