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
typedef pair<double,double> PDD;
typedef PDD Point;
typedef PDD Vector;

#define x first
#define y second

const double eps=1e-8,PI=acos(-1);

int cmp(double x,double y)
{
    if(fabs(x-y)<eps) return 0;
    else if(x>y) return 1;
    else return -1;
}
int sign(double x) { return cmp(x,0); } 

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); } 
Vector operator+(Vector a,Vector b) { return Vector(a.x+b.x,a.y+b.y); }
double dot(Vector a,Vector b) { return a.x*b.x+a.y*b.y; }
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
Vector rotate(Vector a,double b) { return Vector(a.x*cos(b)+a.y*sin(b),-a.x*sin(b)+a.y*cos(b)); }
double get_length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }

const int N=1e5+5;
const int dx[]={-1,1,-1,1},dy[]={1,1,-1,-1};

int n;
double la,lb,r;
int cnt;
Point a[N];

int stk[N],tt;
bool used[N];

double Andrew()
{
    sort(a+1,a+cnt+1);
    int i;
    for(i=1;i<=cnt;i++) {
        while(tt>=2 && cross(a[i]-a[stk[tt-1]],a[stk[tt]]-a[stk[tt-1]])<=0)
            used[stk[tt--]]=false;
        stk[++tt]=i;
        used[i]=true;
    }
    used[1]=false;
    for(i=cnt;i>=1;i--) {
        if(used[i]) continue;
        while(tt>=2 && cross(a[i]-a[stk[tt-1]],a[stk[tt]]-a[stk[tt-1]])<=0)
            tt--;
        stk[++tt]=i;
    }
    double res=0;
    for(i=2;i<=tt;i++) 
        res+=get_length(a[stk[i]]-a[stk[i-1]]);
    return res;
}

int main()
{
//  freopen("1.in","r",stdin);
    int i,j;
    double x,y,z;

    cin>>n;
    cin>>la>>lb>>r;
    la/=2,lb/=2;


    for(i=1;i<=n;i++) {
        cin>>x>>y>>z;
        for(j=0;j<4;j++) 
            a[++cnt]=rotate(Vector(dx[j]*lb-dx[j]*r,dy[j]*la-dy[j]*r),-z)+Vector(x,y);
    }
    printf("%.2lf",Andrew()+2*PI*r);
    return 0;
}

