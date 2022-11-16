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


ULL Hash(const string &str) 
{
	ULL res=0;
	for(int i=0;i<(int)str.length();i++) 
		res=res*13+(str[i]-'A');
	return res;
}

set<ULL> S;

string Wash(const string &a,const string &b)
{
	string D;
	for(int i=0;i<(int)a.length();i++) {
		D.push_back(b[i]);
		D.push_back(a[i]);
	}
	return D;
}

int T,n;
string A,B,C,D;

int main() 
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&T);
	for(int t=1;t<=T;t++) {
		S.clear();
		scanf("%d",&n);
		printf("%d ",t);
		cin>>A>>B>>C;
		int ans=1;
		D=Wash(A,B);
		S.insert(Hash(D));
		if(D==C) {
			printf("%d\n",ans);
			continue;
		}
//		cout<<D<<endl;
		for(;;ans++) {
			D=Wash(D.substr(0,n),D.substr(n,n));
			if(D==C) break;
//			cout<<D<<endl;
			if(S.count(Hash(D))) 
				break;
			else S.insert(Hash(D));
		}
		if(S.count(Hash(D))) 
			puts("-1");
		else printf("%d\n",++ans);
	}
	
	return 0;
}

