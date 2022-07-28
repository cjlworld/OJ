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

const int N=5000+5;

int n,R,ans;
int s[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&R);
	while(n--) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		s[x][y]+=z;
	}
	n=5001;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++)
			s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
	if(R>=n) ans=s[n][n];
	for(i=R;i<=n;i++) // Ã¶¾Ù×óÏÂ½Ç×ø±ê 
		for(j=R;j<=n;j++) 
			ans=max(ans,s[i][j]-s[i-R][j]-s[i][j-R]+s[i-R][j-R]);
	cout<<ans<<endl;
	return 0;
}

