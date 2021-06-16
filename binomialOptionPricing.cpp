//
//  binomialOptionPricing.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 16/06/2021.
//

#include "binomialOptionPricing.h"
#include <algorithm>

double option_price_call_euro_bin_single_period(const double& S, const double& X, const double& r, const double& u, const double& d ){
    
    
    double p_up = (exp(r)-d)/(u-d);
    double p_down = 1.0 - p_up;
    
    double c_u = std::max(0.0, u*S-X);
    double c_d = std::max(0.0, d*S-X);
    
    double call_price = exp(-r)*(p_up*c_u + p_down*c_d);
    
    return call_price;
}

std::vector<std::vector<double>> binomial_tree(const double& S0, const double& u, const double& d, const int& no_steps){
    
    std::vector<std::vector <double>> tree;
    
    for(int i = 1; i <= no_steps; ++i){
        std::vector<double> S(i);
        for (int j = 0; j<i; j++){
            S.at(j) = S0*pow(u,j)*pow(d, i-j-1);
        };
        
        tree.push_back(S);
    }
    
    return tree;
}

double option_price_call_euro_bin_multi_period(const double& S, const double& K, const double& r, const double& u, const double& d, const int& no_steps ){
    
    double Rinv = exp(-r);
    double uu = u*u;
    double p_up = (exp(r)-d)/(u-d);
    double p_down = 1.0-p_up;
    
    std::vector<double> prices(no_steps+1);
    prices[0] = S*pow(d, no_steps);
    
    for (int i = 1; i<=no_steps; ++i)
        prices[i] = uu*prices[i-1];
    
    std::vector<double> call_values(no_steps+1);
    
    for (int i = 1; i<=no_steps; ++i)
        call_values[i] = std::max(0.0, prices[i]-K);
    
    for (int step = no_steps -1; step >=0; step --){
        for (int i=0; i<=step; i++){
            call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
        }
    }
    return call_values[0];
}

int testEuroCallBinomialMultiPeriod(){
    
    double S = 100.0;
    double K = 100.0;
    double r = 0.025;
    double u = 1.05;
    double d = 1/u;
    
    std::cout<<" one period european call: "<<std::endl;
    std::cout<<option_price_call_euro_bin_single_period(S, K, r, u, d)<<std::endl;
    
    int no_periods = 2;
    std::cout<<" three period european call: "<<std::endl;
    std::cout<<option_price_call_euro_bin_multi_period(S, K, r, u, d, no_periods)<<std::endl;
    
    
    
    return 0;
}
