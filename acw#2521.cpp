#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=133333+5,M=1e6+5;

int n,m,mq,mc;
int a[N];

int siz;

struct quiz
{
    int l,r;
    int o,t; // 第几次询问，询问的时间戳。 
}q[N];
inline bool cmp(const quiz &a,const quiz &b)
{
    if(a.l/siz!=b.l/siz) return a.l<b.l;
    else if(a.r/siz!=b.r/siz) return a.r<b.r;
    else return (a.r/siz&1)^(a.t>b.t);
}

struct Range
{
	int pos,key; // 把 pos 位置上的数替换成 key。 
}c[N];

int ans; // 保存当前区间内颜色的数目。 
int Ans[N],cnt[M]; // 按询问先后的ANS 和 值域 
inline void Add(int key)
{
	if(cnt[key]==0) ans++;
	cnt[key]++;
}
inline void Sub(int key)
{
	cnt[key]--;
	if(cnt[key]==0) ans--;
}

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    char opt[2];
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    for(i=1;i<=m;i++) {
        scanf("%s",opt);
        if(*opt=='R') {
            mc++; // 修改的编号，也就是时间戳。 
            scanf("%d%d",&c[mc].pos,&c[mc].key);
        }
        else {
            mq++;
            scanf("%d%d",&q[mq].l,&q[mq].r);
            q[mq].t=mc,q[mq].o=mq; 
			// 时间q[i].t 表示询问是第 q[i].t 次修改后 , q[i].t+1 次修改前发生的。 
        }
    }
    
    siz=cbrt(n*mc+1);
    sort(q+1,q+mq+1,cmp);
    
    int hh=1,tt=0,tim=0; 
	// hh,tt 表示当前值域维护的区间的左端点和右端点。[hh,tt];
	// tim 是当前的时间戳，表示当前的序列是第 tim 次修改后的。 
    for(i=1;i<=mq;i++) {
        while(hh>q[i].l) Add(a[--hh]);
        while(tt<q[i].r) Add(a[++tt]);
        while(hh<q[i].l) Sub(a[hh++]);
        while(tt>q[i].r) Sub(a[tt--]);
        while(tim>q[i].t) {
        	if(c[tim].pos>=hh&&c[tim].pos<=tt) 
				Sub(a[c[tim].pos]),Add(c[tim].key);
			swap(c[tim].key,a[c[tim].pos]); // 用于恢复数据，很精妙的一个操作 
			// 时间戳回来的时候会将 a[pos] 改为 修改前原来的数  
			// 认真想一想。 
			tim--;
		}
        while(tim<q[i].t) {
        	tim++;
        	if(c[tim].pos>=hh&&c[tim].pos<=tt) 
				Sub(a[c[tim].pos]),Add(c[tim].key);
			swap(c[tim].key,a[c[tim].pos]);  // 同上 
		}
        Ans[q[i].o]=ans;
    }
    
    for(i=1;i<=mq;i++) 
        printf("%d\n",Ans[i]);
    return 0;
}
