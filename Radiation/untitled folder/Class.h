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



#ifndef __Class
#define __Class

using namespace std;


class Zone_Class
{
    public:
    
    
        // VARIABLES //
        int pop ;  // population
        int emp ;
        double in_flow ;
        double acc_jobs , cost_to_jobs;
    
        // VECTORS
        vector<double> Cbus ;
        vector<double> Ccar ;
    
        vector <double> Ctot ;
        vector <int> ord_neigh ;
        vector <int> modal_code ;
    
    
        //FUNCTIONS
        void Ctot_dest_code();
        void bus_or_car();
        void Set_Ctot();
    
        void setDim(int dim) ;
    
        void  rank_function() ;
        void  ordered_neighbours() ;
    
        vector<int> rank;
    
    
    
};

#endif /* defined(__Class) */

