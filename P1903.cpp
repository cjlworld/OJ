#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
#define rint register int 
#define ris register
template<class T>
inline void read(T &x)
{
	x=0;
	ris char c;
	ris bool sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c-'0');
	if(sign) x=~x+1;
	return;
}
short bcc[22];
int top=0;
template<class T>
inline void print(T x)
{
	top=0;
	if(!x) {
		putchar('0');
		return;
	}
	if(x<0) putchar('-'),x=~x+1;
	while(x) {
		bcc[++top]=x%10;
		x=x/10;
	}
	for(;top>=1;--top) 
		putchar(48+bcc[top]);
	return;
}
const int N=133333+5;
const int M=1e6+5;
int n,m;
int a[N];
int c[M];
int ago[N];
int ans=0;
struct quiz
{
	int l,r;
	int ans;
	int o;
	int Tim;
}Q[N],R[N];
int Qtot=0,Rtot=0,siz;
inline bool cmp(const quiz &a,const quiz &b)
{
	if(a.l/siz!=b.l/siz) 
		return a.l<b.l;
	if(a.r/siz!=b.r/siz) 
		return a.r<b.r;
	return a.Tim<b.Tim;	return (a.r/siz&1) ? a.Tim<b.Tim : a.Tim>b.Tim;
}
inline bool rule(const quiz &a,const quiz &b)
{
	return a.o<b.o;
}
inline void Add(const int &pos)
{
	if(c[a[pos]]==0) ans++;
	c[a[pos]]++;
	return;
}
inline void Sub(const int &pos)
{
	if(c[a[pos]]==1) ans--;
	c[a[pos]]--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	rint x,y,z;
	ris char opt;
	read<int>(n); read<int>(m);
	for(i=1;i<=n;i++) 
		read<int>(a[i]);
	for(i=1;i<=n;i++) 
		ago[i]=a[i];
	for(i=1;i<=m;i++) {
		for(opt=getchar();opt!='R'&&opt!='Q';opt=getchar());
		if(opt=='R') {
			Rtot++;
			read(R[Rtot].l); read(R[Rtot].r);
			R[Rtot].Tim=ago[R[Rtot].l];
			R[Rtot].o=i;
			ago[R[Rtot].l]=R[Rtot].r;
		}
		else {
			Qtot++;
			read(Q[Qtot].l); read(Q[Qtot].r);
			Q[Qtot].Tim=Rtot;
			Q[Qtot].o=i;
		}
	}
	siz=pow(n+Qtot,0.66666666);
	sort(Q+1,Q+Qtot+1,cmp);
	rint head=1,tail=0,times=0;
	for(i=1;i<=Qtot;++i) {
		while(times<Q[i].Tim) {
			++times;
			if(R[times].l>=head&&R[times].l<=tail) {
				Sub(R[times].l);
				a[R[times].l]=R[times].r;
				Add(R[times].l);
			}
			else a[R[times].l]=R[times].r;
		}
		while(times>Q[i].Tim) {
			if(R[times].l>=head&&R[times].l<=tail) {
				Sub(R[times].l);
				a[R[times].l]=R[times].Tim;
				Add(R[times].l);
			}
			else a[R[times].l]=R[times].Tim;
			--times;
		}
		while(head>Q[i].l) Add(--head);
		while(tail<Q[i].r) Add(++tail);
		while(head<Q[i].l) Sub(head++);
		while(tail>Q[i].r) Sub(tail--);
		Q[i].ans=ans;
	}
	sort(Q+1,Q+Qtot+1,rule);
	for(i=1;i<=Qtot;i++) 
		print(Q[i].ans),putchar('\n');
	return 0;
}
