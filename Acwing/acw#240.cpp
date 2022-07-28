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

const int N=1e5+5;
int n,k;

int par[N],d[N];
int Find(int x)
{
	if(par[x]!=x) {
		int root=Find(par[x]);
		d[x]=(d[x]+d[par[x]])%3;
		par[x]=root;
	}
	return par[x];
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z,opt;
	int ans=0;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) par[i]=i;
	while(k--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(x>n||y>n) ans++;
		else if(opt==2&&x==y) ans++;
		else {
			if(opt==1) {
				if(Find(x)==Find(y)&&d[x]!=d[y]) ans++; 
					// x,y 已经异类 
				else if(Find(x)!=Find(y)){
					z=Find(y);
					par[z]=x, d[z]=(-d[y]+3)%3;
					// d[y]+d[z]==0 (mod 3)
					// d[z]=-d[y] (mod 3)
				}	
			}
			else {
				if(Find(x)==Find(y)&&(d[x]-1+3)%3!=d[y]) ans++; 
					// y --> x 或 x,y 同类 
				else if(Find(x)!=Find(y)) {
					z=Find(x);
					par[z]=y,d[z]=(1-d[x]+3)%3;
					// d[z]+d[x]==1 (mod 3)
					// d[z]=1-d[x] (mod 3)
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

