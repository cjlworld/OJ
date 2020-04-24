#include<set>
#include<queue>
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
set<int> S;
queue< pair<int,int> > q;
int n;
short cnt[N];
int head,tail;
inline void del(int x)
{
	if(cnt[x]==1) S.erase(x);
	if(cnt[x]) cnt[x]--;
	return;
}
inline void add(int x)
{
	cnt[x]++;
	if(cnt[x]==1) 
		S.insert(x);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	int x,y,z;
	int t;
	for(i=1;i<=n;i++) {
		scanf("%d",&t);
		tail=t;
		while(q.size()&&q.front().first<=tail-86400) {
			del(q.front().second);
			q.pop();
		}
		scanf("%d",&z);
		for(j=1;j<=z;j++) {
			scanf("%d",&x);
			q.push(pair<int,int>(t,x));
			add(x);
		}
		printf("%d\n",(int)S.size());
	}
	return 0;
}

