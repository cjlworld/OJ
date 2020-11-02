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

int mark(int x,int y)
{
	return min(min(x,8-x),min(y,8-y))+6;
}

const int N=16,M=2e4+5;

int a[N][N];
bool used[N][N][N],usn[N][N],usm[N][N];
int kk[M],kx[M],ky[M],cnt;

int n=9,m=324,sum,ans;

int l[M],r[M],u[M],d[M];
int s[M],row[M],col[M],one[M],idx;

void init()
{
	for(int i=0;i<=m;i++) {
		l[i]=i-1,r[i]=i+1;
		u[i]=d[i]=i;
	}
	l[0]=m,r[m]=0;
	idx=m;
	memset(s,0,sizeof s);
	memset(one,0,sizeof one);
}
void add(int x,int y)
{
	idx++; row[idx]=x,col[idx]=y,s[y]++;
	u[idx]=y,d[idx]=d[y],u[d[idx]]=idx,d[y]=idx;
	if(!one[x]) one[x]=l[idx]=r[idx]=idx;
	else {
		r[idx]=r[one[x]],l[r[idx]]=idx;
		r[one[x]]=idx,l[idx]=one[x];
	}
}

void addoption(int i,int j,int k)
{
	kk[++cnt]=k,kx[cnt]=i,ky[cnt]=j;
	add(cnt,i*9+j+1);
	add(cnt,81+i*9+k);
	add(cnt,81*2+j*9+k);
	add(cnt,81*3+((i/3)*3+(j/3))*9+k);
}


void remove(int p)
{
	r[l[p]]=r[p],l[r[p]]=l[p];
	int i,j;
	for(i=d[p];i!=p;i=d[i]) // 这一列选了，删除与这一列有关的行	
		for(j=r[i];j!=i;j=r[j]) {
			s[col[j]]--;
			d[u[j]]=d[j],u[d[j]]=u[j];
		}
}

void resume(int p)
{
	int i,j;
	for(i=u[p];i!=p;i=u[i]) 
		for(j=l[i];j!=i;j=l[j]) {
			u[d[j]]=d[u[j]]=j;
			s[col[j]]++;
		}
	r[l[p]]=l[r[p]]=p;
}

void dance()
{
	if(!r[0]) return ans=max(ans,sum),void();
	int p=r[0],i,j;
	for(i=r[p];i;i=r[i]) 
		if(s[i]<=s[p]) p=i;
	remove(p);
	for(i=d[p];i!=p;i=d[i]) {
		sum+=mark(kx[row[i]],ky[row[i]])*kk[row[i]];
		for(j=r[i];j!=i;j=r[j]) remove(col[j]);
		dance();
		for(j=l[i];j!=i;j=l[j]) resume(col[j]);
		sum-=mark(kx[row[i]],ky[row[i]])*kk[row[i]];
	}
	resume(p);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	init();
	for(i=0;i<n;i++) 
		for(j=0;j<n;j++) {
			scanf("%d",&a[i][j]);
			used[i/3][j/3][a[i][j]]=usn[i][a[i][j]]=usm[j][a[i][j]]=(a[i][j]>0);
		}
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			if(a[i][j]) 
				addoption(i,j,a[i][j]);
			else {
				for(k=1;k<=9;k++) 
					if(!used[i/3][j/3][k]&&!usn[i][k]&&!usm[j][k]) 
						addoption(i,j,k);// 不与现有状态冲突 
			}
		}
	}
	dance();
	if(ans==0) printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}

