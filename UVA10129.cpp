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

const int N=256;

int T,n;
int din[N],dout[N];
string s;

int w[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,x,y;
	
	scanf("%d",&T);
	while(T--) {
		memset(din,0,sizeof din);
		memset(dout,0,sizeof dout);
		memset(w,0,sizeof w);
		
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			cin>>s;
			x=s[0]-'a',y=s[s.length()-1]-'a';
			dout[x]++;
			din[y]++;
			w[x][y]=1;
		}
		
		for(k=0;k<26;k++) 
			for(i=0;i<26;i++) 
				for(j=0;j<26;j++) 
					w[i][j]=w[i][j]|(w[i][k]&w[k][j]);
		
		for(i=0;i<26;i++) {
			if(dout[i]+din[i]==0) continue;
			for(j=0;j<26;j++) {
				if(dout[j]+din[j]==0||i==j) continue;
				else if(w[i][j]+w[j][i]==0) 
					break;
			}
			if(j<26) break;
		}
		
		if(i<26) {
			printf("The door cannot be opened.\n");
			continue;
		}
		
		int cnt1=0,cnt2=0;
		for(i=0;i<26;i++) {
			if(din[i]-dout[i]==1) cnt1++;
			else if(dout[i]-din[i]==1) cnt2++;
			else if(din[i]!=dout[i]) break;
		}
		if(i==26) {
			if((cnt1==1&&cnt2==1)||(cnt1==cnt2&&cnt1==0))
				printf("Ordering is possible.\n");
			else printf("The door cannot be opened.\n");
		}
		else printf("The door cannot be opened.\n");
	}
	return 0;
}

