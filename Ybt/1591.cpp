#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=25;
int dim[N];
LL f[N][N][N];//第i位放j所得k的个数 
LL tmp;
LL pow10[N]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000};
LL dfs(int now,int sta,int cnt,bool lit)
{
	if(now==0) return 0;
	if(!lit&&f[now][sta][cnt]!=-1) 
		return f[now][sta][cnt];
	LL res=0;
	int maxn=(lit) ? dim[now-1] : 9; //??
	for(int i=0;i<=maxn;i++) {
		res+=dfs(now-1,i,cnt,(lit&&i==maxn)); 
	}
	if(sta==cnt) {
		if(lit) res+=tmp%(pow10[now-1])+1;
		else res+=pow10[now-1];
	}
	if(!lit) f[now][sta][cnt]=res;
	return res;
}
LL prefix(LL x,int cnt)
{
	memset(dim,0,sizeof dim);
	memset(f,-1,sizeof(f));
	int top=0;
	tmp=x;
	while(x>0) {
		dim[++top]=x%10;
		x/=10;
	}
	LL res=0;
	for(int i=1;i<=dim[top];i++) 
		res+=dfs(top,i,cnt,(i==dim[top]));
	for(int j=1;j<=top-1;j++) {
		for(int i=1;i<=9;i++) {
			res+=dfs(j,i,cnt,false);	
		}
	}
	return res;
}
int main()
{
	LL a,b;
	cin>>a>>b;
	LL ans=0;
	for(int i=0;i<=9;i++) {
		ans=prefix(b,i);
		ans-=prefix(a-1,i);
		cout<<ans<<" ";
	}
//	cout<<std::endl;
//	for(int i=0;i<=9;i++) {
//		cout<<prefix(a-1,i)<<" ";
//	}
//	cout<<std::endl;
//	for(int i=0;i<=9;i++) {
//		cout<<prefix(b,i)<<" ";
//	}
	return 0;
}

