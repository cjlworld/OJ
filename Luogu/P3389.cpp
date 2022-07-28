#include<cmath>
#include<cstdio>
#include<iostream>

using namespace std;

const int N=1e3+5;
const double eps=1e-10;

int n;
double a[N][N];

void print()
{
	for(int i=0;i<n;i++,printf("\n"))
		for(int j=0;j<n+1;j++) 
			printf("%.2lf ",a[i][j]);
	printf("\n");	
}

int gauss()
{
	int r,c;
	for(c=0,r=0;c<n;c++) {
		int t=r;
		for(int i=r;i<n;i++) 
			if(fabs(a[i][c])>fabs(a[t][c])) t=i;
		for(int i=0;i<n+1;i++) 
			swap(a[r][i],a[t][i]);
		double rate=a[r][c]; // !
		if(fabs(rate)<eps) continue; // !
		for(int i=c;i<n+1;i++) a[r][i]/=rate;
		for(int i=r+1;i<n;i++) {
			rate=a[i][c];
			for(int j=c;j<n+1;j++) 
				a[i][j]-=rate*a[r][j];
		}
		r++;
	}
	
	if(r<n) {
		for(int i=r;i<n;i++) 
			if(fabs(a[i][n])>eps) return 2; // No Solution !
		return 1; // Infinite group solutions !
	} 
	
	for(int i=n-1;i>=0;i--) 
		for(int j=i-1;j>=0;j--)
			a[j][n]-=a[i][n]*a[j][i];
	return 0;
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++) 
		for(int j=0;j<n+1;j++) 
			cin>>a[i][j];
	
	int ans=gauss();
	if(ans==2) puts("No Solution");
	else if(ans==1) puts("No Solution");
	else {
		for(int i=0;i<n;i++) 
			printf("%.2lf\n",a[i][n]);
	}
	
	return 0;
}

