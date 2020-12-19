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

// ���� 0 : ��Զ��� ��Ȼ ��͹���ϡ� 
// ���� 1 : ��Զ��� ��Ȼ �Ƕ�����֮һ��
// ���� 2.1 : ��һ�� ������ ��Ȼ������ һ��ƽ���� ʹ��һ������ƽ�����ϡ�
//      2.2 : ������һ��ƽ������Զ�ĵ�һ������һ������㡣
// ���� 3 :  ͹���Ͼ���һ������Զ�ĵ���е����ԡ� 

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

