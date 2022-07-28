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


const int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
const int N=256;

int op[N][N],cnt[N];

string a;
map<string,int> M;
string ed("111110111100*110000100000");

int A()
{
	int cnt=0,i;
	for(i=0;i<25;i++) 
		if(a[i]!='*'&&a[i]!=ed[i]) cnt++;
	return cnt;
}

bool dfs(int u,int depth,int cur)
{
	if(u-1+A()>depth) return false;
	else if(u-1==depth) return true;
	if(M.count(a)&&M[a]<u-1) return false;
	M[a]=u-1;
	int i,y;
	for(i=0;i<cnt[cur];i++) {
		y=op[cur][i];
		swap(a[cur],a[y]);
		if(dfs(u+1,depth,y)) return true;
		swap(a[cur],a[y]);
	}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	int T;
	int i,j,k,x,y,cur,depth;
	char ch;
	for(i=0;i<5;i++) 
		for(j=0;j<5;j++) {
			cur=i*5+j;
			for(k=0;k<8;k++) {
				x=i+dx[k],y=j+dy[k];
				if(x>=0&&x<5&&y>=0&&y<5) 
					op[cur][cnt[cur]++]=x*5+y;
			}
		}
	
	cin>>T;
	while(T--) {
		M.clear();
		a.clear();
		for(i=0;i<25;i++) {
			cin>>ch;
			if(ch=='*') cur=i;
			a=a+ch;
		}
		depth=0;
		while(!dfs(1,depth,cur)) {
			depth++;
			if(depth>15) break;
		}
		if(depth>15) printf("-1\n");
		else printf("%d\n",depth);
	}
		
	return 0;
}

