//
//  timeValue.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 20/05/2021.
//

#ifndef timeValue_h
#define timeValue_h

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "norm.h"

const double ERRROR = -1.0e30;
const double ACCURACY = 1.0e-5;
const int MAX_ITERATIONS = 50;

double cash_flow_pv_discrete(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts, const double& r);

double cash_flow_irr_discrete(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts);

bool cash_flow_unique_irr(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts);

double cash_flow_pv(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts, const double& r);

int testTimeValue();
int testIrr();
int testUniqueIRR();
int testCashFlowPV();


#endif /* timeValue_h */
