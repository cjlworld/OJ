#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
typedef long long LL;
LL p[N],tot=0,phi[N];
bool tag[N];
void prime(int n)
{
    int i,j;
//    phi[1]=1;
    for(i=2;i<=n;i++) {
        if(!tag[i]) p[++tot]=i,phi[i]=i-1;
        for(j=1;j<=tot && p[j]*i<=n;j++) {
            tag[p[j]*i]=true;
            if(i%p[j]) phi[i*p[j]]=phi[i]*(p[j]-1);
            else {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
        }
    }    
    return;
}
int n;
int main()
{
    LL i,j;
    LL ans=0;
    cin>>n;
    prime(n);
    for(i=1,j=tot;i<=n;i++) {
        for(;i*p[j]>n && j>0;j--);
        ans+=(LL)phi[i]*j;
    }
    cout<<ans*2+tot;
    return 0;
}
