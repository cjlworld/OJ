#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const double eps=1e-12;

double f(double x) { return sin(x)/x; }
double area(double l,double r) 
{
	double mid=(l+r)/2;
	return (f(l)+4*f(mid)+f(r))/6*(r-l);
}

double simpson(double l,double r,double s)
{
	double mid=(l+r)/2;
	double left=area(l,mid),right=area(mid,r);
	if(fabs(left+right-s)<eps) return left+right;
	else return simpson(l,mid,left)+simpson(mid,r,right);
}

int main()
{
	double a,b;
	cin>>a>>b;
	printf("%.6lf\n",simpson(a,b,area(a,b)));
	return 0;
}

