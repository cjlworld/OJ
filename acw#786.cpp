#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1e5+5;

int a[N];
int n,k;

int main()
{
    int i;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    nth_element(a+1,a+k,a+n+1);
    printf("%d\n",a[k]);
    return 0;
}
