#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
//对于100%的数据，1 ≤ N ≤ 100,000，0 ≤ M ≤ 10,000
const int N=100000+5;
const int SQ=1000;
vector<int> bl[SQ];
int n,m;
int siz;
char opt[26];
int cnt=0;
inline void Sw(int pos,int x,int y)
{
	int temp=bl[pos][x];
	bl[pos][x]=bl[pos][y];
	bl[pos][y]=temp;
	return;
}
inline void Add(int pos,int x)
{
	int i,j;
	i=bl[pos].size();
	bl[pos].push_back(x);
	while(i-1>=0&&bl[pos][i-1]>x) Sw(pos,i,i-1),i--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	siz=ceil(sqrt(n));
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		bl[0].push_back(x);
	}
	cnt=n;
	sort(bl[0].begin(),bl[0].end());
	for(i=0;i<n;i++) 
		bl[i/siz+1].push_back(bl[0][i]);
	scanf("%d",&m);
	while(m--) {
		scanf("%s",opt);
		if(opt[0]=='a') {
			cnt++;
			scanf("%d",&x);
			for(i=1;i<=siz;i++) {
				if(bl[i].empty()||x<=bl[i].back()) 
					break;
			}
			Add(i,x);
		}
		else {
			if(cnt&1) y=(cnt+1)>>1;
			else y=cnt>>1;
			z=0;
			for(i=1;i<=n;i++) {
				if(z+bl[i].size()>=y) {
					cout<<bl[i][y-z-1]<<endl;
					break;
				}
				z+=bl[i].size();
			}
		}
	}
	return 0;
}

