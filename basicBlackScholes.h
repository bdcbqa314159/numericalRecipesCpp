//
//  basicBlackScholes.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#ifndef basicBlackScholes_h
#define basicBlackScholes_h

#include <math.h>
#include <iostream>

double N(double x);
double n(double x);

double option_price_call_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time);

double option_price_put_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time);

void option_price_partials_call_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time, double& Delta, double& Gamma, double& Theta, double& Vega,  double& Rho);

double option_price_implied_vol_call_BS_bissections(const double& S, const double& K, const double& r, const double& time, const double& option_price);

double option_price_implied_vol_call_BS_Newton(const double& S, const double& K, const double& r, const double& time, const double& option_price);

int testOptionPriceCallPutPartialsBS();
int testVolImplied();


#endif /* basicBlackScholes_h */
