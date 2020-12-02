#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const double eps=1e-7;
int n,m;
double a[N];
double c[N],cmin[N];

bool check(double t)
{
    memcpy(c,a,sizeof c);
    memset(cmin,0,sizeof cmin);
    int i;
    for(i=1;i<=n;i++) c[i]-=t;
    for(i=1;i<=n;i++) c[i]+=c[i-1];
    for(i=1;i<=n;i++) cmin[i]=min(cmin[i-1],c[i]);
	for(i=m;i<=n;i++) 
		if(c[i]-cmin[i-m]>=0) return true;
    return false;
}
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    cin>>n>>m;
    for(i=1;i<=n;i++) 
        scanf("%lf",&a[i]);
    
    double L=0.0,R=10000000.0,mid;
    while(L+eps<R) {
        mid=(L+R)/2.0;
        if(check(mid)) L=mid;
        else R=mid;
    }
    printf("%d",(int)floor(R*1000.0));
    if(check(R)) printf("\ncheck R!!!");
    return 0;
}

