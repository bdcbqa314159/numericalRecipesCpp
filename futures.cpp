//
//  futures.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 16/06/2021.
//

#include "futures.h"

double futures_price(const double& S, const double& r, const double& time_to_maturity){
    
    
    
    return exp(r*time_to_maturity)*S;
    
}

int testFutures(){
    
    double S = 100;
    double r=0.1;
    double time = 0.5;
    
    std::cout<<"futures price = "<<futures_price(S, r, time)<<std::endl;
    
    return 0;
}
