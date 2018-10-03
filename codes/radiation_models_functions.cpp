
#include "functions_headers_class_defintion.h"



int Zone_Class :: clean_travel_times()
{
    int clean = 1 ;
    for(int k1 =0 ; k1 < cost_matrix.size() ; k1++)
    {
        for(int k2 = k1 +1 ; k2 < cost_matrix.size() ; k2++)
        if(cost_matrix[k1] == cost_matrix[k2])
        {
            cost_matrix[k2] += cost_matrix[k2] / 500;
            clean = 0 ;
        }

    }
  
    return clean ;
}

void Zone_Class:: rank_function()
{
    rank.resize(cost_matrix.size());
    for(int i = 0; i < cost_matrix.size(); i++)
    {
        int rnk = 0 ;
        for(int k = 0 ; k < cost_matrix.size() ; k++)
        {
            if(cost_matrix[i] > cost_matrix[k])
            rnk ++;
        }
        rank[i] = rnk;
    }

    return ;
}


//////////   7 ////////////
void Zone_Class::  ordered_neighbours()
{
    
    ord_neigh.resize(cost_matrix.size());
    
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

void Zone_Class:: calculate_flows_radiation( vector<Zone_Class>& zone, int O )
{
    int    mi = zone[O].emp;
    double Ti = zone[O].pop / (1 -  (zone[O].emp*1./ M)) ;
    
    radiation_flows.resize(zone.size());

    radiation_flows[O] = 0 ;
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
            radiation_flows[D] = Ti*mi*nj*1. /( (mi + sij) * (mi + nj + sij) ) ;
    
    }
    return ;
}


void Zone_Class :: calculate_flows_extended_radiation(vector <Zone_Class>& zone, int O , double alpha)
{

    int pi = zone[O].emp;
    double Z = 0;

    extended_radiation_flows.resize(cost_matrix.size(),0);
    

    for(int R = 0 ; R < zone[O].cost_matrix.size(); R ++)
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
        
        extended_radiation_flows[D] = num / den ;
        Z +=  num / den ;
    
    }
    
    for(int R = 0 ; R < zone[O].cost_matrix.size(); R ++)
    {
        extended_radiation_flows[R] *= (zone[O].pop/Z);
    }
    
    return ;
}
