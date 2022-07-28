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
namespace FastIO
{
	const int _SIZE = (1 << 21) + 1;
	char ibuf[_SIZE],c;
	char *iS,*iT;
	bool sign;
	inline char NextChar()
	{
		if(iS==iT) 
			iS=ibuf,iT=iS+fread(ibuf,1,_SIZE,stdin);
		return (iS == iT ? EOF : *iS++);
	}
	template <class T>
	inline void read(T &x) 
	{
		x=0;
		sign=false;
	    for (c=NextChar();c<'0'||c>'9';c=NextChar())
	        if (c=='-') sign=true;
	    for (;c>='0'&&c<='9';c=NextChar()) 
			x=(x<<1)+(x<<3)+(c&15);
		if(sign) x=-x;
	}
} 
using FastIO::read;

const int N=1e5+5;
int T,n;
vector<int> nums,ans;
int a[N],cnt[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int cmax;
	read(T);
	while(T--) {
		nums.clear(),ans.clear();
		read(n);
		for(i=1;i<=n;i++) {
			read(a[i]);
			nums.push_back(a[i]);
		}
		sort(nums.begin(),nums.end());
		nums.erase(unique(nums.begin(),nums.end()),nums.end());
		for(i=0;i<(int)nums.size();i++) 
			cnt[i]=0;
		for(i=1;i<=n;i++) {
			a[i]=(int)(lower_bound(nums.begin(),nums.end(),a[i])-nums.begin());
			cnt[a[i]]++;
		}
		cmax=0;
		for(i=0;i<(int)nums.size();i++) 
			cmax=max(cmax,cnt[i]);
		for(i=0;i<(int)nums.size();i++) 
			if(cnt[i]==cmax)
				ans.push_back(i);
		if(ans.size()==nums.size()) printf("-1\n");
		else {
			printf("%llu\n",ans.size());
			for(i=0;i<(int)ans.size();i++) 
				printf("%d ",nums[ans[i]]);
			printf("\n");
		}
	}
	return 0;
}
