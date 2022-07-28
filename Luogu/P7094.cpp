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


int T;
LL a,b,c,d;

int main()
{
//	freopen("1.in","r",stdin);
	int y;
	
	cin>>T;
	while(T--) {
		int ans=0;
		cin>>a>>b>>c>>d;
		for(y=1;b*y<d*c;y++) {
			if(a*c*y%(d*c-b*y)==0)
				ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}

