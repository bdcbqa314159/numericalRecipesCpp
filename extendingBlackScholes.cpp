//
//  extendingBlackScholes.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 22/06/2021.
//

#include "extendingBlackScholes.h"


double optPriceEurCallPayout(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time){
    
    double sigma_sqr = pow(sigma, 2);
    double time_sqrt = sqrt(time);
    
    double d1 = (log(S/K) + (r-q +0.5*sigma_sqr)*time)/(sigma*time_sqrt);
    double d2 = d1 - sigma*time_sqrt;
    
    double call_price = S*exp(-q*time)*N(d1) - K*exp(-r*time)*N(d2);
    return call_price;
}

double optPriceEurPutPayout(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time){
    
    double sigma_sqr = pow(sigma, 2);
    double time_sqrt = sqrt(time);
    
    double d1 = (log(S/K) + (r-q +0.5*sigma_sqr)*time)/(sigma*time_sqrt);
    double d2 = d1 - sigma*time_sqrt;
    
    double put_price = K*exp(-r*time)*N(-d2)- S*exp(-q*time)*N(-d1);
    return put_price;

}
int testOptPriceEurPayout(){
    
    double S = 100;
    double K = 100;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1;
    double q = 0.05;
    
    double callPrice = optPriceEurCallPayout(S, K, r, q, sigma, time);
    double putPrice = optPriceEurPutPayout(S, K, r, q, sigma, time);
    
    std::cout<<"Call Price = "<<callPrice<<std::endl;
    std::cout<<"Put Price = "<<putPrice<<std::endl;
    
    return 0;
}


double optionPriceEurCallDividends(const double& S, const double& K, const double& r, const double& sigma, const double& time, const std::vector<double>& dividend_times, const std::vector<double>& dividend_amounts){
    
    
    double adjusted_S = S;
    
    for (int i = 0; i<dividend_times.size(); i++){
        if (dividend_times[i]<=time)
            adjusted_S -= dividend_amounts[i]*exp(-r*dividend_times[i]);
    }
    
    return option_price_call_BS(adjusted_S, K, r, sigma, time);
    
}

int testOptPriceEurCallDividends(){
    
    double S = 100.0;
    double K = 100.0;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1.0;
    double dividend_yield = 0.05;
    
    std::vector<double> dividend_times{};
    std::vector<double> dividend_amounts{};
    dividend_times.push_back(0.25);
    dividend_amounts.push_back(2.5);
    dividend_times.push_back(0.75);
    dividend_amounts.push_back(2.5);
    
    std::cout<<"Euro Call option with continuous dividends = "<<optPriceEurCallPayout(S, K, r, dividend_yield, sigma, time)<<std::endl;
    std::cout<<"Euro Call option with discrete dividends = "<<optionPriceEurCallDividends(S, K, r, sigma, time, dividend_times, dividend_amounts)<<std::endl;
    
    return 0;
}

double optionPriceAmCallOneDividend(const double& S, const double& K, const double& r, const double& sigma, const double& tau, const double& D1,  const double& tau1){
    
    
    if (D1 <= K*(1.0 - exp(-r*(tau-tau1))))
        return option_price_call_BS(S - exp(-r*tau1)*D1, K, r, sigma, tau);
    
    const double ACCURACY = 1e-6;
    double sigma_sqr = sigma*sigma;
    double tau_sqrt = sqrt(tau);
    double tau1_sqrt = sqrt(tau1);
    double rho = -sqrt(tau1/tau);
    
    double S_bar = 0;
    double S_low = 0;
    double S_high = S;
    
    double c = option_price_call_BS(S_high, K, r, sigma, tau-tau1);
    double test = c-S_high-D1+K;
    
    while( (test>0.0) && (S_high<=1e10)){
        S_high *= 2.0;
        c = option_price_call_BS(S_high, K, r, sigma, tau-tau1);
        test = c-S_high-D1+K;
    }
    
    if (S_high>1e10)
        return option_price_call_BS(S - exp(-r*tau1)*D1, K, r, sigma, tau);
    
    S_bar = 0.5*S_high;
    
    c = option_price_call_BS(S_bar, K, r, sigma, tau-tau1);
    
    test = c-S_bar-D1+K;
    
    while ( (fabs(test) > ACCURACY) && ((S_high - S_low) > ACCURACY)){
        if (test<0.0)
            S_high = S_bar;
        else
            S_low = S_bar;
        
        S_bar = 0.5*(S_high+S_low);
        c = option_price_call_BS(S_bar, K, r, sigma, tau-tau1);
        test = c-S_bar-D1+K;
    }
    
    double a1 = (log((S-D1*exp(-r*tau1))/K) + (r+0.5*sigma_sqr)*tau)/(sigma*tau_sqrt);
    double a2 = a1 - sigma*tau_sqrt;
    double b1 = (log((S-D1*exp(-r*tau1))/S_bar) + (r+0.5*sigma_sqr)*tau1)/(sigma*tau1_sqrt);
    double b2 = b1 - sigma*tau1_sqrt;
    
    double C = (S-D1*exp(-r*tau1))*N(b1)+(S-D1*exp(-r*tau1))*N(a1,-b1,rho) - (K*exp(-r*tau))*N(a2,-b2,rho)-(K-D1)*exp(-r*tau1)*N(b2);
    
    return C;
}

int testOptionPriceAmCallOneDividend(){

    double S = 100;
    double K = 100;
    double r = 0.1;
    double sigma = 0.25;
    double tau = 1;
    double tau1 = 0.5;
    double D1 = 10.0;
    
    double callAmPrice = optionPriceAmCallOneDividend(S,K,r,sigma,tau,D1,tau1);
    
    
    std::cout<<"Call Price one dividend = "<<callAmPrice<<std::endl;
  
    return 0;
}

double futuresOptionPriceEurCallBlack(const double& F,const double& K, const double& r, const double& sigma, const double& time){
    
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double d1 = (log(F/K) +0.5*sigma_sqr*time)/(sigma*time_sqrt);
    double d2 = d1 - sigma*time_sqrt;
    
    return exp(-r*time)*(F*N(d1) - K*N(d2));
}


double futuresOptionPriceEurPutBlack(const double& F,const double& K, const double& r, const double& sigma, const double& time){
    
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double d1 = (log(F/K) +0.5*sigma_sqr*time)/(sigma*time_sqrt);
    double d2 = d1 - sigma*time_sqrt;
    
    return exp(-r*time)*(-F*N(-d1) + K*N(-d2));
}


double currencyOptionPriceEurCall(const double& S, const double& X, const double& r, const double& r_f, const double& sigma, const double& time){
    
    double sigma_sqr = sigma*sigma;
    double time_sqrt = sqrt(time);
    double d1 = (log(S/X) +(r-r_f+ 0.5*sigma_sqr*time))/(sigma*time_sqrt);
    double d2 = d1 - sigma*time_sqrt;
    
    return S*exp(-r_f*time)*N(d1) -X*exp(-r*time)*N(d2);

}

double optionPriceAmPerpetualCall(const double& S, const double& K, const double& r, const double& q, const double& sigma){
    
    
    double sigma_sqr = sigma*sigma;
    double h1 = 0.5-((r-q)/sigma_sqr);
    h1 += sqrt(pow(((r-q)/sigma_sqr-0.5),2) +2.0*r/sigma_sqr);
    double price = (K/(h1-1.0))*pow(((h1-1.0)/h1)*(S/K),h1);

    return price;
}

int testFuturesOptionPriceEurBlack(){
    
    double F = 50.0;
    double K = 45;
    double r = 0.08;
    double sigma = 0.2;
    double time = 0.5;
    
    std::cout<<"European futures call option = "<<futuresOptionPriceEurCallBlack(F, K, r, sigma, time)<<std::endl;
    
    std::cout<<"European futures put option = "<<futuresOptionPriceEurPutBlack(F, K, r, sigma, time)<<std::endl;
    
    return 0;
}


int testCurrencyOptionPriceEurCall(){
    
    double S = 50.0;
    double K = 52.0;
    double r = 0.08;
    double r_f = 0.05;
    double sigma = 0.2;
    double time = 0.5;
    
    std::cout<<"European currency call option = "<<currencyOptionPriceEurCall(S, K, r, r_f, sigma, time)<<std::endl;
    
    return 0;
}

int testOpptionPriceAmPerpetualCall(){
    
    double S = 50.0;
    double K = 40.0;
    double r = 0.05;
    double q = 0.02;
    double sigma = 0.05;
    
    std::cout<<"Perpetual American call = "<<optionPriceAmPerpetualCall(S, K, r, q, sigma)<<std::endl;
    
    return 0;
}
