#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
struct Node
{
	Node *lc,*rc;
	int val;
	int pri;
	int size;
	Node(Node *child,const int &val,const int &size) :  lc(child) , rc(child) , val(val) ,size(size) {
		pri=rand();
		return;
	} 
	inline void update()
	{
		size = lc->size + rc->size + 1;
		return;
	}
};
Node *nul=new Node(NULL,0,0);
Node *root=nul;
Node *merge(Node *x,Node *y)
{
	if(x==nul||y==nul) 
		return (x==nul) ? y : x;
	if(x->pri > y->pri) {
		x->rc=merge(x->rc,y);
		x->update();
		return x;
	}
	else {
		y->lc=merge(x,y->lc);
		y->update();
		return y;
	}
	return nul;
}
void split(Node *now,const int &key,Node *&x,Node *&y)
{
	if(now==nul) {
		x=y=nul;
		return;
	}
	if(now->val<=key) {
		x=now;
		split(now->rc,key,x->rc,y);
	}
	else {
		y=now;
		split(now->lc,key,x,y->lc);
	}
	now->update();
	return;
}
inline void insert(const int &key) 
{
	Node *x,*y;
	split(root,key,x,y);
	root=merge(merge(x,(new Node(nul,key,1))),y);
	return;
}
inline int getnum(int rank)
{
	Node *now=root;
	while(now!=nul&&rank>0) {
		if(now->lc->size+1==rank) 
			return now->val;
		if(now->lc->size+1>rank) 
			now=now->lc;
		else rank-=now->lc->size+1,now=now->rc;
	}
	return now->val;
}
int n,cmin,cha;
int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	rint i;
	int x;
	Node *k1,*k2;
	int cnt=0;
	char c;
	scanf("%d%d",&n,&cmin);
	// 令x+cha为真实的工资 
	for(i=1;i<=n;i++) {
		for(c=getchar();c!='I'&&c!='A'&&c!='S'&&c!='F';c=getchar());
		scanf("%d",&x);
		if(c=='I') {
			if(x<cmin) continue;
			insert(x-cha);
		}
		else if(c=='A') 
			cha+=x;
		else if(c=='S') {
			cha-=x;
			split(root,cmin-cha-1,k1,k2); // x+cha<cmin ----> x<cmin-cha -----> x<=cmin-cha-1 
			cnt+=k1->size;
			root=k2;
		}
		else if(c=='F') {
			if(x>root->size) 
				puts("-1");
			else printf("%d\n",getnum(root->size-x+1)+cha);
		}
	}
	printf("%d\n",cnt);
	return 0;
}

