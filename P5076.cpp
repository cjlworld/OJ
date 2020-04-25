#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#define LL long long
using namespace std;
//查询 xx 数的排名（排名定义为比当前数小的数的个数 +1+1。若有多个相同的数，因输出最小的排名）。
//查询排名为 xx 的数。
//求 xx 的前驱（前驱定义为小于 xx，且最大的数）。
//求 xx 的后继（后继定义为大于 xx，且最小的数）。
//插入一个数 xx。
const int N=1e4+5;
struct node
{
	int lc,rc;
	int val;
	int size;
	int pri;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define s(x) t[x].size
	#define p(x) t[x].pri
}t[N];
int root,cnt;
inline int newnode(int val)
{
	cnt++;
	v(cnt)=val;
	p(cnt)=rand();
	s(cnt)=1;
	lc(cnt)=rc(cnt)=0;
	return cnt;
}
inline void update(const int &now)
{
	s(now)=s(lc(now))+s(rc(now))+1;
	return;
}
void split(int now,const int &key,int &x,int &y)
{
	if(now==0) {
		x=y=0;
		return;
	}
	if(v(now)<=key) {
		x=now;
		split(rc(now),key,rc(x),y);
	}
	else {
		y=now;
		split(lc(now),key,x,lc(y));
	}
	update(now);
	return;
}
int merge(int x,int y)
{
	if(x==0||y==0) 
		return x+y;
	if(p(x)>p(y)) {
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else {
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
inline void insert(const int &key)
{
	int x,z;
	split(root,key-1,x,z);
	root=merge(merge(x,newnode(key)),z);
	return;
}
inline int getpre(const int &key)
{
	int x,y,z;
	split(root,key-1,x,y);
	int now=x;
	while(rc(now)) 
		now=rc(now);
	z=(now!=0) ? v(now) : -0x7fffffff;
	root=merge(x,y);
	return z;
}
inline int getsuf(const int &key)
{
	int x,y,z;
	split(root,key,x,y);
	int now=y;
	while(lc(now)) 
		now=lc(now);
	z=(now!=0) ? v(now) : 0x7fffffff;
	root=merge(x,y);
	return z;
}
inline int getrank(const int &key)
{
	int x,y,z;
	split(root,key-1,x,y);
	z=s(x)+1;
	root=merge(x,y);
	return z;
}
inline int getnum(int rank)
{
	int now=root;
	while(now>0&&rank>0) {
		if(s(lc(now))+1==rank) 
			return v(now);
		if(s(lc(now))+1>rank) 
			now=lc(now);
		else rank-=s(lc(now))+1,now=rc(now);
	}
	return v(now);
}
int n;
int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	int i,j;
	int opt,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&opt,&x);
		switch(opt) {
			case 1 : printf("%d\n",getrank(x)); break;
			case 2 : {
				printf("%d\n",getnum(x));
				break;
			}
			case 3 : {
				printf("%d\n",getpre(x));
				break;
			}
			case 4 : {
				printf("%d\n",getsuf(x));
				break;
			}
			case 5 : {
				insert(x);
				break;
			}
		}
	}
	return 0;
}

