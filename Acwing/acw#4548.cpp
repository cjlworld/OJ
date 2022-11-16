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

const int N=256;

int n,m;

vector<int> nums;
int getid(int x) { return (upper_bound(nums.begin(),nums.end(),x)-nums.begin()); }

int a[N],b[N],c[N];
struct Brick
{
	int a,b,c;
}e[N*N];

int f[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int times=0; 
	while(scanf("%d",&n),n) {
		nums.clear(); ++times;
		for(int i=1;i<=n;i++) {
			scanf("%d%d%d",&a[i],&b[i],&c[i]);
			nums.push_back(a[i]);
			nums.push_back(b[i]);
			nums.push_back(c[i]);
		}
		sort(nums.begin(),nums.end());
		nums.erase(unique(nums.begin(),nums.end()),nums.end());
		
		m=0; 
		for(int i=1;i<=n;i++) {
			m++; e[m].a=getid(a[i]); e[m].b=getid(b[i]); e[m].c=c[i];
			m++; e[m].a=e[m-1].b; e[m].b=e[m-1].a; e[m].c=e[m-1].c;
			m++; e[m].a=getid(a[i]); e[m].b=getid(c[i]); e[m].c=b[i];
			m++; e[m].a=e[m-1].b; e[m].b=e[m-1].a; e[m].c=e[m-1].c;
			m++; e[m].a=getid(b[i]); e[m].b=getid(c[i]); e[m].c=a[i];
			m++; e[m].a=e[m-1].b; e[m].b=e[m-1].a; e[m].c=e[m-1].c;
		} 
		
		memset(f,0,sizeof f);
		for(int i=nums.size();i>=1;i--) 
			for(int j=nums.size();j>=1;j--) {
				for(int k=1;k<=m;k++) {
					if(e[k].a==i && e[k].b==j) 
						f[i][j]=max(f[i][j],f[i+1][j+1]+e[k].c);
				}
				for(int k=i;k>=1;k--) 
					for(int e=j;e>=1;e--) {
						if(i==k && j==e) continue;
						else if(f[k][e]>=f[i][j]) break;
						else f[k][e]=f[i][j];
					}
			}
		
		printf("Case %d: maximum height = %d\n",times,f[1][1]);
	}
	
	return 0;
}

