#include<bits/stdc++.h>
using namespace std;
/*第1行：一个正整数N(N≤15,000)，表示小明补办银联卡总共的天数。
第2行到第N+1 行：每一行描述一天中收到的帐单。
先是一个非负整数M≤100，表示当天收到的账单数，
后跟M个正整数（都小于1,000,000,000），表示每张帐单的面额。
输入数据保证每天都可以支付两张帐单。*/
multiset<int> q;
int n,m;
int sum=0;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	int x,y;
	for(i=1;i<=n;i++) {
		scanf("%d",&m);
		for(j=1;j<=m;j++) {
			scanf("%d",&x);
			q.insert(x);
		}
		printf("%d ",*q.begin());	//输出最小值
		q.erase(q.begin());	//删除最小值
		printf("%d\n",*(--q.end()));	//输出最大值
		q.erase(--q.end());		//删除最大值
	}
	return 0;
}

