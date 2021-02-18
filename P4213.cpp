// 	P4213 ¡¾Ä£°å¡¿¶Å½ÌÉ¸£¨Sum£©
#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL Maxn=1e7;

int p[Maxn],tot;
bool tag[Maxn];
LL phi[Maxn],miu[Maxn];
void prime(int n)
{
	int i,j;
	miu[1]=1,phi[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) {
			p[++tot]=i;
			phi[i]=i-1;
			miu[i]=-1;
		}
		for(j=1;j<=tot && p[j]*i<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) {
				phi[i*p[j]]=phi[i]*p[j];
				miu[i*p[j]]=0;
				break;
			}
			else {
				phi[i*p[j]]=phi[i]*(p[j]-1);
				miu[i*p[j]]=-miu[i];
			}
		}
	}
	for(i=1;i<=n;i++) 
		miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

LL Sum_phi(LL n)
{
	static map<int,LL> sum;
	if(n<Maxn) return phi[n];

	if(sum.count(n)) return sum[n];
	
	LL res=1ll*n*(n+1)/2;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res-=(j-i+1)*Sum_phi(t);
	}
	return sum[n]=res;
}

LL Sum_miu(LL n)
{
	static map<LL,LL> sum;
	
	if(n<Maxn) return miu[n];
	
	if(sum.count(n)) return sum[n];
	LL res=1ll;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res-=(j-i+1)*Sum_miu(t);
	}
	return sum[n]=res;
}

int T;
LL n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(Maxn-1);
	cin>>T;
	while(T--) {
		cin>>n;
		cout<<Sum_phi(n)<<" "<<Sum_miu(n)<<endl;
	}
	return 0;
}


