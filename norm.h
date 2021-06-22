//
//  norm.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#ifndef norm_h
#define norm_h

#include <math.h>

double sgn(const double& x);
double f(const double& x, const double& y, const double& aprime, const double& bprime, const double& rho);
double N(double x);
double n(double x);
double N(const double& a, const double& b , const double& c);


#endif /* norm_h */
