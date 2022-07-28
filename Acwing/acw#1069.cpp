#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

#define int long long 
vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	if(a.size()<b.size()) swap(a,b);
	int t=0;
	unsigned i;
	for(i=0;i<a.size();i++) {
		t+=a[i];
		if(i<b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10;
	}
	if(t) c.push_back(t);
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

vector<int> mul(vector<int> a,int b)
{
	int t=0;
	vector<int> c;
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	while(t) c.push_back(t%10),t/=10;
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

vector<int> Min(vector<int> a,vector<int> b)
{
	if(a.size()<b.size()) return a;
	else if(b.size()<a.size()) return b;
	for(int i=a.size()-1;i>=0;i--) {
		if(a[i]<b[i]) return a;
		else if(a[i]>b[i]) return b;
	}
	return a;
}

const int N=51;
int n;
vector<int> f[N][N];
int w[N];
signed main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,len;
	vector<int> c; c.push_back(1);
	cin>>n;
	for(i=1;i<=n;i++) cin>>w[i];
	for(len=3;len<=n;len++) {
		for(i=1;i+len-1<=n;i++) {
			j=i+len-1;
			if(len==1||len==2) {
				f[i][j].clear();
				f[i][j].push_back(0);	
			}
			else if(len==3) f[i][j]=mul(mul(mul(c,w[i]),w[i+1]),w[j]);
			else {
				for(k=1;k<=40;k++) 
					f[i][j].push_back(0);
				f[i][j].push_back(1);
				for(k=i+1;k<=j-1;k++) 
					f[i][j]=Min(f[i][j],add(add(f[i][k],f[k][j]),mul(mul(mul(c,w[i]),w[k]),w[j])));
			}
		}
	}
	for(i=f[1][n].size()-1;i>=0;i--)
		cout<<f[1][n][i];
	return 0;
}

