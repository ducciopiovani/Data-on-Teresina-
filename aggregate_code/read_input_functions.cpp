
#include "functions_headers_class_defintion.h"



void read_population_employment(vector <Zone_Class>& zone, string file_path )
{   
    
    ifstream fP(file_path);
    int var1, var2 ,label;
    double cnt_p = 0 , cnt_e = 0;
    double prop_cost = 3.55 ;


    while(fP>>label>>var1>>var2)
    {
        Zone_Class z ;
        z.pop = var1 / prop_cost; // I take into account the working population //
        z.emp = var2 ;
        
        zone.push_back(z);
    } 
    
    fP.close();
    
    
    return ;
}


void read_cost_matrix(vector <Zone_Class>& zone, string file_path )
{
    
    ifstream fC(file_path) ;
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].cost_matrix.resize(zone.size()) ;
    }
    int label, var1,var2;
    double bus, car, total ;
    
    while(fC>> var1 >> var2 >> car >>bus)
    {
        
        zone[var1-1].cost_matrix[var2-1] = bus ;
        zone[var2-1].cost_matrix[var1-1] = bus ;
    }
    
    
    return ;
}