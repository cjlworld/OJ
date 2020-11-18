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

const int N=1e6+5;

int n,m; // n��ʾ�ַ����ĳ��ȣ�m��ʾ��ǰ�ؼ��ֵ��������� 
char a[N];
int sa[N],rk[N]; // sa[i] ��ʾ����Ϊi�ĺ�׺�� sa[i] ��rk[i] ��ʾ��׺i ��������

void get_sa()
{
	int i,k,num;
	static int x[N],y[N],c[N];
	// x[i] ��ʾ��׺i������ 
	// y[i] ��ʾ�ڶ��ؼ�������Ϊi�ĺ�׺Ϊ y[i] 
	// c[] �����ڼ�����Ͱ�� 
	memset(c,0,sizeof c);
	for(i=1;i<=n;i++) c[x[i]=a[i]]++;	
	for(i=2;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i; 
	
	for(k=1;k<=n;k<<=1) { // k��ʾ��һ�ؼ��ֵĳ��ȡ� 
		num=0;
		for(i=n-k+1;i<=n;i++) y[++num]=i; // ��Щ��׺û�еڶ��ؼ���--> �ڶ��ؼ�����С�� 
		for(i=1;i<=n;i++) 
			if(sa[i]>k) y[++num]=sa[i]-k;
			
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[x[i]]++;
		for(i=2;i<=m;i++) c[i]+=c[i-1];
		
		for(i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		// ����� x[] ��ͬ�ĺ�׺���� sa[] �ϵ�һ�εĻ���
		// ���forѭ������˼���ǰ��յڶ��ؼ��ֵĴ�С��
		// ��ÿһ����һ�ؼ��ֶ�Ӧ�Ķ��ڴӺ���ǰ�����׺�� 
		
		// �� x[] ���� ǰ2k����ĸ��sa[] ����Ϊ��һ��ѭ���ĵ�һ�ؼ��� �� 
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(i=2;i<=n;i++)
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num);
		if(num==n) break; // ����Ѿ�������ͬ���˳��� 
		m=num; // ���� �ؼ��ֵ������� 
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
	// ����Ϊi�ĺ�׺������Ϊi )_( 
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%s",a+1);
	n=strlen(a+1),m=122;
	get_sa();
	for(i=1;i<=n;i++) printf("%d ",sa[i]);
	printf("\n");
	return 0; 
}

