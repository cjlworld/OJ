#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=1e7+5;

int p[N],tot;
bool tag[N];
LL phi[N],Sphi[N];

void prime(int n)
{
	int i,j;
	phi[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) phi[p[++tot]=i]=i-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) {
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	Sphi[0]=-1;
	for(i=1;i<=n;i++) Sphi[i]=Sphi[i-1]+2*phi[i];
}

int main()
{
//	freopen("1.in","r",stdin);
	int n;
	cin>>n;
	prime(n);
	LL ans=0;
	for(int i=1;i<=tot;i++) 
		ans+=Sphi[n/p[i]];
	cout<<ans<<endl;
	return 0;
}

