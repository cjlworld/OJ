#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=2e5+5;
int n,m;
int a[N];
vector<int> v;
struct Node
{
	int lc,rc;
	int size;
}hjt[40*N];
int pool=0;
int root[N];
void insert(int &now,const int &pre,const int &key,const int &x,const int &y)
{
	hjt[now=++pool]=hjt[pre];
	hjt[now].size++;
	if(x==y) return;
	int mid=(x+y)>>1;
	if(key<=mid) insert(hjt[now].lc,hjt[pre].lc,key,x,mid);
	else insert(hjt[now].rc,hjt[pre].rc,key,mid+1,y);
	return;
}
int findkth(const int &L,const int &R,const int &rank,const int &x,const int &y) //(L,R]
{
	if(x==y) return x;
	int tmp=hjt[hjt[R].lc].size-hjt[hjt[L].lc].size;
	int mid=(x+y)>>1;
	if(rank<=tmp) return findkth(hjt[L].lc,hjt[R].lc,rank,x,mid);
	else return findkth(hjt[L].rc,hjt[R].rc,rank-tmp,mid+1,y);
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) 
		a[i]=(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
	for(i=1;i<=n;i++) 
		insert(root[i],root[i-1],a[i],1,v.size());
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		printf("%d\n",v[findkth(root[x-1],root[y],z,1,v.size())-1]);
	}
	return 0;
}

