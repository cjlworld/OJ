#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<bitset>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=15,S=(1<<9)-1;
int a[N][N];
int h[N],l[N],u[N][N];
void print()
{
	for(int i=1;i<=9;i++,putchar('\n')) 
		for(int j=1;j<=9;j++)
			printf("%d",a[i][j]);
	printf("\n");
	return;
}
char c[N*N];
int ones[S+5]; 
bool flag;
int lowbit(int x)
{
	return x&(-x);
}
int count(int x)
{
	int res=0;
	for(;x>0;res++,x-=lowbit(x));
	return res;
}
void dfs(int step)
{
//	print();
//	cout<<step<<endl;
	int x=-1,y=-1;
	int i,j;
	int cmin=20;
	for(i=1;i<=9;i++) 
		for(j=1;j<=9;j++) {
			if(a[i][j]==0&&ones[h[i]&l[j]&u[(i-1)/3+1][(j-1)/3+1]]<cmin) {
				cmin=ones[h[i]&l[j]&u[(i-1)/3+1][(j-1)/3+1]];
				x=i; y=j;
			}
		} 
	if(x==-1) {
		flag=true;
		for(int i=1;i<=9;i++) 
			for(int j=1;j<=9;j++) 
				printf("%d",a[i][j]);
		printf("\n");
		return;
	} 
	int nums=h[x]&l[y]&u[(x-1)/3+1][(y-1)/3+1];
	while(nums>0) {
		i=log2(lowbit(nums))+1;
		nums-=lowbit(nums);
		
		h[x]-=1<<(i-1); l[y]-=1<<(i-1); u[(x-1)/3+1][(y-1)/3+1]-=1<<(i-1);
		
		a[x][y]=i;
		dfs(step+1);
		if(flag) return;
		a[x][y]=0;
		
		h[x]+=1<<(i-1); l[y]+=1<<(i-1); u[(x-1)/3+1][(y-1)/3+1]+=1<<(i-1);
	}
//	for(int i=1;i<=9;i++) {
//		if(check(x,y,i)) {
//			update(x,y,i,true);
//			a[x][y]=i;
//			dfs(step+1);
//			if(flag) return;
//			a[x][y]=0;
//			update(x,y,i,false);
//		}
//	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,j,x,y;
	for(i=1;i<=S;i++) 
		ones[i]=count(i);
	while(scanf("%s",c+1)==1) {
		if(c[1]=='e') return 0;
		memset(a,0,sizeof a);
		fill(h,h+11,S);
		fill(l,l+11,S);
		for(i=1;i<=3;i++) 
			for(j=1;j<=3;j++) 
				u[i][j]=S;
		for(i=1;i<=81;i++) {
			x=(i-1)/9+1; y=(i-1)%9+1;
			if(c[i]=='.') a[x][y]=0;	
			else {
				a[x][y]=(c[i]-'0');
				h[x]-=1<<(a[x][y]-1); l[y]-=1<<(a[x][y]-1); u[(x-1)/3+1][(y-1)/3+1]-=1<<(a[x][y]-1);
			}
		}
		flag=false;
//		print();
		dfs(1);
	}
	return 0;
}
//inline bool check(int x,int y,int num)
//{
//	if()(h[x]>>(num-1)&1) return false;
//	else if(l[y]>>(num-1)&1) return false;
//	else if(u[(x-1)/3+1][(y-1)/3+1]>>(num-1)&1) return false;
//	return true;
//}
//inline void update(int x,int y,int num,bool p)
//{
//	h[x][num]=p;
//	l[y][num]=p;
//	u[(x-1)/3+1][(y-1)/3+1][num]=p;
//	return;
//}
