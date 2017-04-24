//orbitlibrary.h

#include <math.h>
#include <stdio.h>

using namespace std;


//Constants

double dt=86400;	// Seconds in a day on earth
double m = 6.0e+24;	// Mass of the earth in kg
double A=-8e+44;	// A = -G*M*m, (6.67e-11*2e+30*6e+24)


//Structure that contains state of planet

#define D 2 //number of dimensions

struct particle {
		double x[D];
		double v[D];
		double F[D];
		double am[D];
		double t;
		double e;
		} ;



				//Functions to be used



//Function to print the current state of particle

double showState( particle &a )
	{
	printf( "Velocity in x direction: %12.6g\n Velocity in y direction: %12.6g\n Position in x: %12.6g\n Position in y: %12.6g\n Angular momentum in x direction: %12.6g\n Angular momentum in y: %12.6g\n Energy of particle: %12.6g\n Forces on particle: %12.6g %12.6g\n ", a.v[0], a.v[1], a.x[0], a.x[1] , a.am[0], a.am[1], a.e, a.F[0], a.F[1]);
	}



//Function to calculate the planet's radial distance to the origin

double radius( particle &a )
	{

	double d = pow((a.x[1]*a.x[1])+ (a.x[0]*a.x[0]), 0.5);
	return d;
	};



//Function to calculate the force on the planet

double force( particle &a, double A )
	{
	double f = A/(pow(radius(a),3));

	for (int i=0; i<D; i++)
		{
		a.F[i] = f*a.x[i];
		}
	}



//Function to calculate components of angular momentum about the origin

	void angm( particle &a, double m)
	{
	for (int i=0; i<D; i++)

		{
	 	a.am[i]=m*a.v[i]*radius(a);
		}
	}



//position step of particle

void pstep(particle &a, double dt)
	{
	for (int i=0; i<D; i++)
		{
	 	a.x[i] = a.x[i] + a.v[i]*dt;
		}
	}


//velocity step of particle

void vstep(particle &a, double dt, double m)
	{
	for (int i=0; i<D; i++)

		{
	 	a.v[i] = a.v[i] + a.F[i]*dt*(1/m);
		}
	}


// total energy of particle

void energy(particle &a, double A, double m)
	{
	a.e = 0.5*m*(a.v[0]*a.v[0]+a.v[1]*a.v[1]) + A*(1/(radius(a))); 
	}



