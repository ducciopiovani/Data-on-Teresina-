#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
#include<vector>
#include <map>
#include<algorithm>
#include <random>
#include<stdio.h>
#include<stdlib.h>



#define Njobs 5
#define Commuters 30 // In percentage of population //


#define M 285987 // TOT Employment for normalisation factor //

using namespace std;

class Flow_Data_Class
{   
    public:
        int origin; 
        int destination;
        double flow; 
};



class Zone_Class
{
public:
    
    
    // VARIABLES //
    int pop ;  // population
    int emp ;
    
    // Indicators //
    double Acc_1, Acc_2, Acc_3;

    // VECTORS
    vector<double> cost_bus ;
    vector<double> cost_car ;
    
    
    
    vector<double> tot_flow ;
    vector<double> bus_flow ;
    vector<double> car_flow ;

    
    
    vector <int> ord_neigh ;
    
    
    //FUNCTIONS
    
    void  calculate_indicators(vector <Zone_Class>&);
    void  calculate_flows_radiation(vector <Zone_Class>&, int);
    void  rank_function() ;
    void  ordered_neighbours() ;
    
    vector<int> rank;
    
};


using namespace std;

double uniform(void);

void read_population_employment(vector <Zone_Class>&);

void read_old_cost_matrix(vector <Zone_Class>&) ;

void read_brt_cost_matrix(vector <Zone_Class>&) ;

void histogram(vector<int>&,vector<int>&,int, int );

void read_flow_data( vector  <Flow_Data_Class> & );

double Soersen_Index(vector <Zone_Class>& , vector <Flow_Data_Class> & );

double min(double , double );


