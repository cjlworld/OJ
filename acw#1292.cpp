#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
bool tag[N];
int p[N],tot=0;
void prime(int n)
{
    long long i,j;
    tag[1]=true;
    for(i=2;i<=n;i++) {
        if(tag[i]) continue;
        p[++tot]=i;
        for(j=i*i;j<=n;j+=i) 
            tag[j]=true;
    }
    return;
}
int n=1e6;
int main()
{
    prime(n);
  //  for(int i=1;i<=10;i++) 
  //      cout<<p[i]<<endl;
    while(cin>>n) {
        if(n==0) break;
        for(int i=1;i<=tot;i++) {
            if(!tag[n-p[i]]) {
                printf("%d = %d + %d\n",n,p[i],n-p[i]);
                break;
            }
        }
    }
    return 0;
}
