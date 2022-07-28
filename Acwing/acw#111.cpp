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
typedef pair<int,int> PII;

const int N=1e5+5;

int n;
priority_queue<PII,vector<PII>,greater<PII> > q;
int f[N];

struct Cow
{
	int l,r,id;
}a[N];
inline bool cmp(const Cow &a,const Cow &b)
{
	return a.l<b.l;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id=i;
	}
		
	sort(a+1,a+n+1,cmp);
	
	int cnt=0;
	for(i=1;i<=n;i++) {
		if(q.empty()||q.top().first>=a[i].l) 
			f[a[i].id]=++cnt,q.push(PII(a[i].r,cnt));
		else {
			f[a[i].id]=q.top().second;
			q.pop();
			q.push(PII(a[i].r,f[a[i].id]));
		}
	}
	printf("%d\n",cnt);
	for(i=1;i<=n;i++) 
		printf("%d\n",f[i]);
	return 0;
}

