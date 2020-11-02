#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
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

const int N=6000+5;

int n,m;
int path[N],tot=0;

struct DancingLinks
{
	int l[N],r[N],u[N],d[N]; // 左右上下的指针,就按照我们平时的生活习惯来. 
	int s[N],row[N],col[N],idx; // 每列的1的数量,row[i]是节点i的行,col[i]是节点i的列,idx用于分配内存。 
	void init()
	{
		for(int i=0;i<=m;i++) {
			l[i]=i-1,r[i]=i+1;
			u[i]=d[i]=i;
		}	
		l[0]=m,r[m]=0;
		idx=m;
	}
	void add(int &hh,int &tt,int x,int y)
	{
		idx++; row[idx]=x,col[idx]=y,s[y]++;
		u[idx]=y,d[idx]=d[y],u[d[y]]=idx,d[y]=idx;
		r[hh]=l[tt]=idx,l[idx]=hh,r[idx]=tt;
		tt=idx;
	}
	void remove(int p) // 删除列p,同时有p的行也不能再选了,也删除。 
	{
		int i,j;
		l[r[p]]=l[p],r[l[p]]=r[p];
		for(i=d[p];i!=p;i=d[i]) 
			for(j=r[i];j!=i;j=r[j]) {
				s[col[j]]--;
				u[d[j]]=u[j],d[u[j]]=d[j];
			}
	}
	void resume(int p)
	{
		int i,j;
		for(i=u[p];i!=p;i=u[i]) 
			for(j=l[i];j!=i;j=l[j]) {
				u[d[j]]=d[u[j]]=j;
				s[col[j]]++;
			}
		l[r[p]]=r[l[p]]=p;
	}
	bool dance()
	{
		if(!r[0]) return true;
		int i,j,p=r[0];
		for(i=r[p];i;i=r[i]) 
			if(s[i]<=s[p]) p=i;
		remove(p);
		for(i=d[p];i!=p;i=d[i]) {
			path[++tot]=row[i];
			for(j=r[i];j!=i;j=r[j]) remove(col[j]);
			if(dance()) return true;
			for(j=l[i];j!=i;j=l[j]) resume(col[j]); 
			tot--;
		}
		resume(p);
		return false;
	}
}D;


int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x;
	scanf("%d%d",&n,&m);
	D.init();
	for(i=1;i<=n;i++) {
		int hh=D.idx+1,tt=D.idx+1;
		for(j=1;j<=m;j++) {
			scanf("%d",&x);
			if(x) D.add(hh,tt,i,j);
		}
	}
//	for(i=0;i<=D.idx;i++) 
//		printf("%d %d %d %d\n",D.l[i],D.r[i],D.u[i],D.d[i]);
	if(D.dance()) {
		for(i=1;i<=tot;i++)
			printf("%d ",path[i]);
		printf("\n");
	}
	else printf("No Solution!\n");
	return 0;
}

