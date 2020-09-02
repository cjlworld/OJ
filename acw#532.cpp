#include<bits/stdc++.h>
using namespace std;
const int N=25000+5;
bool f[N];
int a[N];
int n,T;
int main()
{
//	freopen("1.in","r",stdin);
    int i,j;
    cin>>T;
    while(T--) {
        memset(f,0,sizeof f);
        cin>>n;
        for(i=1;i<=n;i++) 
            cin>>a[i];
        sort(a+1,a+n+1);
        f[0]=true;
        int ans=0;
        for(i=1;i<=n;i++) {
        	if(f[a[i]]) continue;
        	else ans++;
            for(j=a[i];j<=a[n];j++) 
                f[j]=f[j]|f[j-a[i]];
            for(j=1;j<=n;j++)
                if(!f[a[j]])
                	break;
            if(j==n+1) {
                cout<<ans<<endl;
                break;
            }
        }
    }
    return 0;
}

