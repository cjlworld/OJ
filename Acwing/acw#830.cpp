#include<bits/stdc++.h>
using namespace std;
stack<int> S;
int main()
{
    int n,x,i;
    cin>>n;
    for(i=1;i<=n;i++) {
        scanf("%d",&x);
        while(S.size()&&S.top()>=x) S.pop();
        if(S.empty()) 
            printf("-1 ");
        else {
            printf("%d ",S.top());
        }
        S.push(x);
    }
}
