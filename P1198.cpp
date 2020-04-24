#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
//===========================================================
namespace FastIO
{
inline void read(char &c)
{
	c=getchar();
	while(c!='Q'&&c!='A') 
		c=getchar();
	return;
}
template<class T>
inline void rd(T &x)
{
	char c=getchar();
	bool sign=false;
	x=0;
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
}
#define read(x) FastIO::read(x)
#define rd(x) FastIO::rd(x)

/*
接下来 m 行，每一行表示一个操作。
如果该行的内容是 Q L，则表示这个操作是询问序列中最后 L 个数的最大数是多少；
如果是 A t，则表示向序列后面加一个数，加入的数是 (t+a)modp。
其中，t 是输入的参数，a 是在这个添加操作之前最后一个询问操作的答案
（如果之前没有询问操作，则 a=0）。
*/

const int M=2e5+5;
int P;
int m;
//===========================================================
namespace SGtree
{
const int M=2e5+5;
struct node
{
	int l,r;
	LL Max;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define Max(x) t[x].Max
};
node t[4*M];
#define lc (now<<1)
#define rc (now<<1|1)
void Build(int now,int l,int r)
{
	l(now)=l;
	r(now)=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	return;
}
void update(int now,int x,int y)
{
	if(x<l(now)||x>r(now)) 
		return;
	if(l(now)==r(now)&&x==l(now)) {
		Max(now)=y;
		return;
	}
	update(lc,x,y);
	update(rc,x,y);
	Max(now)=max(Max(lc),Max(rc));
	return;
}
LL query(int now,int x,int y)
{
	if(y<l(now)||x>r(now)) 
		return 0;
	if(x<=l(now)&&y>=r(now)) 
		return Max(now);
	LL a,b,res;
	a=query(lc,x,y);
	b=query(rc,x,y);
	res=max(a,b);
	return res;
}
}
int cnt;
LL ago;
//===========================================================
int main()
{
	rd(m); rd(P);
	int i,j;
	char opt;
	LL x,y,z;
	int ans=0;
	SGtree::Build(1,1,m);
	while(m--) {
		read(opt);
		rd(x);
		if(opt=='Q') {
			ago=SGtree::query(1,cnt-x+1,cnt);
			printf("%lld\n",ago);
		}
		else {
			cnt++;
			SGtree::update(1,cnt,(x+ago)%P);
		}
	}
	return 0;
}
