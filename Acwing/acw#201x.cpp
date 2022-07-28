#include<bits/stdc++.h>
using namespace std;
const int N=1024;
int p[N],phi[N],tot=0;
bool tag[N];
void prime(int n)
{
    int i,j;
    phi[1]=1;
    for(i=2;i<=n;i++) {
        if(!tag[i]) 
            p[++tot]=i,phi[i]=i-1;
        for(j=1;j<=tot&&p[j]*i<=n;j++) {
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
int s[N];
int main()
{
    prime(1000);
    int i,j;
    int x,y,z;
    // for(i=1;i<=10;i++) 
    //     cout<<phi[i]<<endl;
    for(i=1;i<=1000;i++) 
        s[i]=s[i-1]+phi[i];
    int T,n;
    cin>>T;
    for(i=1;i<=T;i++) {
        cin>>n;
        cout<<i<<" "<<n<<" "<<s[n]*2+1<<endl;
    }
    return 0;
}
