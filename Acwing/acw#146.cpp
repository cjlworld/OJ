#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e6+5;

struct Trie
{
    int ch[N][10],idx,cnt[N];
    void insert(const char *a,int len)
    {
        int i,now=0;
        for(i=0;i<len;i++) {
            int &s=ch[now][a[i]-'0'];
            if(!s) s=++idx;
            now=s;
        } 
        cnt[now]++;
    }
    
    bool query(const char *a,int len)
    {
        int i,now=0,s;
        for(i=0;i<len;i++) {
            s=ch[now][a[i]-'0'];
            if(!s) return false;
            else now=s;
            if(cnt[now]) return true;
        }
        return true;
    }
    
    void clear()
    {
        idx=0;
        memset(ch,0,sizeof ch);
        memset(cnt,0,sizeof cnt);
    }
}Tr;

char a[N];
int n,m;

int main()
{
//  freopen("1.in","r",stdin);
    int T,i;
    cin>>T;
    while(T--) {
        scanf("%d",&n);
        Tr.clear();
        for(i=1;i<=n;i++) {
            scanf("%s",a);
            if(Tr.query(a,strlen(a))) break;
            else Tr.insert(a,strlen(a));
        }
        if(i==n+1) printf("YES\n");
        else {
        	printf("NO\n");
        	for(i++;i<=n;i++) scanf("%s",a);
		}
    }
    
    return 0; 
}

