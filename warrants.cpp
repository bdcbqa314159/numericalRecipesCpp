//
//  warrants.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#include "warrants.h"

double warrant_price_adjusted_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time, const double& m, const double& n){
    
    double time_sqrt = sqrt(time);
    double w = (n/(n+m))*option_price_call_BS(S, K, r, sigma, time);
    double g = w-(n/(m+n))*option_price_implied_vol_call_BS_bissections(S+w*m/n, K, r, sigma, time);
    
    double d1{};
    while(fabs(g)>EPSILON){
        d1 = (log((S+m/n)/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt;
        double gprime = 1-(m/n)*N(d1);
        w = w-g/gprime;
        g = w-(n/(n+m))*option_price_call_BS(S +w*m/n, K, r, sigma, time);
    }
    return w;
}

int testWarrantAdjustedBS(){
    double S = 48;
    double K = 40;
    double r = 0.08;
    double sigma = 0.3;
    double time = 0.5;
    double m = 1000;
    double n = 10000;
    double w = warrant_price_adjusted_BS(S, K, r, sigma, time, m, n);
    
    std::cout<<" warrant price = "<<w<<std::endl;
    return 0;
}

