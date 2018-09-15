#include "functions_radiation.h"

//////////  1 ////////////////
void read_population_employment(vector <Zone_Class>& zone )
{
    // I have rewritten the cost function with no=duplicates
    // because the caused problems with the ordering
    
    ifstream fP("../data/Population_Work.txt");
    double var1, var2 ,label;

    double prop_cost = 3.55 ; // Working population
    while(fP>>label>>var1>>var2)
    {
        Zone_Class z ;
        
        z.pop = var1 / prop_cost;
        z.emp = var2 ;
    
        zone.push_back(z);
    }
    fP.close();
    
    return ;
}


//////////  2 ////////////////
void read_old_cost_matrix(vector <Zone_Class>& zone ){
    ifstream fC("clean_bus.txt") ;
    // I have rewritten the cost function with no=duplicates
    // because the caused problems with the ordering
    
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].bus_flow.resize(zone.size()) ;
        zone[i].cost_bus.resize(zone.size()) ;
    }
    
    int label, var1,var2;
    double bus, car, total ;
    while(fC>> var1 >> var2 >>bus)
    {
        zone[var1].cost_bus[var2] = bus ;
        zone[var2].cost_bus[var1] = bus ;
    }
    
    return ;
}

//////////  3 ///////////////
void read_brt_cost_matrix(vector <Zone_Class>& zone )
{
    ifstream fC("clean_brt.txt") ;
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].bus_flow.resize(zone.size()) ;
        zone[i].cost_bus.resize(zone.size()) ;
        
    }
    
    int    label , var1 ,var2 ;
    double bus, car, tostal ;
    
    while(fC>>var1 >> var2 >>bus )
    {
        zone[var1].cost_bus[var2] = bus;
        zone[var2].cost_bus[var1] = bus;
    }
    fC.close();
    return ;
}


////////// 4 ////////////
void Zone_Class:: calculate_flows_radiation( vector<Zone_Class>& zone, int O )
{
    int    mi = zone[O].emp;
    double Ti = zone[O].pop / (1 -  (zone[O].emp*1./ M)) ;
    
    bus_flow[O] = 0 ;
    for(int k = 1 ; k < zone[O].ord_neigh.size();k++)
    {
        int D  = zone[O].ord_neigh[k];
        int nj = zone[D].emp;
        
        long int sij = 0 ;
        for(int k1 = 1 ; k1  < k ; k1++ )
        {
            int middle_zone = zone[O].ord_neigh[k1];
            sij += zone[middle_zone].emp;
        }
        
        if(D!=O)
            bus_flow[D] = Ti*mi*nj*1. /( (mi + sij) * (mi + nj + sij) ) ;
    
    }
    
    return ;
}

//////////  5 ////////////
void Zone_Class :: calculate_indicators(vector <Zone_Class>& zone)
{
    double tot_bus_flow =0;   
    Acc_1 = 0 ; Acc_2 = 0 ;  Acc_3 = 0 ;
    
    for(int j = 0 ; j < zone.size() ; j ++ )
        if(cost_bus[j] > 0)
        {
            
            Acc_1   +=  bus_flow[j]  * zone[j].emp / cost_bus[j]  ;
            
            Acc_2   +=  bus_flow[j] * zone[j].emp ;
            
            Acc_3   +=  bus_flow[j] / cost_bus[j];
            
        }
 
    Acc_1 /= pop;
    Acc_2 /= pop;
    Acc_3 /= pop;
    
    return ;
}

void read_flow_data( vector <Flow_Data_Class> & flow)
{
    ifstream fP("../data/J_Work_bus_Network.txt");
    double o,d,tod ; 
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

double Soersen_Index(vector <Zone_Class>& zone, vector <Flow_Data_Class> & flow)
{

    double I ;
    double num = 0 ; 
    double den = 0 ; 
    for(int i = 0 ; i < flow.size(); i++)
    {
        int o = flow[i].origin;
        int d = flow[i].destination;
        int tod = flow[i].flow;
        
        num += 2 * min(tod, zone[o].bus_flow[d]);   
        den +=   tod + zone[o].bus_flow[d];
    }

    I = num / den ;
    cout << num <<" "<<den<<endl;
    return I ; 

}

double min(double a, double b)
{
    if(a < b) return a;
    else return b;
}

//////////  6 ////////////
void Zone_Class:: rank_function()
{
    
    rank.resize(cost_bus.size());
    for(int i = 0; i < cost_bus.size(); i++)
    {
        int rnk = 0 ;
        for(int k = 0 ; k < cost_bus.size() ; k++)
            if(cost_bus[i] > cost_bus[k])
                rnk ++;
        rank[i] =rnk;
    }
    return ;
}


//////////   7 ////////////
void Zone_Class::  ordered_neighbours()
{
    
    ord_neigh.resize(cost_bus.size());
    
    for(int R = 0 ; R <rank.size() ; R ++)
    {
        for(int i = 0 ; i < rank.size() ; i ++ )
        {
            if(rank[i] == R)
            {
                ord_neigh[R] = i ;
            }
        }
    }
    return ;
}



//////////  8  ////////////
void histogram(vector<Zone_Class>& zone, vector<double> & Pm, int Range, double bins)
{
    int num_bins = (int) (Range / bins) ;
    Pm.resize(num_bins,0);
    double norm = 0 ;
    
    for(int k1 = 0 ; k1 < zone.size() ; k1 ++)
    {
        
        for(int k2 = 0 ; k2 < zone.size() ; k2 ++)
        {
            for(int n = 0 ;n< num_bins ; n ++)
            {
                if(zone[k1].cost_bus[k2] > n * bins && zone[k1].cost_bus[k2] < (n+1)*bins)
                {
                    Pm[n]+= zone[k1].bus_flow[k2];
                    norm += zone[k1].bus_flow[k2];
                }
            }
        }
    }
    
    cout << "Done "<<endl;
    for(int n = 0 ;n< num_bins ; n ++)
    {
        Pm[n] /= norm ;
        
    }
    
    
    
    return ;
}




