  #include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


class Zone_Class
{
    
    public:
        // Indicators //
        double  Acc_1 , Acc_2, Acc_3 ;
    
        vector<double> bus_flow ;
        
        vector<double> cost_bus ;
        
        double pop ;
        double emp ;
        
      
        void calculate_flows_single(vector<Zone_Class>&, int , double ,vector <double>  ) ;
    
        void check_constraints(vector<Zone_Class>&,int);
    
        void calculate_indicators(vector <Zone_Class>&);
    
    
};

class Flow_Data_Class
{   
    public:
        int origin; 
        int destination;
        double flow; 
};


void calculate_normalisation_terms_single(vector<Zone_Class>&zone,vector<double>& A, double Beta_bus);

void read_population_employment(vector <Zone_Class> &);

void read_old_cost_matrix(vector <Zone_Class>& );

void histogram(vector<Zone_Class>&, vector<double>&, int , double ) ;

double Likelihood(vector<double>& , vector<double>& ) ;

void read_brt_cost_matrix(vector <Zone_Class>& ) ;

void read_flow_data( vector  <Flow_Data_Class> & );

double Soersen_Index(vector <Zone_Class>& ,vector <Flow_Data_Class> & );

double min(double , double );



