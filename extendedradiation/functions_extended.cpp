 #include "functions_extended.h"



/////////////// 1 ////////////////////
void read_population_employment(vector <Zone_Class>& zone )


{    ifstream fP("../data/Population_Work.txt");
    int var1, var2 ,label;
    
    while(fP>>label>>var1>>var2)
    {
        
        Zone_Class z ;
        
        z.pop = var1 / 3.55;
        z.emp = var2;
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

void Zone_Class :: calculate_indicators(vector <Zone_Class>& zone)
{

    double tot_bus_flow =0 ;

    Acc_1 = 0 ; Acc_2 = 0 ;  Acc_3 = 0 ;

    for(int j = 0 ; j < zone.size() ; j ++ )
        if(cost_bus[j] > 0)
        {

            Acc_1   +=  zone[j].emp / cost_bus[j]  ;

            Acc_3   +=  bus_flow[j] / cost_bus[j];
        }

    Acc_1 /= pop;
    Acc_3 /= pop;

    return ;
}


//////////  4 ////////////////
void read_brt_cost_matrix(vector <Zone_Class>& zone )
{
    ifstream fC("clean_brt.txt") ;
    
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



/////////////// 5 /////////////////
double Likelihood(vector<double>& Pe, vector<double>& Pm)
{
    
    if(Pe.size() != Pm.size())
    {
        cout << "Different Dimensions "<<endl;
        cout << Pe.size() << "\t"<<Pm.size()<<endl;
    }
    double L =0. ;
    
    for(int x = 0 ; x < Pe.size() ; x ++)
        if(Pm[x]>0){
            L += Pe[x] * log(Pm[x]) ;
            
        }
    
    return L ;
}

void Zone_Class::  ordered_neighbours()
{
    ord_neigh.resize(cost_bus.size(),0);

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

void Zone_Class:: rank_function()
{
    rank.resize(cost_bus.size(),0);

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


////////////  6 ////////////

void Zone_Class :: calculate_flows_extended(vector <Zone_Class>& zone, int O , double alpha)
{
    
    int pi = zone[O].emp;
    double Z = 0;
    
    bus_flow.resize(cost_bus.size(),0);
    
    for(int R = 0 ; R < zone[O].cost_bus.size(); R ++)
    {
        int D  = zone[O].ord_neigh[R];
        int ej = zone[D].emp;
        
        //  We have to start from 1 to avoid self-flow //
        long int sij = 0 ;
        for(int k = 1 ; k  < R ; k ++ )
        {
            int middle_zone = zone[O].ord_neigh[k];
            sij += zone[middle_zone].emp;
        }
        
        double aij = sij + pi;

        double num =  ( pow((aij + ej), alpha ) - pow(aij, alpha) )*( pow(pi,alpha) + 1 );
        double den =  ( pow(aij,alpha) + 1 ) * ( pow(aij + ej, alpha) + 1 ) ;
        
        bus_flow[D] = num / den ;
        Z +=  num / den ;
    
    }
    
    for(int R = 0 ; R < zone[O].cost_bus.size(); R ++)
    {
        bus_flow[R] *= (zone[O].pop/Z);
    }
    
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
    return I ; 

}

double min(double a, double b)
{
    if(a < b) return a;
    else return b;
}




