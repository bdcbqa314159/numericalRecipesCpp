//
//  basicBlackScholes.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#include "basicBlackScholes.h"

double N(double x){
    
    double gamma = 0.2316419 ;
    double a1 = 0.319381530;
    double a2 = -0.356563782;
    double a3 = 1.781477937;
    double a4 = -1.821255978;
    double a5 = 1.330274429;
    double pi = 3.14159;
    double k = 1.0/(1.0+gamma*x);
    
    if(x >= 0.0){
        
        return 1-((((a5*k+a4)*k+a3)*k+a2)*k+a1)*k*exp(-x*x/2.0)/sqrt(2.0*pi);
    }
    
    else
        return 1.0-N(-x);
}


double n(double x){
    
    double pi = 4.0*atan(1.0);
    
    return exp(-x*x/2)/sqrt(2*pi) ;
    
}

double option_price_call_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time){
    
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K) + r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;
    
    return S*N(d1)-K*exp(-r*time)*N(d2);
    
}

double option_price_put_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time){
    
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K) + r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;
    
    return K*exp(-r*time)*N(-d2) -S*N(-d1);
    
}

void option_price_partials_call_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time, double& Delta, double& Gamma, double& Theta, double& Vega, double& Rho){
    
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K) + r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;
    
    Delta = N(d1);
    Gamma = n(d1)/(S*sigma*time_sqrt);
    Theta = -S*sigma*n(d1)/(2*time_sqrt) - r*K*exp(-r*time)*N(d2);
    Vega = S*time_sqrt*n(d1);
    Rho = K*time*exp(-r*time)*N(d2);

}

int testOptionPriceCallPutPartialsBS(){
    
    double S = 50;
    double K = 50;
    double r = 0.10;
    double sigma = 0.0500427;// 0.30;
    double time = 0.50;
    
    std::cout<<"Black-Scholes call price = "<<std::endl;
    std::cout<<option_price_call_BS(S, K, r, sigma, time)<<std::endl;
    
    std::cout<<"Black-Scholes call put = "<<std::endl;
    std::cout<<option_price_put_BS(S, K, r, sigma, time)<<std::endl;
    
    double Delta{}, Gamma{}, Theta{}, Vega{}, Rho{};
    
    option_price_partials_call_BS(S,K,r,sigma,time,Delta,Gamma,Theta,Vega, Rho);
    
    std::cout<<"Delta = "<<Delta<<std::endl;
    std::cout<<"Gamma = "<<Gamma<<std::endl;
    std::cout<<"Theta = "<<Theta<<std::endl;
    std::cout<<"Vega = "<<Vega<<std::endl;
    std::cout<<"Rho = "<<Rho<<std::endl;
    
    
    return 0;
}

double option_price_implied_vol_call_BS_bissections(const double& S, const double& K, const double& r, const double& time, const double& option_price){
    
    if(option_price<0.99*(S-K*exp(-time*r))) return 0.0;
    
    const double ACCURACY = 1.0e-5;
    const int MAX_ITER = 100;
    const double HIGH_VAL = 1e10;
    const double ERROR = -1e40;
    
    double sigma_low = 1.0e-5;
    double sigma_high = 0.3;
    
    double price = option_price_call_BS(S, K, r, sigma_high, time);
    
    while (price<option_price){
        sigma_high = 2.0*sigma_high;
        price = option_price_call_BS(S, K, r, sigma_high, time);
        if (sigma_high>HIGH_VAL) return ERROR;
    }
    
    double test{};
    double sigma{};
    for (int i = 0; i<MAX_ITER; i++){
        sigma = (sigma_low+sigma_high)*0.5;
        
        price = option_price_call_BS(S, K, r, sigma, time);
        test = price-option_price;
        
        if (fabs(test)<ACCURACY) return sigma;
        if (test<0.0)
            sigma_low = sigma;
        else
            sigma_high = sigma;
    }
    
    return ERROR;
}

double option_price_implied_vol_call_BS_Newton(const double& S, const double& K, const double& r, const double& time, const double& option_price){
    
    if(option_price<0.99*(S-K*exp(-time*r))) return 0.0;
    
    const double ACCURACY = 1.0e-5;
    const int MAX_ITER = 100;
    const double ERROR = -1e40;
    double t_sqrt = sqrt(time);
    
    double sigma = (option_price/S)/(0.398*t_sqrt);
    
    double diff {};
    double d1 {};
    double vega {};
    for (int i = 0; i<MAX_ITER; i++){
        double price = option_price_call_BS(S, K, r, sigma, time);
        diff = option_price-price;
        if (fabs(diff)<ACCURACY) return sigma;
        d1 = (log(S/K) + r*time)/(sigma*t_sqrt)+0.5*sigma*t_sqrt;
        vega = S*t_sqrt*n(d1);
        sigma = sigma + diff/vega;
    }
    
    return ERROR;
}

int testVolImplied(){
    
    double S = 50;
    double K = 50;
    double r = 0.10;
    double time = 0.50;
    double C = 2.5;
    
    std::cout<<"Black-Scholes implied volatility using Newton = "<<option_price_implied_vol_call_BS_Newton(S, K, r, time, C)<<std::endl;
    
    std::cout<<"Black-Scholes implied volatility using Bissection = "<<option_price_implied_vol_call_BS_bissections(S, K, r, time, C)<<std::endl;
    
    return 0;
}
