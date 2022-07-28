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
typedef pair<int,string> PIS;

priority_queue<PIS> q;

int n;

void write(const string &s)
{
	for(int i=0;i<(int)s.length();i++) 
		putchar(s[i]);
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int x;
	char opt[10],name[20];
	PIS y;
	scanf("%d",&n);
	while(n--) {
		scanf("%s",opt);
		if(!strcmp(opt,"push")) {
			scanf("%s%d",name,&x);
			q.push(PIS(x,name));
		}
		else {
			if(q.empty()) printf("none\n");
			else {
				y=q.top(); q.pop();
				write(y.second); printf(" %d\n",y.first);
			}	
		}
	}
	return 0;
}

