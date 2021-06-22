//
//  extendingBlackScholes.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 22/06/2021.
//

#ifndef extendingBlackScholes_h
#define extendingBlackScholes_h

#include <iostream>
#include <vector>
#include <math.h>
#include "norm.h"
#include "basicBlackScholes.h"

double optPriceEurCallPayout(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time);

double optPriceEurPutPayout(const double& S, const double& K, const double& r, const double& q, const double& sigma, const double& time);

double optionPriceEurCallDividends(const double& S, const double& K, const double& r, const double& sigma, const double& time, const std::vector<double>& dividend_times, const std::vector<double>& dividend_amounts);

double optionPriceAmCallOneDividend(const double& S, const double& K, const double& r, const double& sigma, const double& tau, const double& D1,  const double& tau1);

int testOptPriceEurPayout();

int testOptPriceEurCallDividends();

int testOptionPriceAmCallOneDividend();



#endif /* extendingBlackScholes_h */
