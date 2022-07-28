#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
const int N=31;
LL f[N][N][N][N][N];
int k;
int a[N];
int n;
int main() 
{
//	freopen("1.in","r",stdin);
	int i,j,k,e,r;
	int x,y,z;
	while(cin>>k,k) {
		n=0; 
		memset(f,0,sizeof f);
		memset(a,0,sizeof a);
		for(i=1; i<=k; i++)
			cin>>a[i],n+=a[i];

		f[0][0][0][0][0]=1;
		for(i=1; i<=a[1]; i++) {
			for(j=0; j<=min(i,a[2]); j++) {
				for(k=0; k<=min(j,a[3]); k++) {
					for(e=0; e<=min(k,a[4]); e++) {
						for(r=0; r<=min(e,a[5]); r++) {
							LL &ans=f[i][j][k][e][r];
							if(i>=1) ans+=f[i-1][j][k][e][r];
							if(j>=1) ans+=f[i][j-1][k][e][r];
							if(k>=1) ans+=f[i][j][k-1][e][r];
							if(e>=1) ans+=f[i][j][k][e-1][r];
							if(r>=1) ans+=f[i][j][k][e][r-1];
						}
					}
				}
			}
		}
		cout<<f[a[1]][a[2]][a[3]][a[4]][a[5]]<<endl;
	}
	return 0;
}
