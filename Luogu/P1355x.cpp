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
typedef pair<LL,LL> PLL;
typedef PLL Point;
typedef PLL Vector;

#define x first
#define y second

inline Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
inline LL cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
inline LL dot(Vector a,Vector b) { return a.x*b.x+a.y*b.y; }

inline int sign(LL x) 
{
	if(x==0) return 0;
	else if(x>0) return 1;
	else return -1;
}

Point a,b,c,d;

inline bool OnSeg(Point a,Point b,Point c) // a �Ƿ��� b,c �� 
{
	return (!cross(a-b,c-b) && dot(a-b,a-c)<=0);
}

int main()
{
//	freopen("1.in","r",stdin);
	char ch;
	
	cin>>ch>>a.x>>ch>>a.y>>ch;
	cin>>ch>>b.x>>ch>>b.y>>ch;
	cin>>ch>>c.x>>ch>>c.y>>ch;
	
	cin>>ch>>d.x>>ch>>d.y>>ch;
	
	if(  (d.x==a.x&&d.y==a.y) 
		|| (d.x==b.x&&d.y==b.y) 
		|| (d.x==c.x&&d.y==c.y) )
			printf("4\n");
	
	else if(OnSeg(d,a,b)||OnSeg(d,b,c)||OnSeg(d,a,c))
			printf("3\n");
	
	else if(sign(cross(a-b,c-b))==sign(cross(a-b,d-b)) // d �� c �� ab ��ͬһ�� 
		&& sign(cross(a-c,b-c))==sign(cross(a-c,d-c)) // d �� b �� ac ��ͬһ�� 
		&& sign(cross(c-b,a-b))==sign(cross(c-b,d-b)) ) // d �� a �� bc ��ͬһ�� 
			printf("1\n");
	
	else printf("2\n");
	
	return 0;
}

