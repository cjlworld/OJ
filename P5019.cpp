#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],c[N];
int n;
int main()
{
    int i;
    int x=0,y=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++) {
        c[i]=a[i]-a[i-1];
        if(c[i]>0) x+=c[i];
        else y-=c[i];
    }
    cout<<max(y,x);
    return 0;
}
