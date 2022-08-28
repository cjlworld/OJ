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

const int N=1e5+5;

char a[N];
int n;
int cnt[26];

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%s",a);
	n=strlen(a);
	int pos=-1;
	for(int i=0;i+25<n;i++) {
		memset(cnt,0,sizeof cnt);
		
		bool flag=true;
		for(int j=i;j<=i+25;j++) {
			if(a[j]=='?') continue;
			else if(cnt[a[j]-'A']) {
				flag=false;
				break;
			}
			else cnt[a[j]-'A']++;
		}
		if(flag) {
			pos=i;
			break;
		}
	}
	if(pos==-1) return puts("-1")&0;
	for(int i=pos;i<=pos+25;i++) {
		if(a[i]!='?') continue;
		for(int j=0;j<26;j++) {
			if(!cnt[j]) {
				a[i]='A'+j;
				cnt[j]++;
				break;
			}
		}
	}
	for(int i=0;i<n;i++) {
		if(a[i]=='?') a[i]='A';
		putchar(a[i]);
	}
	puts("");
	return 0;
}

