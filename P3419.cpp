#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=5e5+5;
int pre[N],Next[N];
int a[N];
bool exist[N];
int n,k,m; //n kinds,k free place,m times;
int pool=0,cnt=0;
priority_queue< pair<int,int> > q;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&k,&m);
	memset(Next,0x3f,sizeof Next);
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		Next[pre[x]]=i;
		pre[x]=i;
		a[i]=x;
	}
	for(i=1;i<=m;i++) {
		if(exist[a[i]]) {
			q.push(make_pair(Next[i],a[i]));
		}
		else if(pool<k) {
			exist[a[i]]=true;
			q.push(make_pair(Next[i],a[i]));
			pool++;
			cnt++;
		}
		else {
			while(!exist[q.top().second]) 
				q.pop();
			exist[q.top().second]=false; q.pop();
			exist[a[i]]=true;
			q.push(make_pair(Next[i],a[i]));
			cnt++;
		}
	}
	cout<<cnt;
	return 0;
}

