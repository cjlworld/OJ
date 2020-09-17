#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=3000+5;

int n;
int a[N],b[N],f[N][N]; // f[i][j] a[1~i] �� b[j] ��β�����������������
int g[N]; // g[k] = max{ states f[i-1][k] | b[k] < a[i] }
int main()
{
//  freopen("1.in","r",stdin);
    int i,j,k;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<=n;i++) cin>>b[i];

    for(i=1;i<=n;i++) {
        memset(g,0,sizeof g);
        int cmax=0;
        for(j=0;j<=n;j++) {
            if(b[j]<a[i]) 
                cmax=max(cmax,f[i-1][j]);
            g[j]=cmax;
        }

        for(j=1;j<=n;j++) {
            f[i][j]=f[i-1][j]; // hasn't used a[i]
            if(a[i]==b[j]) f[i][j]=max(f[i][j],g[j]+1);
            if(a[i]!=b[j]) continue;
            // for(k=0;k<=j-1;k++) 
            //     if(b[k]<a[i]&&f[i-1][k]+1>f[i][j]) printf("Wrong here\n");
//                    f[i][j]=max(f[i][j],f[i-1][k]+1);
//            printf("%d %d : %d\n",i,j,f[i][j]);
        }
    }

    int ans=0;
    for(i=1;i<=n;i++)
        ans=max(ans,f[n][i]);
    cout<<ans;
    return 0;
}
/*
���ߣ�cjlworld
���ӣ�https://www.acwing.com/activity/content/code/content/472493/
��Դ��AcWing
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/
