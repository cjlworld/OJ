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

const int N=2048;

vector<int> e[N];
map<int,int> mp[N];
int h[N];
vector<int> ans;
void Euler(int x)
{
	int y;
	for(int &i=h[x];i<(int)e[x].size();i++) {
		y=e[x][i];
		if(mp[x][y]) {
			mp[x][y]--,mp[y][x]--;
			Euler(y);	
		}
	}
	ans.push_back(x);
}

int n=500,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		e[x].push_back(y),e[y].push_back(x);
		mp[x][y]++,mp[y][x]++;
	}
	for(i=1;i<=n;i++) 
		sort(e[i].begin(),e[i].end());
	for(i=1;i<=n;i++) 
		if(e[i].size()%2) 
			break;
	if(i==n+1) {
	    for(i=1;i<=n;i++) 
	        if(e[i].size()) break;
	}
	Euler(i);
	while(ans.size()) 
		printf("%d\n",ans.back()),ans.pop_back();
	return 0;
}

