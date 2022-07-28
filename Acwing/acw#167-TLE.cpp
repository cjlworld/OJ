#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=100+5;
const unsigned P=133333;
//
//struct HashExcel
//{
//	int one[P],idx;
//	unsigned ver[P];
//	int Next[P];
//	
//	void insert(unsigned x)
//	{
//		unsigned u=x%P;
//		Next[++idx]=one[u],one[u]=idx,ver[idx]=x;
//	}
//}
vector<unsigned> v;

int a[N];
int n,W;
int w[N],tot,cnt;

unsigned Hash(int *arr,int ed)
{
	unsigned res=1;
	int i;
	for(i=1;i<=ed;i++) 
		res=res*(unsigned)arr[i];
	for(i=1;i<=ed;i++) 
		res=res+arr[i];
	return res;
}

void dfs1(int step,int depth,int W)
{
	if(step==depth+1) {
		v.push_back(Hash(w,tot));
		return;
	}
	for(int i=1;i<=cnt;i++) {
		if(w[i]+a[step]<=W) {
			w[i]+=a[step];
			dfs1(step+1,depth,W);
			w[i]-=a[step];
		}
	}
	if(cnt<tot) {
		cnt++;
		w[cnt]+=a[step];
		dfs1(step+1,depth,W);
		w[cnt]-=a[step];
		cnt--;
	}
}

bool dfs2(int step,int depth)
{
	if(step==depth+1) {
		unsigned h=Hash(w,tot);
		if((int)(upper_bound(v.begin(),v.end(),h)-lower_bound(v.begin(),v.end(),h)))
			return true;
		else return false;
	}
	for(int i=1;i<=cnt;i++) {
		if(w[i]>=a[step]) {
			w[i]-=a[step];
			if(dfs2(step+1,depth)) return true;
			w[i]+=a[step];
		}
	}
	if(cnt<tot) {
		cnt++;
		w[cnt]-=a[step];
		if(dfs2(step+1,depth)) return true;
		w[cnt]+=a[step];
		cnt--;
	}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	int i;
	while(scanf("%d",&n),n) {
		int sum=0,cmax=0; 
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]),sum+=a[i],cmax=max(cmax,a[i]);
		random_shuffle(a+1,a+n+1);
		random_shuffle(a+1,a+n+1);
		for(i=cmax;i<=sum;i++) {
			if(sum%i) continue;
			v.clear();
			tot=sum/i,cnt=0;
			
			memset(w,0,sizeof w);
			dfs1(1,n/2-1,i);
			
			sort(v.begin(),v.end());
			v.erase(unique(v.begin(),v.end()),v.end());
			fill(w+1,w+tot+1,i);
			if(dfs2(n/2,n)) {
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}

