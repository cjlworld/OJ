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
    int o,t; // �ڼ���ѯ�ʣ�ѯ�ʵ�ʱ����� 
}q[N];
inline bool cmp(const quiz &a,const quiz &b)
{
    if(a.l/siz!=b.l/siz) return a.l<b.l;
    else if(a.r/siz!=b.r/siz) return a.r<b.r;
    else return (a.r/siz&1)^(a.t>b.t);
}

struct Range
{
	int pos,key; // �� pos λ���ϵ����滻�� key�� 
}c[N];

int ans; // ���浱ǰ��������ɫ����Ŀ�� 
int Ans[N],cnt[M]; // ��ѯ���Ⱥ��ANS �� ֵ�� 
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
            mc++; // �޸ĵı�ţ�Ҳ����ʱ����� 
            scanf("%d%d",&c[mc].pos,&c[mc].key);
        }
        else {
            mq++;
            scanf("%d%d",&q[mq].l,&q[mq].r);
            q[mq].t=mc,q[mq].o=mq; 
			// ʱ��q[i].t ��ʾѯ���ǵ� q[i].t ���޸ĺ� , q[i].t+1 ���޸�ǰ�����ġ� 
        }
    }
    
    siz=cbrt(n*mc+1);
    sort(q+1,q+mq+1,cmp);
    
    int hh=1,tt=0,tim=0; 
	// hh,tt ��ʾ��ǰֵ��ά�����������˵���Ҷ˵㡣[hh,tt];
	// tim �ǵ�ǰ��ʱ�������ʾ��ǰ�������ǵ� tim ���޸ĺ�ġ� 
    for(i=1;i<=mq;i++) {
        while(hh>q[i].l) Add(a[--hh]);
        while(tt<q[i].r) Add(a[++tt]);
        while(hh<q[i].l) Sub(a[hh++]);
        while(tt>q[i].r) Sub(a[tt--]);
        while(tim>q[i].t) {
        	if(c[tim].pos>=hh&&c[tim].pos<=tt) 
				Sub(a[c[tim].pos]),Add(c[tim].key);
			swap(c[tim].key,a[c[tim].pos]); // ���ڻָ����ݣ��ܾ����һ������ 
			// ʱ���������ʱ��Ὣ a[pos] ��Ϊ �޸�ǰԭ������  
			// ������һ�롣 
			tim--;
		}
        while(tim<q[i].t) {
        	tim++;
        	if(c[tim].pos>=hh&&c[tim].pos<=tt) 
				Sub(a[c[tim].pos]),Add(c[tim].key);
			swap(c[tim].key,a[c[tim].pos]);  // ͬ�� 
		}
        Ans[q[i].o]=ans;
    }
    
    for(i=1;i<=mq;i++) 
        printf("%d\n",Ans[i]);
    return 0;
}
