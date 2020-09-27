#include<set>
#include<cstdio>
#include<iostream>

using namespace std;

const int N=5e4+5,INF=1e9+5;

multiset<int> t[4*N];

#define lc (now<<1)
#define rc (now<<1|1)

void insert(int now,int pos,int key,int l,int r)
{
    t[now].insert(key);
//    multiset<int>::iterator it;
//    printf("[%d,%d] : ",l,r);
//    for(it=t[now].begin();it!=t[now].end();it++) 
//        printf("%d ",*it);
//    printf("\n");
    if(l==r&&l==pos) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(lc,pos,key,l,mid);
    else insert(rc,pos,key,mid+1,r);
    return;
}

void erase(int now,int pos,int key,int l,int r)
{
    t[now].erase(t[now].find(key));
//    multiset<int>::iterator it;
//        printf("[%d,%d] : ",l,r);
//         for(it=t[now].begin();it!=t[now].end();it++) 
//         	printf("%d ",*it);
//         printf("\n");
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) erase(lc,pos,key,l,mid);
    else erase(rc,pos,key,mid+1,r);
    return;
}

int Fdprev(int now,int x,int y,int key,int l,int r)
{
    if(x<=l&&r<=y) {
        if(*t[now].begin()>=key) return -INF; 
        multiset<int>::iterator it;
//        printf("[%d,%d] : ",l,r);
//         for(it=t[now].begin();it!=t[now].end();it++) 
//         	printf("%d ",*it);
 //        printf("\n");
        it=t[now].lower_bound(key);
//        printf("[%d,%d] : %d %d\n",l,r,key,*it);
        it--;
//        printf("[%d,%d] : %d %d\n",l,r,key,*it);
        return *it;
    }
    int mid=(l+r)>>1,res=-INF;
    if(x<=mid) res=max(res,Fdprev(lc,x,y,key,l,mid));
    if(y>=mid+1) res=max(res,Fdprev(rc,x,y,key,mid+1,r));
    return res;
}

int n,m;
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    int x,y,z,opt;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        insert(1,i,a[i],1,n);
    }
    while(m--) {
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==1) {
            erase(1,x,a[x],1,n);
            insert(1,x,y,1,n);
            a[x]=y;
        }
        else {
            scanf("%d",&z);
            printf("%d\n",Fdprev(1,x,y,z,1,n));
        }
    }
    return 0;
}

