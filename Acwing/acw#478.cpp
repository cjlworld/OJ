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

const int N=256;
int m,n,p;

string names[N];
string days[N]={"","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday",""};

int check(string f,string s,string t)
{
	for(int j=0;j<m;j++) 
		if(s==f+names[j]+t) return j;
	return -1;
}
int checkday(string s)
{
	for(int i=1;i<=7;i++) 
		if(s==" Today is "+days[i]+".") return i;
	return -1;
}

int day[N]; // 0 表示没说，否则几就是星期几。 
int v[N][N];

void Set(int x,int y,int k)
{
	if(v[x][y]!=-1&&v[x][y]!=k) {
		printf("Impossible\n");
		exit(0);
	}
	else v[x][y]=k;
}

int g[N]; // 是1，不是0，待定-1 
int fd[N];

vector<int> gg;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	cin>>m>>n>>p;
	for(i=0;i<m;i++) 
		cin>>names[i];
	
	string name,s,t;
	memset(v,-1,sizeof v);
	for(i=1;i<=p;i++) {
		cin>>name;
		x=check("",name,":"); // 第x个人说的。
		getline(cin,s);
  //      s.erase(s.end()-1);
		if(s==" I am guilty.") Set(x,x,1);
		else if(s==" I am not guilty.") Set(x,x,0);
		else if(~(y=check(" ",s," is guilty."))) Set(x,y,1);
		else if(~(y=check(" ",s," is not guilty."))) Set(x,y,0);
		else if(~(y=checkday(s))) day[x]=y; // ? 也许一个人会说两个时间 
	}
	bool have=false;
	
	for(i=0;i<(1<<m);i++) { // 枚举说假话的人 
		int cnt=0;
		for(j=0;j<m;j++) 
			cnt+=((i>>j)&1);
		if(cnt!=n) continue;
		
		memset(g,-1,sizeof g);
		memset(fd,-1,sizeof fd);
		bool flag=false;
		
		for(x=0;x<m;x++) {
			k=(i>>x)&1;
			for(y=0;y<m;y++) {
				if(v[x][y]>=0) {
					if(g[y]==(v[x][y]^k^1)) flag=true;
					else g[y]=(v[x][y]^k);
				}
				if(flag) break;
			}
			if(day[x]!=0) {
				if(fd[day[x]]==k) flag=true;
				else fd[day[x]]=(k^1); 
			}
			if(flag) break;
		}
		if(flag) continue;
		have=true;
		cnt=0;
		for(j=1;j<=7;j++) 
			if(fd[j]==1) cnt++;
		if(cnt>1) continue;
		
		
		// 自恰
// 		for(j=0;j<m;j++) 
// 		    printf("%d",(i>>j)&1);
// 		printf(" : ");
// 		for(j=0;j<m;j++) 
// 			cout<<g[j]<<" ";
// 		cout<<endl;

		int cnt0=0,cnt1=0;
		for(j=0;j<m;j++) {
			if(g[j]==1) cnt1++,x=j;
			if(g[j]==0) cnt0++;
			else y=j;
		}
		if(cnt1==1) gg.push_back(x);
		else if(cnt0==m-1) gg.push_back(y);
	}
	sort(gg.begin(),gg.end());
	gg.erase(unique(gg.begin(),gg.end()),gg.end());	
	if(!have) cout<<"Impossible"<<endl;
    else if(gg.size()==1) cout<<names[gg[0]]<<endl;
    else cout<<"Cannot Determine"<<endl;
	return 0;
}
