#include<set>
#include<map>
#include<queue>
#include<deque>
#include<stack>
#include<ctime>
#include<cmath>
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

const int N=1e6+5,M=10024;

int id[N];
int rk[N],gr[N];
deque<int> group[M];
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,z;
	char opt[30];
	int T=0;
	int hh,tt;
	
	while(scanf("%d",&n),n) {
		memset(id,0,sizeof id);
		memset(rk,0,sizeof rk);
		memset(gr,0,sizeof gr);
		
		for(i=1;i<=n;i++) {
			scanf("%d",&z);
			for(j=1;j<=z;j++) {
				scanf("%d",&x);
				id[x]=i;
			}
		}
		printf("Scenario #%d\n",++T);
		hh=1,tt=0;
		while(scanf("%s",opt)==1) {
			if(!strcmp(opt,"STOP")) break;
			else if(!strcmp(opt,"ENQUEUE")) {
				scanf("%d",&x);
				if(!rk[id[x]]) {
					rk[id[x]]=++tt,gr[tt]=id[x];
					group[tt].clear();
				}
				group[rk[id[x]]].push_back(x);
			}
			else {
				printf("%d\n",group[hh].front());
				group[hh].pop_front();
				if(group[hh].empty()) {
					rk[gr[hh]]=0;
					gr[hh]=0;
					hh++;
				}
			}
		}
		printf("\n");
	}
	return 0;
}

