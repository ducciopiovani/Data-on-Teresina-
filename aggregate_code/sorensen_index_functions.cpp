#include "functions_headers_class_defintion.h"



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