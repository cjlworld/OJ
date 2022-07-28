#include<iostream>

using namespace std;
typedef long long LL;
const int N=4000+5;
const LL MOD=2147483648;

LL f[N];
int n;
int main()
{
    int i,j;
    cin>>n;
    f[0]=1;
    for(i=1;i<=n-1;i++) 
        for(j=i;j<=n;j++) 
            f[j]=(f[j]+f[j-i])%MOD;
    cout<<f[n]<<endl;
    return 0;
}
