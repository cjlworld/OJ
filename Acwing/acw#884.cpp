#include<bitset>
#include<cstdio>
#include<iostream>

using namespace std;

const int N=200+5;

int n;
bitset<N> a[N];

int gauss()
{
	int r,c;
	for(c=0,r=0;c<n;c++) {
		int t=r;
		for(int i=r;i<n;i++) 
			if(a[i][c]>a[t][c]) t=i;
		swap(a[r],a[t]);
		if(!a[r][c]) continue;
		for(int i=r+1;i<n;i++) 
			if(a[i][c]) a[i]=a[i]^a[r];
		r++;
	}
	
	if(r<n) {
		for(int i=r;i<n;i++)
			if(a[i][n]) return 2;
		return 1;
	}
	
	for(int i=n-1;i>=0;i--) 
		for(int j=i-1;j>=0;j--) 
			if(a[j][i]) a[j]=a[j]^a[i];
	return 0;
}

int main()
{
	int i,j,x;

	scanf("%d",&n);
	for(i=0;i<n;i++) 
		for(j=0;j<n+1;j++) {
			scanf("%d",&x);
			a[i][j]=x;
		}
	
	int ans=gauss();
	if(ans==2) puts("No solution");
	else if(ans==1) puts("Multiple sets of solutions");
	else {
		for(i=0;i<n;i++) 
			printf("%d\n",a[i][n]==1);
	}
	return 0;
}

