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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=50;
const LL INF=0x3f3f3f3f3f3f3f3f;

int T,n;
LL a[N];
vector<LL> v1,v2;
LL sum1,sum2;
LL ans;

inline LL mabs(LL x) { return ((x<0) ? -x : x); }
void SA()
{
	random_shuffle(a+1,a+n+1);
	sum1=sum2=0;
	v1.clear(); v2.clear();
	for(int i=1;i<=n/2;i++) v1.push_back(a[i]),sum1+=a[i];
	for(int i=n/2+1;i<=n;i++) v2.push_back(a[i]),sum2+=a[i];
	
	for(double t=1e4;t>1e-4;t*=0.99) {
		int x=rand()%v1.size(),y=rand()%v2.size();
		LL dt=mabs((sum1-v1[x]+v2[y])-(sum2-v2[y]+v1[x]))-mabs(sum1-sum2); // ¶¼ÊÇ ÐÂ-¾É 
		if(exp(-dt/t)>(double)rand()/RAND_MAX) { // Accept
			sum1=sum1-v1[x]+v2[y];
			sum2=sum2-v2[y]+v1[x];
			swap(v1[x],v2[y]);
			ans=min(ans,mabs(sum1-sum2));
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i;
		
	cin>>T;
	while(T--) {
		cin>>n;
		for(i=1;i<=n;i++) cin>>a[i];
		if(n==1) {
			printf("%lld\n",a[1]);
			continue;
		}
		ans=INF;
		for(i=1;i<=100;i++) SA();
		cout<<ans<<endl;
	}
	return 0;
}

