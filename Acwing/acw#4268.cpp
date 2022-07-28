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

const int N=2e4+5; 

bool vis[N];
int p[N],tot;

void prime()
{
	for(int i=2;i<N;i++) {
		if(!vis[i]) p[++tot]=i;
		for(int j=1;j<=tot && ((LL)i)*p[j]<N;j++) {
			vis[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
}

inline bool isprime(int x)
{
	if(x<=1) return false;
	for(int i=1;i<=tot && ((LL)p[i])*p[i]<=x;i++) 
		if(x%p[i]==0) return false;
	return true;
}

int n;

int main()
{
	prime();
	
	cin>>n;
	if(!isprime(n) || (!isprime(n-6) && !isprime(n+6))) {
		puts("No");
		for(int i=n+1;;i++) {
			if(isprime(i) && isprime(i-6)) {
				if(i-6>n) printf("%d",i-6);
				else printf("%d",i);
				break;
			}
		}
	} 
	else {
		puts("Yes");
		if(isprime(n-6)) printf("%d",n-6);
		else printf("%d",n+6);
	}

	return 0;
}

/*
prime();
for(int i=1;i<=tot;i++) {
	if((p[i]>6 && !vis[p[i]-6]) || (p[i]+6<N && !vis[p[i]+6])) 
		S.insert(p[i]);
}
for(set<int>::iterator i=S.begin();i!=S.end();i++) {
	printf("%d,",*i);
}
cin>>n;
if(S.count(n)) {
	puts("Yes");
	if(S.count(n-6)) printf("%d\n",n-6);
	else printf("%d\n",n+6);
}
else  printf("No\n%d\n",*S.upper_bound(n));
*/
