#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	char c;
	bool sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		sign=(c=='-') ? true : sign;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	x=(sign) ? (~x+1) : x;
	return;
}
struct Node
{
	Node *lc,*rc;
	int val;
	int size;
	int pri;
	Node(int value)   {
		val=value;
		size=1;
		pri=rand();
		lc=rc=NULL;
		return;
	}
};
Node *root,*p;
Node *x,*y,*z;
#define siz(x) ((x==NULL) ? 0 : x->size)
#define update(x) x->size=siz(x->lc)+siz(x->rc)+1
#define newnode(key) (new Node(key))
void split(Node *now,const int &key,Node *&x,Node *&y)
{
	if(now==NULL) {
		x=y=NULL;
		return;
	}
	if( now->val <= key ) {
		x=now;
		split(now->rc,key,now->rc,y);
	}
	else {
		y=now;
		split(now->lc,key,x,now->lc);
	}
	update(now);
	return;
}
Node* merge(Node *x,Node *y)
{
	if(x==NULL||y==NULL) 
		return (x==NULL) ? y : x;
	if(x->pri > y->pri) {
		x->rc =merge(x->rc , y);
		update(x);
		return x;
	}
	else {
		y->lc =merge(x , y->lc);
		update(y);
		return y;
	}
	return 0;
}
inline void insert(const int &key)
{
	split(root,key-1,x,z);
	root=merge(merge(x,newnode(key)),z);
	return;
}
inline void erase(const int &key)
{
	split(root,key-1,x,z);
	split(z,key,y,z);
	z=merge(merge(y->lc,y->rc),z);
	root=merge(x,z);
	delete y;
	return;
}
inline int getpre(const int &key)
{
	split(root,key-1,x,y);
	Node* now=x;
	while(now->rc!=NULL) 
		now=now->rc;
	root=merge(x,y);
	return now->val;
}
inline int getsuf(const int &key)
{
	split(root,key,x,y);
	Node* now=y;
	while(now->lc!=NULL) 
		now=now->lc;
	root=merge(x,y);
	return now->val;
}
inline int getrank(const int &key)
{
	split(root,key-1,x,y);
	int tmp=siz(x)+1;
	root=merge(x,y);
	return tmp;
}
inline int getnum(int rank)
{
	Node *now=root;
	while(now!=NULL&&rank>0) {
		if(siz(now->lc)+1==rank) 
			return now->val;
		if(siz(now->lc)+1>rank) 
			now=now->lc;
		else rank-=siz(now->lc)+1,now=now->rc;
	}
	return now->val;
}
int n,m;
/*插入一个整数 xx。
删除一个整数 xx（若有多个相同的数，只删除一个）。
查询整数 xx 的排名（排名定义为比当前数小的数的个数 +1+1）。
查询排名为 xx 的数。
求 xx 的前驱（前驱定义为小于 xx，且最大的数）。
求 xx 的后继（后继定义为大于 xx，且最小的数）。*/
#define rint register int 
int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	rint i;
	rint opt,x;
	rint last=0;
	rint ans=0;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(x); 
		insert(x);	
	}
	for(i=1;i<=m;i++) {
		read(opt); read(x);
		x=x^last;
		switch(opt) {
			case 1 : insert(x); break;
			case 2 : erase(x); break;
			case 3 : last=getrank(x); break;
			case 4 : last=getnum(x); break;
			case 5 : last=getpre(x); break;
			case 6 : last=getsuf(x); break;
		}
		if(opt>=3&&opt<=6) 
			ans^=last;
	}
	cout<<ans;
	return 0;
}

