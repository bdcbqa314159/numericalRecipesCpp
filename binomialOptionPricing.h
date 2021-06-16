//
//  binomialOptionPricing.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 16/06/2021.
//

#ifndef binomialOptionPricing_h
#define binomialOptionPricing_h

#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>

double option_price_call_euro_bin_single_period(const double& S, const double& X, const double& r, const double& u, const double& d );

std::vector<std::vector<double>> binomial_tree(const double& S0, const double& u, const double& d, const int& no_steps);

int testEuroCallBinomialMultiPeriod();

#endif /* binomialOptionPricing_h */
