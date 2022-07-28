#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=4000+5,INF=0x3f3f3f3f;

int n,m;
int a[N];
int f[N][3],g[N][3];

inline void relax(int &a,const int &b) { a=((a>b) ? a : b); }

int main()
{
    int i,j;
    int x,y,z;
    cin>>n>>m;
    for(i=1;i<=n;i++) cin>>a[i];

    memset(f,-0x3f,sizeof f);
    f[0][0]=0;

    for(i=1;i<=n;i++) {
        memcpy(g,f,sizeof g);
        memset(f,-0x3f,sizeof f);

        for(j=0;j<=m;j++) {
            relax(f[j][0],g[j][0]);
            relax(f[j][0],g[j][1]);
            relax(f[j][0],g[j][2]);

            if(j==0) continue;
            relax(f[j][1],g[j-1][0]);
            relax(f[j][2],g[j-1][1]+a[i]);
            relax(f[j][2],g[j-1][2]+a[i]);
        }
    }

    int ans=-INF;
    relax(ans,f[m][0]);
    relax(ans,f[m][1]);
    relax(ans,f[m][2]);

    // 强制 1 在睡 , n 在睡或者在休息。

    memset(f,-0x3f,sizeof f);
    f[1][2]=a[1];

    for(i=2;i<=n;i++) {
        memcpy(g,f,sizeof g);
        memset(f,-0x3f,sizeof f);

        for(j=0;j<=m;j++) {
            relax(f[j][0],g[j][0]);
            relax(f[j][0],g[j][1]);
            relax(f[j][0],g[j][2]);

            if(j==0) continue;
            relax(f[j][1],g[j-1][0]);
            relax(f[j][2],g[j-1][1]+a[i]);
            relax(f[j][2],g[j-1][2]+a[i]);
        }
    }

    // 因为 m<n , 所以不可能从 1 睡到 n , 所以是合法的。

    relax(ans,f[m][1]);
    relax(ans,f[m][2]);

    cout<<ans<<endl;
    return 0;
}

