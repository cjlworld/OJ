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

int q[N],tt;
bool used[N];

void Andrew()
{
    int i;
    sort(a,a+n);
    for(i=0;i<n;i++) {
        while(tt>=2 && cross(a[q[tt]]-a[q[tt-1]],a[i]-a[q[tt-1]])>=0) tt--;
        q[++tt]=i;
    }
    for(i=2;i<=tt;i++) used[q[i]]=true;
    for(i=n-1;i>=0;i--) {
        if(used[i]) continue;
        while(tt>=2 && cross(a[q[tt]]-a[q[tt-1]],a[i]-a[q[tt-1]])>=0) tt--;
        q[++tt]=i;
    }
}

inline LL mabs(LL x) { return ((x>0) ? x : -x); }
LL RC()
{
    int i,j;
    Point d,e;
    LL res=0;
    if(tt<=2) return res=dist(a[0],a[n-1]); 
    for(i=1,j=3;i<tt;i++) {
        d=a[q[i]],e=a[q[i+1]];
        while(mabs(cross(e-d,a[q[j+1]]-d))>mabs(cross(e-d,a[q[j]]-d))) {
            j++;
            if(j==tt) j=1;
        }
        res=max(res,dist(a[q[j]],d)); 
        res=max(res,dist(a[q[j]],e)); 
    }
    return res;
}

int main()
{
//  freopen("1.in","r",stdin);
    int i;

    scanf("%d",&n);
    for(i=0;i<n;i++) 
        scanf("%lld%lld",&a[i].x,&a[i].y);

    Andrew();
    cout<<RC()<<endl;

    return 0;
}

