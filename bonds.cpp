//
//  bonds.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 05/06/2021.
//

#include "bonds.h"
#include <cmath>
#include <iostream>

double bonds_price_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){

	double p{};

	for (int i{}; i<times.size(); i++){
        p+= cashflows.at(i)/(pow((1+r), times.at(i)));
	}

    return p;

}

double bonds_yield_to_maturity_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double& bondprice){

	const double ACCURACY = 1e-5;
	const int MAX_ITER = 200;

	double bot = 0;
	double top = 1.0;

	while(bonds_price_discrete(times,cashflows,top) > bondprice){top = 2*top;}

	double r = 0.5*(top+bot);

	for (int i{}; i<MAX_ITER;i++){
		double diff = bonds_price_discrete(times,cashflows,r) - bondprice;

		if (fabs(diff)<ACCURACY) return r;
		if (diff>0.0)
			bot = r;
		else
			top = r;
		r = 0.5*(top+bot);
	}

	return r;
}

double bonds_duration_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){

	double B = bonds_price_discrete(times, cashflows, r);
	double D{};

	for (int i{}; i<times.size(); i++){
		D += times.at(i)*cashflows.at(i)/pow((1+r), times.at(i));
	}

	return D/B;
}

double bonds_duration_macaulay_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price){

	double y = bonds_yield_to_maturity_discrete(times, cashflows, bond_price);
	return bonds_duration_discrete(times, cashflows, y);

}

double bonds_duration_modified_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price){

	double y = bonds_yield_to_maturity_discrete(times, cashflows, bond_price);
	double D = bonds_duration_discrete(times, cashflows, y);

	return D/(1+y);
}


double bonds_convexity_discrete(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){


	double Cx{};
	for (int i{}; i<times.size(); i++){
		Cx += cashflows.at(i)*times.at(i)*(times.at(i)+1)/pow((1+r), times.at(i));
	}

	double B = bonds_price_discrete(times, cashflows, r);

	return (Cx/(pow(1+r,2)))/B;

}

double bonds_price(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){

	double p{};

	for (int i{}; i<cashflows.size();i++){
        p += exp(-r*times.at(i))*cashflows.at(i);
	}

	return p;

}

double bonds_duration(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){

	double D{};

	for (int i{}; i<times.size(); i++)
        D += times.at(i)*cashflows.at(i)*exp(-r*cashflows.at(i));

	return D/bonds_price(times, cashflows, r);

}

double bonds_yield_to_maturity(const std::vector<double>& times, const std::vector<double>& cashflows, const double& bondprice){

	const double ACCURACY = 1e-5;
	const int MAX_ITER = 200;

	double bot = 0;
	double top = 1.0;

	while(bonds_price(times,cashflows,top) > bondprice){top = 2*top;}

	double r = 0.5*(top+bot);

	for (int i{}; i<MAX_ITER;i++){
		double diff = bonds_price(times,cashflows,r) - bondprice;

		if (fabs(diff)<ACCURACY) return r;
		if (diff>0.0)
			bot = r;
		else
			top = r;
		r = 0.5*(top+bot);
	}

	return r;
}

double bonds_duration_macaulay(const std::vector<double>& times, const std::vector<double>& cashflows, const double &bond_price){
	double y = bonds_yield_to_maturity(times, cashflows, bond_price);
	return bonds_duration_discrete(times, cashflows, y);
}

double bonds_convexity(const std::vector<double>& times, const std::vector<double>& cashflows, const double &r){


	double Cx{};
	for (int i{}; i<times.size(); i++){
		Cx += cashflows.at(i)*pow(times.at(i),2)*exp(-r*times.at(i));
	}

	double B = bonds_price(times, cashflows, r);

	return Cx/B;

}


int testBondsPricingDiscrete(){

	std::vector<double> cflows{};
	std::vector<double> times{};

	times.push_back(1);
	times.push_back(2);
	times.push_back(3);

	cflows.push_back(10);
	cflows.push_back(10);
	cflows.push_back(110);

	double r = 0.09;

	std::cout<<"Bond price: "<< bonds_price_discrete(times, cflows, r)<<std::endl;


	return 0;
}

int testBondsYieldToMaturityDiscrete(){

	std::vector<double> cflows{};
	std::vector<double> times{};

	times.push_back(1);
	times.push_back(2);
	times.push_back(3);

	cflows.push_back(10);
	cflows.push_back(10);
	cflows.push_back(110);

	double r = 0.09;

	double bond_price = bonds_price_discrete(times, cflows, r);

	std::cout<<"Bond price: "<< bond_price <<std::endl;
	std::cout<<"Bond YTM: "<< bonds_yield_to_maturity_discrete(times, cflows, bond_price)<<std::endl;

	return 0;
}

int testBondsDurationSensisDiscrete(){

	std::vector<double> cflows{};
	std::vector<double> times{};

	times.push_back(1);
	times.push_back(2);
	times.push_back(3);

	cflows.push_back(10);
	cflows.push_back(10);
	cflows.push_back(110);

	double r = 0.09;

	double bond_price = bonds_price_discrete(times, cflows, r);
	std::cout<<"Bond price: "<< bond_price <<std::endl;
	std::cout<<"Bond duration: "<<bonds_duration_discrete(times, cflows, r)<<std::endl;
	std::cout<<"Bond Macaulay duration: "<<bonds_duration_macaulay_discrete(times, cflows, bond_price)<<std::endl;

	std::cout<<"Bond Duration modified: "<<bonds_duration_modified_discrete(times, cflows, bond_price)<<std::endl;
	std::cout<<"Bond Convexity: "<<bonds_convexity_discrete(times, cflows, r)<<std::endl;
	std::cout<<"New Bond price: "<<bonds_price_discrete(times, cflows, 0.1)<<std::endl;


	return 0;
}

int testBondsContinuous(){

	std::vector<double> cflows{};
	std::vector<double> times{};

	times.push_back(1);
	times.push_back(2);
	times.push_back(3);

	cflows.push_back(10);
	cflows.push_back(10);
	cflows.push_back(110);

	double r = 0.09;

	double bond_price = bonds_price(times, cflows, r);
	std::cout<<"Bond price: "<< bond_price <<std::endl;
	std::cout<<"Bond duration: "<<bonds_duration(times, cflows, r)<<std::endl;
	std::cout<<"Bond Macaulay duration: "<<bonds_duration_macaulay(times, cflows, bond_price)<<std::endl;

	std::cout<<"Bond Convexity: "<<bonds_convexity_discrete(times, cflows, r)<<std::endl;
	std::cout<<"New Bond price: "<<bonds_price_discrete(times, cflows, 0.1)<<std::endl;

	return 0;
}
