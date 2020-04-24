#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
using namespace std;
const int N=30000+5;
const int H=5000+5;
bool a[N];
struct data
{
	int l,r;
	int sum;
}c[H];
int cnt=0;
inline bool rule(const data &a,const data &b)
{
	return a.r<b.r;
}
int n,h;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&h);
	for(int i=1;i<=h;i++) 
		scanf("%d%d%d",&c[i].l,&c[i].r,&c[i].sum);
	sort(c+1,c+h+1,rule);
	for(int i=1;i<=h;i++) {
		for(int j=c[i].l;j<=c[i].r;j++) {
			if(a[j]) c[i].sum--;
		}
		for(int j=c[i].r;j>=c[i].l;j--) {
			if(c[i].sum<=0) break;
			if(a[j]) continue;
			a[j]=true; c[i].sum--; cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
