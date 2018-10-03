#include "functions_headers_class_defintion.h"



void gravity_double_constrained_normalisation_terms(vector<Zone_Class>& zone , vector<double>& A , vector<double>& B , double Beta )
{
    /*
        In this function the normalization terms of the double constrained gravity model are calculated.
        The flow from origin i to destination j has the form
            
            Tij =  Ai Bi Pi Ej e ^ -(Beta cij) 

        where Pi is the population in im, and Ej is the Employment in j. 
        Here we recursively calculate Ai and Bj, so that sum_i Tij = Pi and sum_j Tij = Ej.
        This means that 

                Ai = sum_j Ej e ^ -(Beta cij)  
                Bj = sum_i Pj e ^ -(Beta cji)

        ATTENTION: The solution might not converge.

        Inputs: 1) zone: vector of class zone instances.
                2) A: vector of doubles to be initialised. 
                3) B: vector of doubles to be initialised
                4) Beta : The Beta parameters value.

        Outputs:  1) A : the vector of the values that assure the constrains. 
                  2) B : the vector of the values that assure the constrains.
    */

    vector <double>  Aold(zone.size(),1);
    vector <double>  Bold(zone.size(),1);

    double diffb = 0 , diffa = 0 , diff_a_old=0 ,diff_b_old=0 ;
    int cnt  = 0  ;
    do{
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
                bi += zone[k].pop  * A[k] *exp(-Beta * zone[k].cost_matrix[i]);
            }
            B[i] = 1./bi ;
            diffb += fabs(B[i]- Bold[i]);
        }
        cnt ++;
       
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
                ai += zone[k].emp * B[k] * exp( -Beta * zone[i].cost_matrix[k]);
            }
            A[i] = 1./ai ; // Assigning value to A component

            diffa += fabs(A[i]- Aold[i])   ;// calculating difference between successive values.
        }

        
    }while( (diffb > 1 || diffa > 1) && cnt < 100 ); 

    return ;
}



void Zone_Class::calculate_flows_gravity_double(vector <Zone_Class>& zone, int Origin , double Beta, vector <double>& A, vector <double>& B)
{
    /*
        Here we calculate the flows with the double constrained gravity model. 
        The equation is :
            
            Tij =  Ai Bi Pi Ej e ^ -(Beta cij) 

        with
            Ai = sum_j Ej e ^ -(Beta cij)  
            Bj = sum_i Pj e ^ -(Beta cji)

        Inputs: 1) zone: vector of class zone instances.
                2) Origin : label of the Origin Zone. 
                3) Beta: parameter for the exponential decay function.
                4) A : vector of the normalization terms. 
                5) B : vector of the normalization terms.

        Outputs:  1) double_gravity_flows : flows from the specified Origin. 
                 
    */
    double_gravity_flows.resize(zone.size());
    for (int j = 0 ; j < zone.size(); j ++)
    {
        double Tb_ij = A[Origin] * pop * zone[j].emp * B[j] * (exp(-Beta * cost_matrix[j])) ;
        double_gravity_flows[j] =  Tb_ij;
    }
    return ;
}


void gravity_single_constrained_normalisation_terms(vector<Zone_Class>& zone , vector<double>& A, double Beta)
{
     /*
        In this function the normalization terms of the single constrained gravity model are calculated.
        The flow from origin i to destination j has the form
            
            Tij =  Ai Pi Ej e ^ -(Beta cij) 

        where Pi is the population in im, and Ej is the Employment in j. 
        Here we calculate the normalieation terms Ai  so that sum_i Tij = Pi.
        This means that 

                Ai = sum_j Ej e ^ -(Beta cij) 

        Inputs: 1) zone: vector of class zone instances.
                2) A: vector of doubles to be initialised. 
                3) Beta : The Beta parameters value.

        Outputs:  1) A : the vector of the values that assure the constrains. 
    */

    // Loop on the A balancing factor //
    for(int i = 0 ; i < zone.size() ; i ++ )// Loops on all zones
    {
        double  ai  = 0; 
        for(int  k = 0 ; k < zone.size() ; k ++ )
        {
            ai += zone[k].emp * exp(- Beta * zone[i].cost_matrix[k]);
        }
        A[i] = 1./ai ; // Assigning value to A component
    }
    return ;
}


void Zone_Class::calculate_flows_gravity_single(vector <Zone_Class>& zone, int Origin , double Beta, vector <double>& A)
{
        /*
        Here we calculate the flows with the double constrained gravity model. 
        The equation is :
            
            Tij =  Ai Pi Ej e ^ -(Beta cij) 
        with:
            Ai = sum_j Ej e ^ -(Beta cij)  
        Inputs:   1) zone: vector of class zone instances.
                  2) Origin : label of the Origin Zone. 
                  3) Beta: parameter for the exponential decay function.
                  4) A : vector of the normalization terms. 

        Outputs:  1) single_gravity_flows : flows from the specified Origin. 
        */

    single_gravity_flows.resize(zone.size()) ;
    for (int j = 0 ; j < zone.size(); j ++)
    {
        double Tb_ij = A[Origin] * pop * zone[j].emp* ( exp(-Beta * cost_matrix[j]) ) ;

        
        single_gravity_flows[j] =  Tb_ij;
    }
    
    return ;
}




