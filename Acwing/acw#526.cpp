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

int T,n;
string times;

int row; // 已经读入了几行 

string ans;

set<char> S;

void read(int &x,string &s)
{
	x=0;
	for(int i=0;i<(int)s.length();i++) 
		x=x*10+(s[i]-'0');
}

int found()
{
	char ForE='\0',item;
	string num1,num2;
	int tmp;
	bool f1=false;
	int k=0,res=0,x,y;
	cin>>item>>num1>>num2;
	if(S.count(item)) ans="ERR";
	else S.insert(item);
	
	if(num1=="n"&&num2=="n") k=0; // O(n^0)
	else if(num1=="n") k=0,f1=true; // 后面无论怎样都不造成复杂度 
	else {
		read(x,num1);
		if(num2=="n") k=1; // O(n^1)
		else {
			read(y,num2);
			if(x>y) k=0,f1=true; // none
			else k=0; // O(n^0) 
		}
	}
	res=k;
	while(row<n&&cin>>ForE&&ForE=='F') {
		row++;
		tmp=found();
		if(!f1) res=max(res,k+tmp); 
	}
	row++;
	if(ForE!='E') ans="ERR";
	S.erase(item);
	return res;
}


int main()
{
//	freopen("1.in","r",stdin);
	int cmax;
	char c;
	cin>>T;
	while(T--) {
		cin>>n>>times;
//		cout<<n<<" "<<times<<endl;
		cmax=row=0;
		S.clear();
		ans="Remain";
		if(n&1) ans="ERR";
		while(row<n&&cin>>c&&c=='F') row++,cmax=max(cmax,found());
		
		if(row<n) {
			ans="ERR";
			for(row++;row<=n;row++) 
				getline(cin,times);
		}
		
		if(ans=="ERR") cout<<ans<<endl;
		else {
			if(cmax==0) {
				if(times=="O(1)") printf("Yes\n");
				else printf("No\n");
			}
			else {
				string g;
				while(cmax) g=g+char(cmax%10+'0'),cmax/=10;
				reverse(g.begin(),g.end());
				if(times=="O(n^"+g+")") printf("Yes\n");
				else printf("No\n");
			}
		}
	}
	return 0;
}

