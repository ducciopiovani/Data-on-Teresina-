 #include "functions_Double.h"

 


//////////  1 ////////////////

void read_population_employment(vector <Zone_Class>& zone )
{
    ifstream fP("../data/Population_Work.txt");
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


double Soersen_Index(vector <Zone_Class>& zone,vector <Flow_Data_Class> & flow)
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

//////////  3 ////////////////
void calculate_normalisation_terms(vector<Zone_Class>&zone,vector<double>& A, vector<double>& B,double Beta_bus)
{
    
    vector <double>  Aold(zone.size(),1);
    vector <double>  Bold(zone.size(),1);
    double diffb = 0 , diffa = 0 , diff_a_old=0 ,diff_b_old=0 ;
    int cnt  = 0  ;
    do{
        // Loop on the A balancing factor //
        diff_a_old = diffa;
        diffa = 0. ;
        for(int i = 0 ; i < zone.size() ; i ++ )// Loops on all zones
        {
            Aold[i] = A[i]; // Setting old to new
            double  ai =0 ;// Initialize value of dummy variable
            
            for(int  k = 0 ; k < zone.size() ; k ++ )
            //if(i!=k)//Excludes "Self Flow", Comment out the 'if' if needed
            {
                ai += zone[k].emp * B[k] * exp(-Beta_bus * zone[i].cost_bus[k]);
            }
            A[i] = 1./ai ; // Assigning value to A component
            diffa += fabs(A[i]- Aold[i])   ;// calculating difference between successive values.
        }

        // Repeating forLoop on the B balancing factor //
        diff_b_old = diffb; // Storing the old value
        diffb = 0. ;
        for(int i = 0 ; i < zone.size() ; i ++ )
        {
            double bi =0 ;
            Bold[i] = B[i];
            
            for(int  k = 0 ; k < zone.size() ; k ++ )
            //if(i!=k)//Excludes "Self Flow", Comment out the 'if' if needed
            {
                bi += zone[k].pop  * A[k] *exp(-Beta_bus * zone[k].cost_bus[i]);
            }
            B[i] = 1./bi ;
            diffb += fabs(B[i]- Bold[i]);
        }
        cnt ++;
    }while((diffb > 1 || diffa > 1) && cnt < 100 ); 



    return ;
}

//////////  3 ////////////////
void read_old_cost_matrix(vector <Zone_Class>& zone )
{
    ifstream fC("../data/Cost_function.txt") ;
    
    
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].bus_flow.resize(zone.size()) ;
        zone[i].cost_bus.resize(zone.size()) ;
    }
    int label, var1,var2;
    double bus, car, total ;
    
    while(fC>> var1 >> var2 >> car >>bus)
    {
        
        zone[var1-1].cost_bus[var2-1] = bus ;
        zone[var2-1].cost_bus[var1-1] = bus ;
    }
    
    
    return ;
}

//////////  4 ///////////////
void read_brt_cost_matrix(vector <Zone_Class>& zone )
{
    ifstream fC("../data/BRTCost_function.txt") ;
    
    
    for(int i = 0 ; i < zone.size() ; i ++ )
    {
        zone[i].bus_flow.resize(zone.size()) ;
        zone[i].cost_bus.resize(zone.size()) ;    
    }
    
    int    label , var1 ,var2 ;
    double bus, car, total ;
    while(fC>>var1 >> var2 >> car >> bus )
    {
        zone[var1-1].cost_bus[var2-1] = bus;
        zone[var2-1].cost_bus[var1-1] = bus;
        
       
    }
    
    
    return ;
}


//////////  6 ////////////
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



//////////  8 ////////////
void Zone_Class::calculate_flows_double_bus(vector <Zone_Class>& zone, int Origin , double Beta_bus, vector <double> A, vector <double> B)
{
    
    for (int j = 0 ; j < zone.size(); j ++)
    {
        double Tb_ij = A[Origin] * pop * zone[j].emp * B[j] * (exp(-Beta_bus * cost_bus[j])) ;
    
        bus_flow[j] =  Tb_ij;
    }
    return ;
}


//////////  9 ////////////

void Zone_Class :: check_constraints(vector <Zone_Class>& zone, int label)
{
    double cij = 0 ;
    double cji = 0 ;
    int i = label;
    for(int j = 0 ; j < zone.size() ; j ++ )
    {
        cij += bus_flow[j];
        cji += zone[j].bus_flow[i];
    }
        
        
    cout <<cij<<"\t"<< pop<<" \t "<< (cij - pop)/pop  <<endl;
    
    cout <<cji<<"\t"<< emp<<" \t "<< (cji - emp )/emp <<endl ;
    
    cout << "\n\n";
        
    
    
    return ;
}

//////////  10 ////////////

void Zone_Class :: calculate_indicators(vector <Zone_Class>& zone)
{
     
   
    Acc_1 = 0 ; Acc_2 = 0 ; Acc_3 = 0 ;
    
    for(int j = 0 ; j < zone.size() ; j ++ )
        if(cost_bus[j] > 0)
        {
            
            Acc_1  +=  zone[j].emp / cost_bus[j] ;
            
            Acc_2  +=  zone[j].emp / cost_bus[j] ;
            
            Acc_3  +=  bus_flow[j] / cost_bus[j];
        }
    
    Acc_3 /= pop;
    Acc_1 /= pop;
    Acc_2 /= pop;
    
    return ;
}



