#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=11;

int n;
int a[N];
bool vis[N];
char str[N];

void dfs(int step) // Ìî³äµÚ step ¸öÎ»ÖÃ 
{
	if(step==n+1) {
		for(int i=1;i<=n;i++) 
			putchar(str[a[i]]);
		puts("");
		return;
	}
	
	for(int i=1;i<=n;i++) 
		if(!vis[i]) {
			vis[i]=true;
			a[step]=i;
			
			dfs(step+1);
			
			vis[i]=false;
			a[step]=0; 
		}
}

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	dfs(1); 
	return 0;
}

