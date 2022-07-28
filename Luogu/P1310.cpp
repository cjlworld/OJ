#include<stack>
#include<cstdio>
#include<iostream>

using namespace std;
typedef long long LL;

const int N=1e5+5;
const LL MOD=10007;

int n;
char str[N];
int a[N];

struct Node
{
	char c;
	int lc,rc;
}t[N];

int root;
void build()
{
	stack<int> S;
	S.push(0); // �������ȼ�Ϊ 0 ���ڱ��ڵ㡣
	for(int i=1;i<=n;i++) {
		if(str[i]==')' || str[i]=='(') continue;
		while(a[S.top()]>a[i]) S.pop();
		int cur=S.top();
		t[i].lc=t[cur].rc; t[cur].rc=i;
		t[i].c=str[i];
		S.push(i);
	} 
	root=t[0].rc;
}

LL f[N][2];
// f[x][0] ��ʾ�� x Ϊ������������ 0 �ķ�����.
// f[x][1] ��ʾ�� x Ϊ������������ 1 �ķ�����.

void dp(int x)
{
	if(!x) return;
	dp(t[x].lc); dp(t[x].rc);
	
	int ls=t[x].lc,rs=t[x].rc;
	if(t[x].c=='+') { // or ���� 
		f[x][0]=f[ls][0]*f[rs][0];
		f[x][1]=f[ls][0]*f[rs][1]+f[ls][1]*f[rs][0]+f[ls][1]*f[rs][1];
	}
	else{
		f[x][0]=f[ls][0]*f[rs][1]+f[ls][1]*f[rs][0]+f[ls][0]*f[rs][0];
		f[x][1]=f[ls][1]*f[rs][1];
	}
	f[x][0]%=MOD; f[x][1]%=MOD;
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	scanf("%s",str+1);
	int bts=0; // ���ż�����
	for(int i=1;i<=n;i++) {
		if(str[i]=='(') bts++;
		else if(str[i]==')') bts--;
		else if(str[i]=='+') a[i]=2*bts+1;
		else if(str[i]=='*') a[i]=2*bts+2;
	}
	build();
	
	f[0][0]=f[0][1]=1;
	dp(root);
	
	printf("%lld\n",f[root][0]);
	return 0;
}
