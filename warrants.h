//
//  warrants.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#ifndef warrants_h
#define warrants_h

#include "norm.h"
#include "basicBlackScholes.h"
#include <iostream>
#include <math.h>

const double EPSILON = 0.00001;

double warrant_price_adjusted_BS(const double& S, const double& K, const double& r, const double& sigma, const double& time, const double& m, const double& n);

int testWarrantAdjustedBS();



#endif /* warrants_h */
