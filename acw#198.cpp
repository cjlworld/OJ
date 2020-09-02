#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100;
int p[N]={0,2,3,5,7,11,13,17,19,23};
int a[N]={30};
LL n,cmax,ans;
void dfs(int step,LL sum,LL cnt)
{
    if(step==10) {
        if(cnt>cmax||(cnt==cmax&&sum<ans)) {
            cmax=cnt;
            ans=sum;
        }
        return;
    }
    for(LL i=0,j=1;i<=a[step-1]&&sum*j<=n;i++,j*=p[step]) {
        a[step]=i;
        dfs(step+1,sum*j,cnt*(i+1));
    }
    return;
}
int main()
{
    cin>>n;
    dfs(1,1,1);
    cout<<ans;
    return 0;
}
