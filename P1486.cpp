#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e5+5;
struct node
{
	int lc,rc;
	int val; //工资 
	int pri;
	int size;
	int tag;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define p(x) t[x].pri
	#define s(x) t[x].size
	#define tag(x) t[x].tag
};
node t[N];
int root=0,cnt=0;
inline void update(const int &now)
{
	s(now)=s(lc(now))+s(rc(now))+1;
	return;
}
inline void push_down(const int &now) 
{
	if(tag(now)==0) return;
	if(lc(now)!=0) {
		v(lc(now))+=tag(now);
		tag(lc(now))+=tag(now);
	}
	if(rc(now)!=0) {
		v(rc(now))+=tag(now);
		tag(rc(now))+=tag(now); 
	}
	tag(now)=0;
	return;
}
void split(int now,const int &key,int &x,int &y) //<= >
{
	if(now==0) {
		x=y=0;
		return;
	}
	push_down(now);
	if(v(now)<=key) {
		x=now;
		split(rc(now),key,rc(now),y);
	}
	else {
		y=now;
		split(lc(now),key,x,lc(now));
	}
	update(now);
	return;
}
int merge(int x,int y) //x<=y
{
	if(x==0||y==0) 
		return x+y;
	if(p(x)>p(y)) {
		push_down(x);
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else {
		push_down(y);
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
	return 0;
}
inline int newnode(const int &key)
{
	cnt++;
	v(cnt)=key;
	s(cnt)=1;
	lc(cnt)=rc(cnt)=0;
	p(cnt)=rand();
	tag(cnt)=0;
	return cnt;
}
inline void insert(const int &key) 
{
	int x,y,z;
	split(root,key-1,x,y);
	root=merge(merge(x,newnode(key)),y);
	return;
}
inline int getnum(int rank)
{
	int now=root;
	while(now>0&&rank>0) {
		push_down(now);
		if(rank-s(lc(now))-1==0) 
			return v(now);
		else if(rank<s(lc(now))+1) 
			now=lc(now);
		else rank-=s(lc(now))+1,now=rc(now);
	}
	return -1;
}
//I k 新建一个工资档案，初始工资为 kk。如果某员工的初始工资低于工资下界，他将立刻离开公司。
//A k 把每位员工的工资加上 kk 。
//S k 把每位员工的工资扣除 kk。
//F k 查询第 kk 多的工资。
int pool=0,ans=0;
int n=0,bound=0;
int main()
{
//	freopen("1.in","r",stdin);
	srand((int)time(0));
	int i,j;
	char opt;
	int x,y,z;
	scanf("%d%d",&n,&bound);
	for(i=1;i<=n;i++) {
		opt=getchar();
		if(opt!='I'&&opt!='A'&&opt!='S'&&opt!='F') {
			i--;
			continue;
		}
		scanf("%d",&x);
		if(opt=='I') {
			if(x<bound) continue;
			pool++;
			insert(x);
		}
		else if(opt=='A') {
			tag(root)+=x;
			v(root)+=x;
		}
		else if(opt=='S') {
			tag(root)-=x;
			v(root)-=x;
			split(root,bound-1,z,root);
			ans+=s(z);
			pool-=s(z);
		}
		else if(opt=='F') {
			if(x>pool) printf("-1\n");
			else printf("%d\n",getnum(pool-x+1));
		}
	}
	cout<<ans;
	return 0;
}

