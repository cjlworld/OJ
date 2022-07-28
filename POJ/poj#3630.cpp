#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
inline int read(int *arr)
{
    char c;
    int i;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(i=1;c>='0'&&c<='9';i++,c=getchar())     
        arr[i]=c-'0';
    return i-1;
}
int T;
int n;
int a[10005][13],len[10005];
struct Node
{
    int ch[10];
    int cnt;
};
Node t[700005];
int root=0;
int cnt=0;
inline void insert(const int *arr,const int &len)
{
    int i;
    int now=root;
    for(i=1;i<=len;i++) {
        if(t[now].ch[arr[i]]==0) 
            t[now].ch[arr[i]]=++cnt;
        now=t[now].ch[arr[i]]; 
    }
    t[now].cnt++;
    return;
}
inline bool query(const int *arr,const int &len)
{
    int i;
    int now=root;
    for(i=1;i<=len;i++) {
        if(t[now].ch[arr[i]]==0) 
            return false;
        if(t[now].cnt==1) 
            return true;
        now=t[now].ch[arr[i]];
    }
    return false;
}
int main()
{
//    freopen("1.in","r",stdin);
    register int i;
    scanf("%d",&T);
    while(T--) {
        memset(t,0,sizeof t);
        cnt=0;
        scanf("%d",&n);
        for(i=1;i<=n;i++) {
            len[i]=read(a[i]);
            insert(a[i],len[i]);
        }
        for(i=1;i<=n;i++) {
            if(query(a[i],len[i])) {
                puts("NO");
                break;
            }
        }
        if(i==n+1) 
            puts("YES");
    }
    return 0;
}
