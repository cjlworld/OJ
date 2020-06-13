#include<set>
#include<stack>
#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
namespace FastIO
{
char c;
bool sign;
template<class T>
inline void read(T &x)
{
	x=0;
	sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c&15);
	if(sign) x=~x+1;
	return;
}
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
}
using FastIO::read;
using FastIO::print;
//===================================================
const int N=2e4+5;
const int M=1e5+5;
int one[N];
int ver[2*M],Next[2*M];
int tot=0;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//===================================================
int dfn[N],low[N],times=0;
// as for not root
// low[v]>=dfn[now]  ---------> now is a required node
// low[v]<dfn[now] -----------> it isn't

// root 
// have more than one child 

// why divide it into root and not root ?
// if low[v]>=dfn[now] then cut now  -----> cause ---> v can not find a way to now's father
// but if now is a root ( now doesn't have a father ) ----> so we only need to think about now's kids
// and now's kids (now not root) only all of the low[v] < dfn[now] ---> now is not a cut
// and at that time , each v can find a way to another v (already cut now) , 
// so only think about child and father , ( not root );
  
set<int> cut;
void tarjan(int now,const int &fa)
{
	dfn[now]=low[now]=++times;
	rint i,v,child=0;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(!dfn[v]) {
			child++;
			tarjan(v,now);
			if((fa==0&&child>1)||(fa!=0&&low[v]>=dfn[now])) 
				cut.insert(now);
			low[now]=min(low[now],low[v]);
		}
		else //if(v!=fa) // 割点并不需要这句，但是指向father的low确实没有意义。（指向father的祖先才有意义）。 但桥要。 
			low[now]=min(low[now],dfn[v]);
	}
	return;  
}
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(i=1;i<=n;i++) 
		if(!dfn[i]) 
			tarjan(i,0);
	print(cut.size()),putchar('\n');
	for(set<int>::iterator it=cut.begin();it!=cut.end();it++) 
		print(*it),putchar(' ');
	return 0;
}

