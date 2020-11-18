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

// ������һ����ǿ������
// ��������ʲôʱ��ѡ���ջ�������ֵ���һ����С��

const int N=256;

int n;
stack<int> S;
int ans[N],top;
int tot;

void dfs(int step) // step ��ʾ��ʣ�� [step,n] δ��վ 
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
	if(S.size()) { // ��ջ 
		x=S.top(); S.pop();
		ans[++top]=x;
		dfs(step);
		S.push(x);
		top--;
	}
	// ��վ
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

