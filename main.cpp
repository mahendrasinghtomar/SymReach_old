/*
 * main.cpp
 *
 *  Created on: May 17, 2018
 *      Author: MahendraSinghTomar
 */

#include "fadiff.h"
#include "badiff.h"
#define Global_L_hat 1  // 1 if global set for hessian computation, else 0
#include "ReachableSet2.h"
#include <iostream>
#include <array>
#include <cmath>
/* time profiling */
#include "TicToc.hh"

int PERFINDS;

// //----------------
int ExampleMst = 2;	// Van der Pol Oscillator
int state_dim = 2;
int input_dim = 1;
template<typename Tx, typename Tu>
Tx funcLj_system(Tx x, Tu u, Tx xx){
    xx[0] = x[1];
    xx[1] = x[1] - x[0] - x[0]*x[0]*x[1];
    return xx;
}
const int gdim = 2;	// global dim
symbol x0, x1;
std::vector<symbol> xs{x0, x1};	// x_symbol
std::vector<ex> f{xs[1],
					(xs[1] - xs[0] - xs[0]*xs[0]*xs[1])};

// //------------

// int ExampleMst = 3; // Laub-Loomis
// int state_dim = 7;
// int input_dim = 1;
// template<typename Tx, typename Tu>
// Tx funcLj_system(Tx x, Tu u, Tx xx){
    // xx[0] = 1.4*x[2] - 0.9*x[0];
    // xx[1] = 2.5*x[4] - 1.5*x[1];
	// xx[2] = 0.6*x[6] - 0.8*x[1]*x[2];
	// xx[3] = 2 - 1.3*x[2]*x[3];
	// xx[4] = 0.7*x[0] - x[3]*x[4];
	// xx[5] = 0.3*x[0] - 3.1*x[5];
	// xx[6] = 1.8*x[5] - 1.5*x[1]*x[6];
    // return xx;
// }
// const int gdim = 7;	// global dim
// symbol x0, x1, x2, x3, x4, x5, x6;
// std::vector<symbol> xs{x0, x1, x2, x3, x4, x5, x6};	// x_symbol
// std::vector<ex> f{1.4*xs[2] - 0.9*xs[0],
					// 2.5*xs[4] - 1.5*xs[1],
					// 0.6*xs[6] - 0.8*xs[1]*xs[2],
					// 2 - 1.3*xs[2]*xs[3],
					// 0.7*xs[0] - xs[3]*xs[4],
					// 0.3*xs[0] - 3.1*xs[5],
					// 1.8*xs[5] - 1.5*xs[1]*xs[6]};
// //------------


int main() {
	char ask = 'y';
	double tau, finaltime;
	int LinErrorMethod;
	double l_max;
	int morder, taylorTerms;
	int ask_chk = 0;
	while(ask == 'y')
	{

    std::vector<double> L_hat_storage;

    double x[state_dim], r[state_dim], u[input_dim];

// Van der Pol Oscillator
if(ExampleMst == 2)
{
	if(ask_chk==0)
	{
	tau = 0.01;	
	finaltime = 7;
	LinErrorMethod = 1;
	morder = 20;	// zonotope order above which order reduction
	l_max = 0.01;	
	taylorTerms = 4;
	PERFINDS = 1;	// 1(out of split only one tested), 2(perfind using both split sets)
	//applied error update (1.02)
	}

		x[0] = (1.55+1.25)*0.5;
	    x[1] = (2.35+2.45)*0.5;
	    r[0] = (1.55 - 1.25)*0.5;
	    r[1] = (2.45 - 2.35)*0.5;
	    u[0] = 0;
}

double W;
if(ExampleMst == 3)	//Laub-Loomis
{
	if(ask_chk==0)
	{
	tau = 0.1; // (0.1, 0.05), 0.01
	finaltime = 20;
	LinErrorMethod = 1;
	morder = 50;	// zonotope order above which order reduction
	l_max = 0.05;	//0.02
	taylorTerms = 4;
	PERFINDS = 1;	// 1(out of split only one tested), 2(perfind using both split sets)
	W = 0.1;	// (0.01, 0.1) initial box width
	}
		x[0] = 1.2;
	    x[1] = 1.05;
		x[2] = 1.5;
		x[3] = 2.4;
		x[4] = 1;
		x[5] = 0.1;
		x[6] = 0.45;
	    for(int i=0;i<state_dim;i++)
			r[i] = W*0.5;
	    u[0] = 0;
}
    ReachableSet(state_dim, input_dim, tau, r, x, u, L_hat_storage, finaltime, LinErrorMethod, l_max, morder, taylorTerms);

    std::cout << "Do you want to try another tau and finaltime?(y,n):";
    std::cin >> ask;
	if(ask!='y')
		return 0;
	std::cout << "enter tau = ";
	std::cin >> tau;
	std::cout << "enter finaltime =  ";
	std::cin >> finaltime;
	std::cout << "enter PERFINDS =  ";
	std::cin >> PERFINDS;
	std::cout << "enter l_max =  ";
	std::cin >> l_max;
	if(ExampleMst==3)
	{
		std::cout << "enter W = ";
		std::cin >> W;
	}

	ask_chk += 1;
	}
    return 0;
}










