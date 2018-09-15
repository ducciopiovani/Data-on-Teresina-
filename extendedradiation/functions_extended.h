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
    double Acc_1 , Acc_2 , Acc_3,Pbus ;
    
    vector<double> tot_flow ;
    vector<double> bus_flow ;
    
    vector<double> cost_bus ;
    
    vector<double> ord_neigh ;
    vector<double> rank ;
    
    double pop ;
    double emp ;
    
    void rank_function();
    
    void ordered_neighbours();
    
    void calculate_flows_extended(vector<Zone_Class>&, int, double) ;
    
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


void read_population_employment(vector <Zone_Class> &);

void read_brt_cost_matrix(vector <Zone_Class>&  );

void read_old_cost_matrix(vector <Zone_Class>& );


double Likelihood(vector<double>& , vector<double>& ) ;


void read_flow_data( vector  <Flow_Data_Class> & );

double Soersen_Index(vector <Zone_Class>& ,vector <Flow_Data_Class> & );

double min(double , double );


