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

const int N=100+5;

int n,m;
int cnt[N],a[N];
int sum[N];

int main()
{
//	freopen("1.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		m=max(m,a[i]);
		cnt[a[i]]++;
	}
	
	for(int i=1;i<=m;i++) {
		if(cnt[i]==2 || cnt[i]==0) continue;
		else if(cnt[i]==1) sum[1]++;
		else sum[3]++;
	}
	if(sum[1]%2==0) {
		puts("YES");
		int tmp=0;
		for(int i=1;i<=n;i++) {
			if(cnt[a[i]]==2) putchar('A');
			else if(cnt[a[i]]==1) {
				tmp++;
				if(tmp<=sum[1]/2) putchar('A');
				else putchar('B');
			}
			else putchar('A');
		}
	}
	else if(sum[3]==0) puts("NO");
	else {
		puts("YES");
		int tmp=0;
		bool flag=false;
		int supernum=0;
		for(int i=1;i<=n;i++) 
			if(cnt[a[i]]>2) {
				supernum=a[i];
				break;
			}
		for(int i=1;i<=n;i++) {
			if(cnt[a[i]]==2) putchar('A');
			else if(cnt[a[i]]==1) {
				tmp++;
				if(tmp<=sum[1]/2) putchar('A');
				else putchar('B');
			}
			else if(!flag && a[i]==supernum){
				flag=true;
				putchar('A');
			}
			else putchar('B');
		}
	}
	return 0;
}

