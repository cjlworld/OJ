// AcWing .106
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

priority_queue<int> sml; // ����� 
priority_queue<int,vector<int>,greater<int> > big; // С���� 
// ά�������sml�ĶѶ�Ϊ��λ���� 
void balance()
{
	unsigned k=(sml.size()+big.size()+1)/2; // ά������ѵ�sizeΪk;
	while(sml.size()>k) big.push(sml.top()),sml.pop();
	while(sml.size()<k) sml.push(big.top()),big.pop();
}
void insert(int x)
{
	if(sml.empty()||x<=sml.top()) sml.push(x);
	else big.push(x);
	balance();
}
int get() { return sml.top(); }
void clear() 
{	
	while(sml.size()) sml.pop();
	while(big.size()) big.pop();
}

const int N=2e4+5;
int a[N];
int P,t,n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&P);
	while(P--) {
		scanf("%d%d",&t,&n);
		printf("%d %d\n",t,(n+1)/2);
		clear();
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			insert(a[i]);
			if(i&1) printf("%d ",get());
			if(i%20==0) printf("\n"); 
		}
		printf("\n");
	}
	return 0;
}

