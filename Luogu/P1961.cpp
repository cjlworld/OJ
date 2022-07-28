#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N=1000+5;
int n;
struct node
{
	LL a,b;
	int lc,rc;
	#define lc(x) t[x].lc 
	#define rc(x) t[x].rc 
	#define a(x) t[x].a 
	#define b(x) t[x].b 
};
node t[N];
LL f[N]; 
int cnt;
int root;
void find(int now)
{
	if(!now) return;
	cnt++;
	find(lc(now));
	find(rc(now));
	return;
}
LL gcd(LL a,LL b)
{
	if(b==0) 
		return a;
	return gcd(b,a%b);
}
LL lcm(LL a,LL b)
{
	return a*b/gcd(a,b);
}
void Dp(int now)
{
	if(!now) return;
	Dp(lc(now));
	Dp(rc(now));
	if(f[lc(now)]==0&&f[rc(now)]==0) {
		f[now]=a(now)+b(now);
		return;
	}
	int x,y;
	if(f[lc(now)]==0) {
		x=lcm(a(now),b(now)*f[rc(now)]);
		f[now]=x/a(now)+x/b(now);
		return;
	}
	if(f[rc(now)]==0) {
		x=lcm(a(now)*f[lc(now)],b(now));
		f[now]=x/a(now)+x/b(now);
		return;
	}
	x=lcm(a(now)*f[lc(now)],b(now)*f[rc(now)]);
	f[now]=x/a(now)+x/b(now);
	return;
}
int main()
{
 	cin>>n;
 	int x;
 	for(int i=1;i<=n;i++) {
 		scanf("%lld%lld%d%d",&t[i].a,&t[i].b,&t[i].lc,&t[i].rc);	
 		x=gcd(a(i),b(i));
 		a(i)=a(i)/x;
 		b(i)=b(i)/x;
	}	
	for(int i=1;i<=n;i++) {
		cnt=0;
		find(i);
		if(cnt==n) { root=i; break; } 
	}
	Dp(root);
	printf("%lld",f[root]);
	return 0;
}


