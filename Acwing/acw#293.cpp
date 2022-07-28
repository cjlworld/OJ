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

const int N=1e5+5;
const LL INF=1e12;

int n,m,k;
LL h[N];
int a[N],b[N]; 
// a[i] 表示在第i座城市，轮到小A开车，下一个的城市的编号，没有就为0.
// b[i] 同理。 
map<LL,int> Mp; // h数组下标和数值的映射。 
set<LL> S;

inline LL mabs(LL a)
{
	if(a<0) return -a;
	else return a;
}

LL f[N][21]; 
// f[i][j] 表示从i出发，是 小A 开车
int g[N][21]; // 表示 f[...] 所走到的点。 
LL fa[N][21];

void Find(int cur,LL dist,LL &ad,LL &bd)
{
	LL pdis=0;
	ad=bd=0;
	
	for(int i=k;i>=0;i--) 
		if(pdis+f[cur][i]<=dist) {
			pdis+=f[cur][i];
			ad+=fa[cur][i];
			cur=g[cur][i];
		}
	bd=pdis-ad;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	scanf("%d",&n);
	while((1<<k)<n) k++;
	for(i=1;i<=n;i++) {
		scanf("%lld",&h[i]);
		Mp[h[i]]=i;
	}
	h[0]=INF;
	Mp[INF]=0;
	
	set<LL>::iterator itl,itr;
	for(i=n;i>=1;i--) {
		// 处理小B 
		if(S.size()) {
			itl=S.lower_bound(h[i]); itl--;
			itr=S.upper_bound(h[i]);
			
			if(itr!=S.end()) b[i]=Mp[*itr];
			if(itr==S.end()||(h[i]>*S.begin()&&h[i]-*itl<=h[Mp[*itr]]-h[i])) 
				b[i]=Mp[*itl];
		}
		// 处理小A
		if(S.size()>=2) {
			itl=S.lower_bound(h[i]); itl--;
			itr=S.upper_bound(h[i]);
			
			x=y=0;
			
			if(itr!=S.end()) x=Mp[*itr];
			if(h[i]>*S.begin()) y=Mp[*itl];
			
//			printf("%lld %lld\n",h[x],h[y]);
			if(mabs(h[i]-h[y])<=mabs(h[i]-h[x])) {
				if(itl==S.begin()) a[i]=x;
				else {
					itl--;
					if(mabs(h[i]-*itl)<=mabs(h[i]-h[x])) a[i]=Mp[*itl];
					else a[i]=x;
				} 
			}
			else {
				if(itr==(--S.end())) a[i]=y;
				else {
					itr++;
					if(mabs(h[i]-h[y])<=mabs(h[i]-*itr)) a[i]=y;
					else a[i]=Mp[*itr];
				}
			}
		} 
		S.insert(h[i]);
	}
	
//	for(i=1;i<=n;i++) 
//		printf("%d ",b[i]);
//	printf("\n");
//	for(i=1;i<=n;i++) 
//		printf("%d ",a[i]);

	for(i=1;i<=n;i++) {
		g[i][0]=a[i];
		f[i][0]=mabs(h[a[i]]-h[i]);
		fa[i][0]=f[i][0];
	}
	for(i=1;i<=n;i++) {
		g[i][1]=b[g[i][0]];
		f[i][1]=f[i][0]+mabs(h[g[i][1]]-h[g[i][0]]);
		fa[i][1]=f[i][0];
	}
	
	for(i=2;i<=k;i++) 
		for(j=1;j<=n;j++) {
			x=g[j][i-1];
			g[j][i]=g[x][i-1];
			f[j][i]=f[j][i-1]+f[x][i-1];
			fa[j][i]=fa[j][i-1]+fa[x][i-1];
		}
	
	LL dist,disa,disb;
	scanf("%lld",&dist);
	LL aa,bb;
	x=1;
	Find(1,dist,aa,bb);
	for(i=2;i<=n;i++) {
		Find(i,dist,disa,disb); 
		if(disa==0&&disb==0&&bb!=0) continue;
		if(disa*bb<aa*disb||(disa*bb==aa*disb&&h[i]>h[x]))
			aa=disa,bb=disb,x=i;
	}
	printf("%d\n",x);
	
	scanf("%d",&m);
	while(m--) {
		scanf("%d%lld\n",&x,&dist);
		Find(x,dist,disa,disb);
		printf("%lld %lld\n",disa,disb);
	}
	return 0;
}

