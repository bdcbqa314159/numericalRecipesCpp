//
//  timeValue.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 20/05/2021.
//

#include "timeValue.h"

double cash_flow_pv_discrete(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts, const double& r){
    
    double PV{};
    
    for (int t{}; t<cflow_times.size(); t++){
        PV += cflow_amounts[t]/std::pow(1.0+r, cflow_times[t]);
    }
    
    return PV;
    
}

double cash_flow_irr_discrete(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts){
    
    if (cflow_times.size()!= cflow_amounts.size()) return ERRROR;
    
    double x1=0.0;
    double x2=0.2;
    
    double f1 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1);
    double f2 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x2);
    
    for (int i=0; i<MAX_ITERATIONS; i++){
        if (f1*f2 < 0.0) break;
        
        if (fabs(f1)<fabs(f2))
            f1 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1+=1.6*(x1-x2));
        else
            f2 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x2+=1.6*(x2-x1));
    }
    
    if (f2*f1>0.0) return ERRROR;
    
    double f = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1);
    double rtb;
    double dx = 0;
    
    if(f<0.0){
        rtb = x1;
        dx = x2-x1;
    }
    
    else{
        rtb = x2;
        dx = x1 - x2;
    }
    
    for (int i = 0; i<MAX_ITERATIONS; i++){
        dx *= 0.5;
        double x_mid = rtb+dx;
        double f_mid = cash_flow_pv_discrete(cflow_times, cflow_amounts, x_mid);
        
        if (f_mid<=0.0) rtb = x_mid;
        if ((fabs(f_mid)< ACCURACY) || (fabs(dx)< ACCURACY)) return x_mid;
    }
    
    return ERRROR;
}


bool cash_flow_unique_irr(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts){
    
    int sign_changes=0;
    
    for (int t = 1; t<cflow_times.size(); ++t)
        if(sgn(cflow_times[-1]) != sgn(cflow_times[t])) sign_changes ++;
    
    if (sign_changes == 0) return false;
    if (sign_changes == 1) return true;
    
    double A = cflow_amounts[0];
    sign_changes = 0;
    for (int t=1; t<cflow_times.size(); ++t)
        if(sgn(A) != sgn(A+=cflow_amounts[t])) sign_changes++;
    
    if (sign_changes<=1) return true;
    return false;
}

double cash_flow_pv(const std::vector<double>& cflow_times, const std::vector<double>& cflow_amounts, const double& r){
    
    double PV{};
    
    for (int t{}; t<cflow_times.size(); t++){
        PV += cflow_amounts[t]*exp(-r*cflow_times[t]);
    }
    
    return PV;
    
}


int testTimeValue(){
    
    std::cout<<std::boolalpha;
    
    std::vector<double> C{-100, 75,75};
    std::vector<double> t{0, 1, 2};
    double r = 0.1;
    
    double NPV = cash_flow_pv_discrete(t, C, r);
    
    std::cout<<"NPV : "<<NPV<<std::endl;
    std::cout<<"Testing unique IRR : "<<std::endl;
    std::cout<<cash_flow_unique_irr(t, C)<<std::endl;
    
    
    return 0;
}

int testIRR(){
    
    std::cout<<std::boolalpha;
    
    std::vector<double> C{-100, 10, 110};
    std::vector<double> t{0, 1, 2};
    double r = 0.05;
    
    double NPV = cash_flow_pv_discrete(t, C, r);
    
    std::cout<<"NPV : "<<NPV<<std::endl;
    
    double IRR = cash_flow_irr_discrete(t, C);
    
    std::cout<<"IRR : "<<IRR<<std::endl;
    
    std::cout<<"Testing unique IRR : "<<std::endl;
    std::cout<<cash_flow_unique_irr(t, C)<<std::endl;
    

    return 0;
}


int testCashFlowPV(){
    
    std::cout<<std::boolalpha;
    
    std::vector<double> C{-100, 75,75};
    std::vector<double> t{0, 1, 2};
    double r = 0.1;
    
    double NPV = cash_flow_pv(t, C, r);
    
    std::cout<<"NPV : "<<NPV<<std::endl;
    std::cout<<"Testing unique IRR : "<<std::endl;
    std::cout<<cash_flow_unique_irr(t, C)<<std::endl;
    
    
    return 0;
    
}


