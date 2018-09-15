#include "Class.h"



void Zone_Class:: bus_or_car()
{
    // The code is  0 for car and 1 for bus //
    modal_code.resize(cost_tot.size() , 3 );
    
    for(int i = 0 ; i < cost_tot.size() ; i ++)
    {
        int bus = 0 ;
        for(int j = 0 ; j < cost_bus.size() ; j ++)
        {
            if(cost_tot[i] == cost_bus[j])
            {
               bus  = 1 ;
            }
        }
        if(bus==1)
            modal_code[i] = 1;
        else
            modal_code[i] = 0;
    
    }
    return ;
}


void Zone_Class:: cost_tot_dest_code()
{
    for(int i = 0 ; i < cost_tot.size() ; i++)
    {
        for(int j = 0 ; j < cost_bus.size(); j++)
        {
            if( cost_tot[i] == cost_bus[j])
            {
                ord_neigh.push_back(j);
            }
         
            if( cost_tot[i] == cost_car[j])
            {
                ord_neigh.push_back(j);
            }
        }
    }
    
    return ;
}




void Zone_Class:: Set_cost_tot()
{

    // I ADD THE BUS COSTS CHECKING THAT THERE ARE NO
    // DUPLICATES
    for(int i = 0 ; i < cost_bus.size() ; i ++)
    {
        int unique ;
        
        do{
            
            unique= 1;
            for(int k = 0 ; k < cost_tot.size();k++)
            {
                if(cost_bus[i]==cost_tot[k])
                {
                    unique = 0 ;
                    cost_bus[i] += 0.01;
                }
            }
        }while(unique==0);
        
        
        if(cost_bus[i] > 0)
            cost_tot.push_back(cost_bus[i]);
    }
    
    // I ADD THE CAR COSTS CHECKING THAT THERE ARE NO
    // DUPLICATES
    for(int i = 0 ; i < cost_car.size() ; i ++)
    {
       
        int unique;
        do{
            
            unique= 1;
            for(int k = 0 ; k < cost_tot.size();k++)
            {
                if(cost_car[i]==cost_tot[k])
                {
                    unique = 0 ;
                    cost_car[i] += 0.01;
                }
            }
        }while(unique==0);
        if(cost_car[i] > 0)
            cost_tot.push_back(cost_car[i]);
    }
   
    
    // I SORT THE VALUES
    sort(cost_tot.begin(),cost_tot.end());
    
    return ;
}



void Zone_Class:: rank_function()
{
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




void Zone_Class::  ordered_neighbours()
{
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


//
//////////// 4 ////////////
//void Zone_Class ::calculate_flows_extended_tot(int O , vector<Zone_Class>& zone)
//{
//    
//    tot_flow.resize(2*cost_bus.size(),0);
//    
//    int    mi = zone[O].emp;
//    double Ti = zone[O].pop / (1 -  (zone[O].emp*1./ M)) ;
//    
//    
//    for(int k = 0 ; k < zone[O].ord_neigh.size();k++)
//    {
//        int D  = zone[O].ord_neigh[k];
//        int nj = zone[D].emp;
//        
//        long int sij = 0 ;
//        for(int k1 = 0 ; k1  < k ; k1++ )
//        {
//            int middle_zone = zone[O].ord_neigh[k1];
//            sij += zone[middle_zone].emp;
//        }
//        
//        tot_flow[k] = Ti*mi*nj*1. /( (mi + sij) * (mi + nj + sij) ) ;
//    }
//    
//    return ;
//}



////////////  6 ////////////

void Zone_Class :: calculate_flows_extended_tot(vector <Zone_Class>& zone, int O , double alpha)
{
    
    int pi = zone[O].emp;
    double Z = 0;
    
    tot_flow.resize(2*cost_bus.size(),0);
    
    for(int R = 0 ; R < zone[O].cost_tot.size(); R ++)
    {
        // We have to start from 1 to avoid self-flow
        
        int D  = zone[O].ord_neigh[R];
        int ej = zone[D].emp;
        
        long int sij = 0 ;
        for(int k = 0 ; k  < R ; k ++ )
        {
            int middle_zone = zone[O].ord_neigh[k];
            sij += zone[middle_zone].emp;
        }
        
        double aij = sij + pi;
        double num =  ( pow((aij + ej), alpha ) - pow(aij, alpha) )*( pow(pi,alpha) + 1 );
        double den =  ( pow(aij,alpha) + 1 ) * ( pow(aij + ej, alpha) + 1 ) ;
        
        tot_flow[R] = num / den ;
        Z +=  num / den ;
    }
    
    for(int R = 0 ; R < zone[O].cost_tot.size(); R ++)
    {
        tot_flow[R] *= (zone[O].pop/Z);
     //   cout <<tot_flow[R]<<" ";
    }
    //cout << endl;
    
    return ;
}


//
////////////  6 ////////////
//void Zone_Class:: rank_function()
//{
//    
//    rank.resize(cost_bus.size());
//    for(int i = 0; i < cost_bus.size(); i++)
//    {
//        int rnk = 0 ;
//        for(int k = 0 ; k < cost_bus.size() ; k++)
//            if(cost_bus[i] > cost_bus[k])
//                rnk ++;
//        rank[i] =rnk;
//    }
//    return ;
//}
//
//
////////////   7 ////////////
//void Zone_Class::  ordered_neighbours()
//{
//    
//    ord_neigh.resize(cost_bus.size());
//    
//    for(int R = 0 ; R <rank.size() ; R ++)
//    {
//        for(int i = 0 ; i < rank.size() ; i ++ )
//        {
//            if(rank[i] == R)
//            {
//                ord_neigh[R] = i ;
//            }
//        }
//    }
//    return ;
//}
//
////////////  5 ////////////


