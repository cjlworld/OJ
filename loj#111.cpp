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

int n,m; // n表示字符串的长度，m表示当前关键字的种类数。 
char a[N];
int sa[N],rk[N]; // sa[i] 表示排名为i的后缀是 sa[i] ，rk[i] 表示后缀i 的排名。

void get_sa()
{
	int i,k,num;
	static int x[N],y[N],c[N];
	// x[i] 表示后缀i的排名 
	// y[i] 表示第二关键字排名为i的后缀为 y[i] 
	// c[] 是用于计数的桶。 
	memset(c,0,sizeof c);
	for(i=1;i<=n;i++) c[x[i]=a[i]]++;	
	for(i=2;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i; 
	
	for(k=1;k<=n;k<<=1) { // k表示第一关键字的长度。 
		num=0;
		for(i=n-k+1;i<=n;i++) y[++num]=i; // 这些后缀没有第二关键字--> 第二关键字最小。 
		for(i=1;i<=n;i++) 
			if(sa[i]>k) y[++num]=sa[i]-k;
			
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[x[i]]++;
		for(i=2;i<=m;i++) c[i]+=c[i-1];
		
		for(i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		// 假设把 x[] 相同的后缀看成 sa[] 上的一段的话，
		// 这个for循环的意思就是按照第二关键字的大到小，
		// 在每一个第一关键字对应的段内从后往前加入后缀。 
		
		// 将 x[] 根据 前2k的字母的sa[] 更新为下一轮循环的第一关键字 。 
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(i=2;i<=n;i++)
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num);
		if(num==n) break; // 如果已经互不相同，退出。 
		m=num; // 更新 关键字的种类数 
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
	// 排名为i的后缀的排名为i )_( 
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

