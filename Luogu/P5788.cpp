#include<cstdio>
#include<iostream>
#include<stack>
#define LL long long
using namespace std;
const int N=3e6+5;
stack< pair<int,int> > S;
int n;
int a[N],f[N];
template<class T>
inline void read(T &x)
{
	char c=getchar();
	bool flag=false;
	x=0;
	while(c<'0'||c>'9') {
		if(c=='-') flag=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	x=((flag) ? (~x+1) :(x));
	return;
}
int main()
{
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n;i++) {
		while(S.size()&&a[i]>S.top().first) {
			f[S.top().second]=i;
			S.pop();
		}
		S.push(pair<int,int>(a[i],i));
	}
	for(i=1;i<=n;i++) 
		printf("%d ",f[i]);
	return 0;
}

