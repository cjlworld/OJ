#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int MOD=1000000;
const int N=80000+5;
const int INF=(-1u)>>1;
set<int> S0,S1;
LL ans=0;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int opt,x,y,z;
	scanf("%d",&n);
	set<int>::iterator it;
	for(i=1;i<=n;i++) {
		scanf("%d%d",&opt,&x);
		y=z=INF;
		if(opt==0) {
			if(S1.empty()) {
				S0.insert(x);
				continue;
			}
			else {
				it=S1.lower_bound(x);
				if(it!=S1.end()) y=*it-x,z=*it;
				if(it!=S1.begin()) {
					it--;
					if(x-*it<=y) {
						y=x-*it;
						z=*it;
					}
				}
				S1.erase(z);
				ans=(ans+y)%MOD;
			}
 		}
 		else {
 			if(S0.empty()) {
 				S1.insert(x);
				continue;	
			}
			else {
				it=S0.lower_bound(x);
				if(it!=S0.end()) y=*it-x,z=*it;
				if(it!=S0.begin()) {
					it--;
					if(x-*it<=y) {
						y=x-*it;
						z=*it;
					}
				}
				S0.erase(z);
				ans=(ans+y)%MOD;
			}
		}
	}
	cout<<ans;
	return 0;
}

