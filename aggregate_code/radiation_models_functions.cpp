
#include "functions_headers_class_defintion.h"



void Zone_Class:: rank_function()
{
    rank.resize(cost_matrix.size());
    for(int i = 0; i < cost_matrix.size(); i++)
    {
        int rnk = 0 ;
        for(int k = 0 ; k < cost_matrix.size() ; k++)
            if(cost_matrix[i] > cost_matrix[k])
                rnk ++;
        rank[i] =rnk;
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