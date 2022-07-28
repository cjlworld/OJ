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

const int N=256;

int n,m; // n����,m���ˡ� 
int a[N];

bool check(int t)
{
	int i,sum=0,cnt=1;
	for(i=n;i>=1;i--) { //�ú�����˶೭
		if(a[i]>t) return false;
		if(sum+a[i]>t) cnt++,sum=a[i];
		else sum+=a[i];
	}
	if(cnt>m) return false;
	else return true;
}

int ansl[N],ansr[N],top;

int main()
{
	int i;
	int L=0,R=0,mid; // ���ֳ�д�����˳�д��ҳ���� 
	// ��֤ R-INF ����, 0-L ���С� 
	scanf("%d%d",&n,&m);
	if(n==0) return 0; // �޿� 
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		R+=a[i];
	}
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	int sum=0;
	ansr[top]=n;
	for(i=n;i>=1;i--) {
		if(sum+a[i]>R) {
			ansl[top]=i+1;
			ansr[++top]=i;
			sum=a[i];
		}
		else sum+=a[i];
	}
	ansl[top]=1;
	for(;top>=0;top--) 
		printf("%d %d\n",ansl[top],ansr[top]);
	return 0;
}

