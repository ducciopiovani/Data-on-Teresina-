
#include "functions_headers_class_defintion.h"



void read_population_employment(vector <Zone_Class>& zone, string file_path )
{   
    
    ifstream fP(file_path);
    int var1, var2 ,label;
    double cnt_p = 0 , cnt_e = 0;
    double prop_cost = 3.55 ;

    string  header;
    std::getline(fP, header) ;
    
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
    string header ;
    std::getline(fC, header) ;
   

    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].cost_matrix.resize(zone.size()) ;
    }
    int label, var1,var2;
    double bus ;

    while(fC>> var1 >> var2 >> bus)
    {
        zone[var1-1].cost_matrix[var2-1] = bus ;
        zone[var2-1].cost_matrix[var1-1] = bus ;
    }
    
    return ;
}

void read_flow_data( vector <Flow_Data_Class> & flow)
{
    ifstream fP("../input_data/trips_from_survey.txt") ;
    double o, d, tod ; 

    string header ;
    std::getline(fP, header) ;
    
    while(fP>>o>>d>>tod)
    {
        Flow_Data_Class f ; 

        f.origin = o; 
        f.destination = d; 
        f.flow = tod;

        flow.push_back(f);
    }
    return;
}