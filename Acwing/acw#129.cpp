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

// 本题有一个很强的性质
// 就是无论什么时候选择出栈操作的字典序一定更小。

const int N=256;

int n;
stack<int> S;
int ans[N],top;
int tot;

void dfs(int step) // step 表示还剩下 [step,n] 未进站 
{
	if(S.empty()&&step==n+1) {
		for(int i=1;i<=top;i++) 
			printf("%d",ans[i]);
		printf("\n");
		tot++;
		if(tot==20) exit(0);
		else return;
	}
	int x;
	if(S.size()) { // 出栈 
		x=S.top(); S.pop();
		ans[++top]=x;
		dfs(step);
		S.push(x);
		top--;
	}
	// 进站
	if(step<=n) {
		S.push(step);
		dfs(step+1);
		S.pop();
	} 
} 

int main()
{
//	freopen("1.in","r",stdin);
	cin>>n;
	dfs(1);
	return 0;
}

