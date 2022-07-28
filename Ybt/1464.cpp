#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int n;
const int M=2e6+5;
const LL Mod=131313;
struct Hash
{
	int one[Mod+1],adj[Mod+1];
	int tot;
	struct node
	{
		LL data;
		int next;	
	};
	node num[M];
	inline LL hf(const LL &key)
	{
		return key%Mod+1;
	}
	inline void add(const LL &key)
	{
		tot++;
		LL t=hf(key);
		if(one[t]==0) one[t]=tot;
		else num[adj[t]].next=tot;
		adj[t]=tot;
		num[tot].data=key;
		return;
	}
	inline bool find(const LL &key)
	{
		LL t=hf(key);
		for(int i=one[t];i;i=num[i].next) 
			if(num[i].data==key) 
				return true;
		return false;
	}
	void del(int &now,const LL &key)
	{
		if(!now) return;
		if(num[now].data==key) 
		{
			num[now].data=0;
			now=num[now].next;
			return;
		}
		del(num[now].next,key);
		return;
	}
	inline int count(const LL &key)
	{
		LL t=hf(key);
		int cnt=0;
		for(int i=one[t];i;i=num[i].next)
			if(num[i].data==key) cnt++;
		return cnt;
	}
};
Hash h;
LL a[M];
int Max,cnt;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) 
	{
		if(!h.find(a[i])) cnt++,h.add(a[i]);
		else
		{
			Max=max(Max,cnt);
			for(int j=i-cnt;j<i;j++) 
			{
				if(h.find(a[i])) 
					h.del(h.one[h.hf(a[j])],a[j]),cnt--;
				else break;
			}
			cnt++;
			h.add(a[i]);
		}
		Max=max(Max,cnt);
	}
	printf("%d",Max);
	return 0;
}

