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

// 性质 0 : 最远点对 必然 在凸包上。 
// 性质 1 : 最远点对 必然 是对踵点对之一。
// 性质 2.1 : 过一对 对踵点对 必然可以作 一对平行线 使有一条边在平行线上。
//      2.2 : 距其中一条平行线最远的点一定是另一个对踵点。
// 性质 3 :  凸包上距离一条边最远的点具有单调性。 

typedef pair<LL,LL> PLL;
typedef PLL Point;
typedef PLL Vector;

#define x first
#define y second

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); } 
Vector operator+(Vector a,Vector b) { return Vector(a.x+b.x,a.y+b.y); } 
Vector operator*(LL a,Vector b) { return Vector(a*b.x,a*b.y); }
Vector operator/(Vector a,LL b) { return Vector(a.x/b,a.y/b); }
LL dot(Vector a,Vector b) { return a.x*b.x+a.y*b.y; }
LL cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
Vector rotate(Vector a,LL b) { return Vector(a.x*cos(b)+a.y*sin(b),-a.x*sin(b)+a.y*cos(b)); } 
LL length(Vector a) { return a.x*a.x+a.y*a.y; } 
LL dist(Point a,Point b) { return length(a-b); }

const int N=1e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int n;
Point a[N];

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	
	int i,j;
	
	scanf("%d",&n);
	for(i=0;i<n;i++) 
		scanf("%lld%lld",&a[i].x,&a[i].y);
	
	LL ans=0;
	sort(a,a+n);
	int T=min(n,10000000/n);
	
	for(i=0;i<T;i++) {
		for(j=n-1;j>i;j--)
			ans=max(ans,dist(a[i],a[j]));
	}
		
	
	cout<<ans<<endl;
	return 0;
}

