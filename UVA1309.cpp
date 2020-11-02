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

const int N=18,M=3e4+5;

int a[N][N];
bool used[N][N][N],usn[N][N],usm[N][N];
int kk[M],kx[M],ky[M],cnt;

int n=16,m=1024;

int l[M],r[M],u[M],d[M];
int s[M],row[M],col[M],one[M],idx;

void init()
{
	memset(l,0,sizeof l);
	memset(r,0,sizeof r);
	memset(u,0,sizeof u);
	memset(d,0,sizeof d);
	for(int i=0;i<=m;i++) {
		l[i]=i-1,r[i]=i+1;
		u[i]=d[i]=i;
	}
	l[0]=m,r[m]=0;
	idx=m;
	memset(s,0,sizeof s);
	memset(one,0,sizeof one);
	memset(row,0,sizeof row);
	memset(col,0,sizeof col);
	
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
	add(cnt,i*16+j+1);
	add(cnt,256+i*16+k);
	add(cnt,256*2+j*16+k);
	add(cnt,256*3+((i/4)*4+(j/4))*16+k);
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

bool dance()
{
	if(!r[0]) return true;
	int p=r[0],i,j;
	for(i=r[p];i;i=r[i]) 
		if(s[i]<=s[p]) p=i;
	remove(p);
	for(i=d[p];i!=p;i=d[i]) {
		a[kx[row[i]]][ky[row[i]]]=kk[row[i]];
		for(j=r[i];j!=i;j=r[j]) remove(col[j]);
		if(dance()) return true;
		for(j=l[i];j!=i;j=l[j]) resume(col[j]);
		a[kx[row[i]]][ky[row[i]]]=0;
	}
	resume(p);
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,T=0;
	char ch;
	while(cin>>ch) {
		if(T!=0) putchar('\n');
		T++;
		
		init();
		memset(used,0,sizeof used);
		memset(usn,0,sizeof usn);
		memset(usm,0,sizeof usm);
		memset(a,0,sizeof a);
		cnt=0;
		memset(kk,0,sizeof kk);
		memset(kx,0,sizeof kx);
		memset(ky,0,sizeof ky);
		
		for(i=0;i<n;i++) 
			for(j=0;j<n;j++) {
				if(i!=0||j!=0) cin>>ch;
				if(ch=='-') a[i][j]=0;
				else a[i][j]=ch-'A'+1;
				used[i/4][j/4][a[i][j]]=usn[i][a[i][j]]=usm[j][a[i][j]]=(a[i][j]>0);
			}
		for(i=0;i<n;i++) 
			for(j=0;j<n;j++) {
				if(a[i][j]) addoption(i,j,a[i][j]);
				else {
					for(k=1;k<=16;k++) 
						if(!used[i/4][j/4][k]&&!usn[i][k]&&!usm[j][k]) 
							addoption(i,j,k);// 不与现有状态冲突 
				}
			}
		dance();
		for(i=0;i<n;i++,putchar('\n')) 
			for(j=0;j<n;j++)
				putchar(a[i][j]+'A'-1);
	}
	return 0;
}

