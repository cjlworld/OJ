#include<bits/stdc++.h>
using namespace std;
const int N=1024;
int gcd(int a,int b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
int s[N];
int main()
{
    int i,j;
    int n=1000;
    for(i=1;i<=n;i++) {
        for(j=0;j<=i;j++) {
            if(gcd(i,j)==1) s[i]++;
            if(gcd(j,i)==1) s[i]++;
        }
        if(gcd(i,i)==1) s[i]--;
    }
    for(i=1;i<=n;i++) 
        s[i]+=s[i-1];
    int C;
    cin>>C;
    for(i=1;i<=C;i++) {
        cin>>n;
        cout<<i<<" "<<n<<" "<<s[n]<<endl;
    }
    return 0;
}
