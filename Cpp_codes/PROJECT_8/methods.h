#include<vector>
#ifndef METHODS_H
#define METHODS_H

using namespace std;

double bisec(double xl, double xr, double tolx, double (*fun)(double))
{
	if (fun(xr)*fun(xl)>0.)
	{
		printf("No zero within the specified range\n");
	}
	else if(fun(xr)*fun(xl)==0.)
	{
		if(fun(xr)==0.){
		return xr;
	}
	else return xl;
	}
	while ((xr-xl)/2.>tolx)
	{
		double x=(xr+xl)/2;
		if (fun(xr)*fun(x)<0.)
		{
			xl=x;
		}
		else
		xr=x;
	}
	return (xr+xl)/2.;

}

vector<double> numerow2(double a,double b,double ndiv,double y0,double y,double (*funk)(double,double),double K)
{
	double h=(b-a)/ndiv;
	vector<double> p;
	p.push_back(y0);
	p.push_back(y);
	for(int i=2;i<ndiv;i++)
	{
		double temp = (2.*p.at(i-1)*(1.-5.*h*h*funk(a+h*(i-1),K)/12.)/(1.+h*h*funk(a+h*i,K)/12.)-p.at(i-2)*(1.+h*h*funk(a+h*(i-2),K)/12.)/(1.+h*h*funk(a+h*i,K)/12.));
		p.push_back(temp);
	}
	return p;
}

#endif
