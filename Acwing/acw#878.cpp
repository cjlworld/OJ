#include<bits/stdc++.h>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0) {
        x=1; y=0;
        return a;
    }
    int z=exgcd(b,a%b,y,x);
    y=y-a/b*x;
    return z;
}
int main()
{
    int n,a,b,c,d,x,y,z;
    cin>>n;
    while(n--) {
        scanf("%d%d%d",&a,&d,&b);
        z=exgcd(a,b,x,y);
        if(d%z) printf("impossible\n");
        else printf("%d\n",(int)((long long)x*(d/z)%(b/z)));
    }
    return 0;
}
