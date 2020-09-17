// Acwing.1063 ÓÀÎŞÏç 
#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

const int N=100000+5;

struct Node
{
    int lc,rc;
    int sum;
    int id;
    void clear()
    {
    	lc=rc=sum=id=0;
    	return;
	}
}t[20*N];
int idx=0,root[N];
int del[20*N],top=0;
int GetNode()
{
	if(top>=1) return del[top--];
	else return ++idx; 
}
void insert(int &now,int key,int id,int l,int r)
{
    if(!now) t[now=GetNode()].clear();
    t[now].sum++;
    if(l==r) {
    	t[now].id=id;
    	return;
	}
    int mid=(l+r)>>1;
    if(key<=mid) insert(t[now].lc,key,id,l,mid);
    else insert(t[now].rc,key,id,mid+1,r);
    return;
}
int merge(int x,int y)
{
    if(!x||!y) return x+y;
    t[x].sum+=t[y].sum;
    t[x].lc=merge(t[x].lc,t[y].lc);
    t[x].rc=merge(t[x].rc,t[y].rc);
    del[++top]=y;
    return x;
}
int getid(int now,int rank,int l,int r)
{
	if(l==r) return t[now].id;
	int tmp=t[t[now].lc].sum,mid=(l+r)>>1;
	if(tmp>=rank) 
		return getid(t[now].lc,rank,l,mid);
	else return getid(t[now].rc,rank-tmp,mid+1,r);
}
//=========================================================
int par[N];
int Find(const int &x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
inline void Join(int x,int y)
{
	x=Find(x),y=Find(y);
	if(x==y) return;
	par[x]=y;
	root[y]=merge(root[x],root[y]);
	return;
}
//============================================
int n,m,q;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	char opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n+2;i++) par[i]=i;
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		insert(root[i],x,i,1,n);
	}
	while(m--) {
		scanf("%d%d",&x,&y);
		Join(x,y);
	}
	scanf("%d",&q);
	while(q--) {
		for(opt=getchar();opt!='B'&&opt!='Q';opt=getchar());
		scanf("%d%d",&x,&y);
		if(opt=='Q') {
			if(t[root[Find(x)]].sum<y) 
				printf("-1\n");
			else printf("%d\n",getid(root[Find(x)],y,1,n));
		}
		else Join(x,y);
	}
	return 0;
}
