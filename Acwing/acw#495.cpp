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
string a,b,c;

inline int get(char c) 
{
	return c-'A'+1;
}
char p[N];
bool vis[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	getline(cin,a); getline(cin,b); getline(cin,c);	
	for(i=0;i<(int)a.length();i++) {
		if(p[get(a[i])]!='\0') {
			if(p[get(a[i])]==b[i]) continue;
			else {
				printf("Failed\n");
				return 0;
			}
		}
		else p[get(a[i])]=b[i];
		vis[get(b[i])]=true;
	}
	for(i=1;i<=26;i++) 
		if(!vis[i]) {
			printf("Failed\n");
			return 0;
		}
	
	for(i=0;i<(int)c.length();i++) 
		c[i]=p[get(c[i])];
	cout<<c;
	return 0;
}

