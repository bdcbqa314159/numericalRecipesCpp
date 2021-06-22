//
//  norm.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 21/06/2021.
//

#include "norm.h"

double sgn(const double& x){
    if (x>=0.0) return 1.0;
    else return -1.0;
}

double f(const double& x, const double& y, const double& aprime, const double& bprime, const double& rho){
    
    double r = aprime*(2*x-aprime) + bprime*(2*y-bprime) + 2*rho*(x-aprime)*(y-bprime);
    return exp(r);
}

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

double N(const double& a, const double& b , const double& rho){
    
    
    if ((a<=0.0) && (b<=0.0) && (rho<=0.0)){
        
        double pi = 4.0*atan(1.0);
        double aprime = a/sqrt(2.0*(1.0-rho*rho));
        double bprime = b/sqrt(2.0*(1.0-rho*rho));
        
        double A[4] = {0.3253030, 0.4211071, 0.134425, 0.006374323};
        double B[4] = {0.1337764, 0.6243247, 1.3425378, 2.2626645};
        
        double sum = 0;
        
        for (int i = 0; i<4; i++){
            for (int j = 0; j<4; j++){
                sum += A[i]*A[j]*f(B[i], B[j], aprime, bprime, rho);
            }
        }
        
        sum = sum *(sqrt(1.0-rho*rho)/pi);
        return sum;
    }
    
    else if ( a*b*rho <= 0.0){
        if ( (a<=0) && (b>=0.0) && (rho>=0.0))
            return N(a) - N(a,-b,-rho);
        
        else if ( (a>=0) && (b<=0.0) && (rho>=0.0))
            return N(b) - N(-a,b,-rho);
        
        else if ( (a>=0) && (b>=0.0) && (rho<=0.0))
            return N(a) + N(b) -1.0 + N(-a,-b,rho);
    }
    
    else if (a*b*rho >= 0.0){
        
        double denum = sqrt(a*a - 2*rho*a*b + b*b);
        double rho1 = ((rho*a-b)*sgn(a))/denum;
        double rho2 = ((rho*b-a)*sgn(b))/denum;
        double delta = (1.0-sgn(a)*sgn(b))/4.0;
        return N(a,0.0,rho1)+N(b,0,rho2) - delta;
        
    }
    
    else {
        
    }
    
    return -99.9;
    
}
