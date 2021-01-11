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

const int N=15;

int n;
double a[N][N],b[N];

void gauss()
{
    int r,c,i,j,t;
    double rate;
    for(r=1,c=1;r<=n;r++,c++) {
//      for(i=1;i<=n;i++) {
//          for(j=1;j<=n;j++) 
//              printf("%.3lf ",a[i][j]);
//          printf("= %.3lf\n",b[i]);
//      }
//      printf("\n");
        t=r;
        for(i=r+1;i<=n;i++) 
            if(fabs(a[i][c])>fabs(a[t][c])) 
                t=i;

        for(i=c;i<=n;i++) swap(a[r][i],a[t][i]);
        swap(b[r],b[t]);

        b[r]/=a[r][c];
        for(i=n;i>=c;i--) a[r][i]/=a[r][c];

        for(i=r+1;i<=n;i++) {
            rate=a[i][c];
            b[i]-=rate*b[r];
            for(j=n;j>=c;j--) 
                a[i][j]-=a[r][j]*rate;
        }
    }
    for(i=n-1;i>=1;i--) 
        for(j=n;j>i;j--) 
            b[i]-=a[i][j]*b[j];
}

int main()
{
//  freopen("1.in","r",stdin);
    int i,j;

    scanf("%d",&n);
    for(i=0;i<=n;i++) 
        for(j=1;j<=n;j++)
            scanf("%lf",&a[i][j]);

    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            b[i]+=a[0][j]*a[0][j]-a[i][j]*a[i][j];
            a[i][j]=2*(a[0][j]-a[i][j]);

//          printf("%.3lf ",a[i][j]);
        }
//      printf("= %.3lf \n",b[i]);
    }
    gauss();
    for(i=1;i<=n;i++) 
        printf("%.3lf ",b[i]);
    return 0; 
}
