#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e4+5;
char path[N];
int n;
int a[N];
int tot=0;
int s1[N],s2[N],t1,t2;

priority_queue<int,vector<int>,greater<int> > q;

bool dfs(int u);

inline bool c1(int u)
{
	vector<int> v1,v2;
	s1[++t1]=a[u];
	path[++tot]='a';
	while(s2[t2]==q.top()||s1[t1]==q.top()) {
		if(s2[t2]==q.top()) {
			v2.push_back(s2[t2]);
			q.pop();
			t2--;
			path[++tot]='d';
		}
		else {
			v1.push_back(s1[t1]);
			q.pop();
			t1--;
			path[++tot]='b';
		}
	}
	if(dfs(u+1)) return true;
	if(v1.size()||v2.size()) {
		while(v1.size()) s1[++t1]=v1.back(),q.push(v1.back()),v1.pop_back(),tot--;
		while(v2.size()) s2[++t2]=v2.back(),q.push(v2.back()),v2.pop_back(),tot--;
	}
	tot--;
	t1--;
	return false;
}
inline bool c2(int u)
{
	vector<int> v1,v2;
	s2[++t2]=a[u];
	path[++tot]='c';
	while(s2[t2]==q.top()||s1[t1]==q.top()) {
		if(s2[t2]==q.top()) {
			v2.push_back(s2[t2]);
			q.pop();
			t2--;
			path[++tot]='d';
		}
		else {
			v1.push_back(s1[t1]);
			q.pop();
			t1--;
			path[++tot]='b';
		}
	}
	if(dfs(u+1)) return true;
	if(v1.size()||v2.size()) {
		while(v1.size()) s1[++t1]=v1.back(),q.push(v1.back()),v1.pop_back(),tot--;
		while(v2.size()) s2[++t2]=v2.back(),q.push(v2.back()),v2.pop_back(),tot--;
	}
	tot--;
	t2--;
	return false;
}

bool dfs(int u)
{
	if(u==n+1) return true;
	int k1=(t1==0||a[u]<s1[t1]),k2=(t2==0||(a[u]<s2[t2]));
	if(!k1&&!k2) return false;
	else if((k1&&!k2)||(k1&&t2==0)||(t1>0&&t2>0&&s1[t1]<s2[t2]&&k1)) {
		if(c1(u)) return true;
	}
	else if(k2&&!k1) {
		if(c2(u)) return true;
	}
	else {
		if(c1(u)) return true;
		if(c2(u)) return true;
	}
//	if(k1&&c1(u)) return true;
//	if(k2&&c2(u)) return true;
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]),q.push(i);
	if(!dfs(1)) printf("0\n");
	else {
		for(i=1;i<=tot;i++) 
			printf("%c ",path[i]);
		printf("\n");
	}
	return 0;
}

