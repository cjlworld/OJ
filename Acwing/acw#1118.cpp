#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=16,S=(1<<N);

int gcd(int a,int b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int n;
int a[N],f[S];

int main()
{
	int i,j,k;
	cin>>n;
	for(i=0;i<n;i++) 
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof f);
	for(i=(1<<n)-1;i>=0;i--) {
		if(f[i]==1) continue;
		for(j=0;j<n;j++) {
			if(!((i>>j)&1)) continue;
			for(k=j+1;k<n;k++) {
				if(!((i>>k)&1)) continue; 
				if(gcd(a[j],a[k])!=1) break;
			}
			if(k<n) break;
		}
		if(j==n) {
			for(j=i;j;j=(j-1)&i) f[j]=1;
//			printf("%d\n",i);
		}	
	}
	for(i=1;i<(1<<n);i++) 
		for(j=(i-1)&i;j;j=(j-1)&i) 
			f[i]=min(f[i],f[j]+f[i-j]);
	cout<<f[(1<<n)-1]<<endl;
	return 0;
}

