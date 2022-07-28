#include<set>
#include<map>
#include<queue>
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

const int N=2e6+5;

int n;
stack<int> sl,sr;
int s[N],cmax[N];

int main()
{
//	freopen("1.in","r",stdin);
	char opt[3];
	int it=0,x;
	
	scanf("%d",&n);
	memset(cmax,-0x3f,sizeof cmax);
	while(n--) {
		scanf("%s",opt);
		if(*opt=='I') {
			scanf("%d",&x);
			sl.push(x);
			it++;
			s[it]=s[it-1]+x;
			cmax[it]=max(cmax[it-1],s[it]);
		}
		else if(*opt=='D') {
			if(it>0) 
				sl.pop(),it--;
		}
		else if(*opt=='L') {
			if(it>0) {
				sr.push(sl.top()),sl.pop();
				it--;
			}
		}
		else if(*opt=='R') {
			if(sr.size()) {
				x=sr.top();
				sr.pop();
				sl.push(x);
				it++;
				s[it]=s[it-1]+x;
				cmax[it]=max(cmax[it-1],s[it]);
			}		
		}
		else {
			scanf("%d",&x);
			printf("%d\n",cmax[x]);
		}
	}
	return 0;
}

