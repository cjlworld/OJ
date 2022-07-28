#include<bits/stdc++.h>
using namespace std;
int varphi(int x)
{
    int res=x;
    int i;
    for(i=2;i*i<=x;i++) {
        if(x%i==0) {
            while(x%i==0) x=x/i;
            res=res/i*(i-1);
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}
int main()
{
    int n,x;
    cin>>n;
    while(n--) {
        cin>>x;
        cout<<varphi(x)<<endl;
    }
    return 0;
}
