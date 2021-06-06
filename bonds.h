//
//  bonds.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 05/06/2021.
//

#ifndef bonds_h
#define bonds_h

#include <vector>

double bonds_price_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);
double bonds_yield_to_maturity_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double& bondprice);
double bonds_duration_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);
double bonds_duration_macaulay_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price);
double bonds_convexity_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);
double bonds_duration_modified_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price);

double bonds_price(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);
double bonds_duration(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);
double bonds_yield_to_maturity(const std::vector<double>& times, const std::vector<double>& cashflows, const double& bondprice);
double bonds_duration_macaulay(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price);
double bonds_convexity(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r);


int testBondsPricingDiscrete();
int testBondsYieldToMaturityDiscrete();
int testBondsDurationSensisDiscrete();

int testBondsContinuous();

#endif /* bonds_h */
