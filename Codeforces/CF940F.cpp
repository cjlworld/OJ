#include<map>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=6e5+5;

int n,m,mc,mq,siz;

struct Query
{
	int l,r;
	int id,tim;
	inline bool operator<(const Query &t) const
	{
		if(l/siz!=t.l/siz) return l<t.l;
		else if(r/siz!=t.r/siz) return r<t.r;
		else return tim<t.tim;
	}
}q[N];

struct Range
{
	int pos,key;
}c[N];

int cnt[N],ans[N];
int a[N];
int exist[N];

inline void Add(int v)
{
	exist[cnt[v]]--;
	cnt[v]++;
	exist[cnt[v]]++;
}

inline void Sub(int v)
{
	exist[cnt[v]]--;
	cnt[v]--;
	exist[cnt[v]]++;
}

inline void travel(int i,int tim)
{
	if(c[tim].pos>=q[i].l && c[tim].pos<=q[i].r) 
		Add(c[tim].key),Sub(a[c[tim].pos]);
	swap(a[c[tim].pos],c[tim].key);
}

vector<int> nums;
inline int getnw(int x) 
{ 
	return (upper_bound(nums.begin(),nums.end(),x)-nums.begin()); 
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,opt;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	for(i=1;i<=m;i++) {
		scanf("%d",&opt);
		if(opt==1) {
			mq++;
			scanf("%d%d",&q[mq].l,&q[mq].r);
			q[mq].id=mq; q[mq].tim=mc; // �� mc ���޸ĺ� 
		}
		else {
			mc++;
			scanf("%d%d",&c[mc].pos,&c[mc].key);
			nums.push_back(c[mc].key);
		}
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) a[i]=getnw(a[i]);
	for(i=1;i<=mc;i++) c[i].key=getnw(c[i].key);
	
	siz=cbrt(1.0*n*mc)+1;
	sort(q+1,q+mq+1);
	
	int hh=1,tt=0,tim=0;
	for(i=1;i<=mq;i++) {
		while(hh>q[i].l) Add(a[--hh]);
		while(tt<q[i].r) Add(a[++tt]);
		while(hh<q[i].l) Sub(a[hh++]);
		while(tt>q[i].r) Sub(a[tt--]);
		
		while(tim<q[i].tim) travel(i,++tim);
		while(tim>q[i].tim) travel(i,tim--);
		
		for(j=1;j<N;j++) 
			if(!exist[j]) {
				ans[q[i].id]=j;
				break;
			}
	}
	
	for(i=1;i<=mq;i++) 
		printf("%d\n",ans[i]);
	return 0;
}

/* 
DeBug
1. swap
2. sum[] ά������ֵ�����г��ֹ��� ֵ �ĸ���������ά��������
3. ����ѯ�ʵ� x ҲҪ��ɢ���������ܵ�ֵ�ĸ������� > n; ����<n+q; 
4. ���ڱ���ɨ�ĸ��Ӷ��ǶԵģ���Ȩֵ�ֿ�ĵ��ˡ� 
*/
