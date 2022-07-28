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
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;

const int N=3e5+20;
const LL INF=0x3f3f3f3f3f3f3f3f;

int n,m;
char a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	int i,k,num;
	m=130;
	memset(c,0,sizeof c);
	
	for(i=1;i<=n;i++) c[x[i]=a[i]]++;
	for(i=1;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i;
	
	for(k=1;k<=n;k<<=1) {
		num=0;
		for(i=n-k+1;i<=n;i++) y[++num]=i;
		for(i=1;i<=n;i++) 
			if(sa[i]>k) y[++num]=sa[i]-k;
		
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[x[i]]++;
		for(i=1;i<=m;i++) c[i]+=c[i-1];
		for(i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		
		swap(x,y);
		x[sa[1]]=1,m=1;
		for(i=2;i<=n;i++)
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? m : ++m);
		if(m==n) break;
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
}

void get_ht()
{
	for(int i=1,j,k=0;i<=n;i++) {
		if(rk[i]==1) continue;
		if(k) k--;
		j=sa[rk[i]-1];
		while(i+k<=n && j+k<=n && a[i+k]==a[j+k]) k++;
		ht[rk[i]]=k;
	}
}

int stmin[N][20],stmax[N][20];

int rmqmin(int x,int y)
{
	int k=log2(y-x+1);
	return min(stmin[x][k],stmin[y-(1<<k)+1][k]);
}
int rmqmax(int x,int y)
{
	int k=log2(y-x+1);
	return max(stmax[x][k],stmax[y-(1<<k)+1][k]);
}

LL b[N],tmp[N];
int id[N],all;

priority_queue<PII> q;

int pr[N],pl[N]; // pr[],pl[] 维护相同颜色极长段。 
int Find(int par[],int x)
{
	if(par[x]!=x) return par[x]=Find(par,par[x]);
	else return x;
}

LL ansc=0,ansmax=-INF;

void add(int l,int r,int x)
{   
//	cerr<<"add : "<<"("<<l<<","<<r<<") , "<< x<<endl;
	ansmax=max(ansmax,rmqmax(l,r)*b[x]);
	ansmax=max(ansmax,rmqmin(l,r)*b[x]);
	ansc+=r-l+1;
	
	id[x]=id[l];
	pl[l]=pl[x]=min(pl[l],x);
	pr[r]=pr[x]=max(pr[r],x);
}

void merge(int l1,int r1,int l2,int r2)
{
	if(r1-l1<r2-l2) 
		return merge(l2,r2,l1,r1);
//	printf("here merge (%d , %d) with (%d , %d) and now ansc is %lld\n",l1,r1,l2,r2,ansc);
	for(int i=l2;i<=r2;i++)	
		add(l1,r1,i); 
//	printf("after the merge , ansc is %lld\n",ansc);
}

vector<PLL> ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	
	scanf("%d",&n);
	scanf("%s",a+1);
	get_sa(),get_ht();
	
	for(i=1;i<=n;i++) 
		scanf("%lld",&tmp[i]);	
	for(i=1;i<=n;i++) 
		stmin[i][0]=stmax[i][0]=b[i]=tmp[sa[i]];
	
	for(j=1;(1<<j)<=n;j++) {
		for(i=1;i+(1<<j)-1<=n;i++) {
			stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
			stmin[i][j]=min(stmin[i][j-1],stmin[i+(1<<(j-1))][j-1]);
		}
	}
	
	for(i=1;i<=n+19;i++) pl[i]=pr[i]=i;
	for(i=2;i<=n;i++) q.push(PII(ht[i],i-1));
	
	
	for(i=n-1;i>=0;i--) {
		while(q.size() && q.top().first>=i) {
			x=q.top().second; q.pop();
			
			if(!id[x] && !id[x+1]) {
				id[x]=id[x+1]=++all;
				ansmax=max(ansmax,b[x]*b[x+1]);
				ansc++;
				pr[x]=x+1,pl[x+1]=x;
				
//				printf("two points %d merge : %d , %d\n",i,x,x+1);
//				cout<<i<<" : "<<b[x]<<" "<<b[x+1]<<endl;
			}
			
			else if(!id[x]) {
			//	cerr<<x<<endl;
				y=Find(pr,x+1);
				add(x+1,y,x);
			}
			
			else if(!id[x+1]) {
				y=Find(pl,x);
				add(y,x,x+1);
			}
			
			else {
				y=Find(pl,x);
				z=Find(pr,x+1);
				merge(y,x,x+1,z);
			}
		}
		
		ans.push_back(PLL(ansc,ansmax));
		
//		printf("print the all ids : ");
//		for(int j=1;j<=n;j++) printf("%d ",id[j]);
//		printf("\n");
//		printf("now ansc is %lld\n",ansc);
	}
	
	for(;ans.size();ans.pop_back()) {
		ansc=ans.back().first; 
		ansmax=ans.back().second;
		
		if(ansmax==-INF) ansmax=0;
		
		printf("%lld %lld\n",ansc,ansmax);
	}
	
	return 0;
}
//int sth[N][20];
//int lcp(int x,int y)
//{
//	int k=log2(y-x+1);
//	return min(sth[x][k],sth[y-(1<<k)+1][k]);
//}
// //		sth[i][0]=ht[i];
//			sth[i][j]=min(sth[i][j-1],sth[i+(1<<(j-1))][j-1]);

// DeBug : 
//  1. sa[] 映射忘了。 
//  2. 方案数看成最小值。 
//  3. 不一定相邻且 id[] 就在同一个块了。
//  4. pr[],pl[] 维护相同颜色极长段。 严格遵循定义。 
//  5. x 写成 z 了。 
//  6. merge 中的 add , 由于不是相邻的加进来，要小心。 

