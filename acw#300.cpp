#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
const int N=5000+5;

int f[N];
int sc[N],st[N],t[N],c[N];
int n,S;
int main()
{
    int i,j;
    int x,y,z;
    scanf("%d%d",&n,&S);
    for(i=1;i<=n;i++) {
        scanf("%d%d",&t[i],&c[i]);
        sc[i]=sc[i-1]+c[i];
        st[i]=st[i-1]+t[i];
    }
    memset(f,0x3f,sizeof f);
    f[0]=0;
    for(i=1;i<=n;i++) 
        for(j=0;j<=i-1;j++) 
            f[i]=min(f[i],f[j]+(sc[n]-sc[j])*S+(sc[i]-sc[j])*st[i]);
    cout<<f[n];
    return 0;
}
