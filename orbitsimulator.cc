/*
*
* Leapfrog and Euler simulations of planetary orbits
* 
*/
#include <iostream>
#include "orbitlibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{

//Initial conditions of planet	
//Use 'define' as this doesn't use memory during runtime
//Key definitions are in one place and so can be altered here

#define I 	  800000	//number of iterations
#define init_v_x    1000	// initial velocity in x axis
#define init_v_y   10000	// initial velocity in y axis
#define init_pos_x 7e+11	// initial x position (metres from 'Sun')
#define init_pos_y     0	// initial y position
#define init_time      0.0	// initial time

//Declarations

	FILE *leapfrogdata;
	FILE *eulerdata;
	FILE *gnuplotPipe;
	char const *tempdatafilename;
	double xpoint,ypoint;

//Initial state of planet

	particle a ;
	a.v[0] = init_v_x;
	a.v[1] = init_v_y;
	a.x[0] = init_pos_x;
	a.x[1] = init_pos_y;
	a.t    = init_time;
	
//leapfrog method simulator

	//Create file for data and open gnuplot

	tempdatafilename = "tempDataLF";
	gnuplotPipe = popen("gnuplot -persist","w");
 
if (gnuplotPipe) 
	{

 	leapfrogdata = fopen(tempdatafilename,"w");

	for(int i=0; i<I; i++)
		{

		//Leapfrog iteration 

			pstep( a, 0.5*dt);
			a.t = a.t + 0.5*dt;
			force(a, A);
			vstep(a, dt, m);
			pstep(a, 0.5*dt);
			a.t = a.t + 0.5*dt;

		//Output of variables into file
		//Intermediate variables not a necessity but provide some clarity

		xpoint = a.x[0];
		ypoint = a.x[1];

		fprintf(leapfrogdata,"%lf %lf\n",xpoint,ypoint);

		}

	//Formatting and printing gnuplot

	fprintf(gnuplotPipe, "set title \"Simulation of Earth's motion around the Sun at (0,0) in a 2D plane using the Leapfrog method\"\n");
	fprintf(gnuplotPipe, "set xlabel \"Position in X\"\n");
	fprintf(gnuplotPipe, "set ylabel \"Position in Y\"\n");
	fprintf(gnuplotPipe,"plot \"%s\" with lines\n",tempdatafilename);
	
	//Close the temp file with the data for leapfrog method

 	fclose(leapfrogdata);
	}
else 
	{
 	printf("gnuplot not found...");
	}


//Reset initial conditions for Euler method simulation

	a.v[0] = init_v_x;
	a.v[1] = init_v_y;
	a.x[0] = init_pos_x;
	a.x[1] = init_pos_y;
	a.t = init_time;


//Euler method simulator

	//Create file for data and open gnuplot

	tempdatafilename = "tempDataE";
	gnuplotPipe = popen("gnuplot -persist","w");
 
if (gnuplotPipe) 
	{

 	eulerdata = fopen(tempdatafilename,"w");

	for(int i=0; i<I; i++)
		{
		//Euler iteration

			force(a, A);
			pstep( a, dt);
			vstep(a, dt, m);
			a.t = a.t + dt;

		//Output of variables into file
		//Intermediate variables not a necessity but provide some clarity
	
		xpoint = a.x[0];
		ypoint = a.x[1];

		fprintf(eulerdata,"%lf %lf\n",xpoint,ypoint);

		}

		//Formatting and printing gnuplot

	fprintf(gnuplotPipe, "set title \"Simulation of Earth's motion around the Sun at (0,0) in a 2D plane using the Euler method\"\n");
	fprintf(gnuplotPipe, "set xlabel \"Position in X\"\n");
	fprintf(gnuplotPipe, "set ylabel \"Position in Y\"\n");
	fprintf(gnuplotPipe,"plot \"%s\" with lines\n",tempdatafilename);

	//Close the temp file with the data for Euler method
	
 	fclose(eulerdata);
	}

else 
	{
 	printf("gnuplot not found...");
	}

showState(a);
return 0;
}







