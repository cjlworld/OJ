#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=500+5;
const int INF=0x3f3f3f3f;

/*
void read(char *str,int &x) 
{
	x=0;
	for(int i=0;'0'<=str[i] && str[i]<='9';i++) 
		x=x*10+(str[i]-'0');
}
*/

string str;
int b[N];
int Readstr() // ��һ�в����ض�ȡ�����ָ��� 
{
//	gets(str);
	getline(cin,str);
	int sum=1; b[1]=0; // sum Ϊ����������¼���ڶ�ȡ�������ǵڼ��������Ѷ��꣬��ָ����һ���� 
	for(int i=0;i<(int)str.length();i++) {
		if('0'<=str[i] && str[i]<='9') b[sum]=b[sum]*10+(str[i]-'0');
		else if(b[sum]!=0) b[++sum]=0;
		else continue;
	}
	if(b[sum]==0) sum--;
	return sum;
}

int n,m; // ��վ����·�������� 
int edge[N][N];

queue<int> q;
bool vis[N];
int dis[N];

void bfs() 
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	
	q.push(1);
	dis[1]=0; vis[1]=true;
	
	int x;
	while(!q.empty()) {
		x=q.front(); q.pop();
		for(int i=1;i<=n;i++) 
			if(!vis[i] && edge[x][i]) {
				vis[i]=true;
				dis[i]=dis[x]+1;
				q.push(i);
			}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	Readstr();
	m=b[1]; n=b[2];
	for(int i=1;i<=m;i++) {
		int sum=Readstr();
		for(int j=1;j<=sum;j++) 
			for(int k=j+1;k<=sum;k++) 
				edge[b[j]][b[k]]=1;
	}
	bfs();
	if(dis[n]==INF) printf("NO\n");
	else printf("%d\n",dis[n]-1);
	return 0;
}

