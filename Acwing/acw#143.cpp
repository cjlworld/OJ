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

const int N=32*1e5+5;

struct Trie
{
	int ch[N][2],cnt[N],idx;
	vector<int> v;
	void get(int x)
	{
		v.clear();
		for(int i=0;i<31;i++) 
			v.push_back(x&1),x>>=1;
		reverse(v.begin(),v.end());
//		for(int i=0;i<31;i++) 
//			printf("%d",v[i]);
//		printf("\n");
	}
	void insert(int x)
	{
		get(x);
		int i,now=0;
		for(i=0;i<31;i++) {
			cnt[now]++;
			if(!ch[now][v[i]]) ch[now][v[i]]=++idx;
			now=ch[now][v[i]];
		}
		cnt[now]++;
	}
	int query(int x)
	{
		get(x);
		int i,now=0,res=0;
		for(i=0;i<31;i++) {
			if(ch[now][v[i]^1]&&cnt[ch[now][v[i]^1]]) 
				now=ch[now][v[i]^1],res^=(v[i]^1)<<(30-i);
			else now=ch[now][v[i]],res^=v[i]<<(30-i);
		}
		return res;
	}
}T;

int n;
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int ans=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		T.insert(a[i]);
	}
	for(i=1;i<=n;i++) 
		ans=max(ans,T.query(a[i])^a[i]);
	cout<<ans<<endl;
	return 0;
}

