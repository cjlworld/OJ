#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<stack>
using namespace std;
struct data
{
	int sum;
	int cmax;
	int pre;
}f[1024];
int a[1024];
stack<int> ans;
void print(int x)
{
//	cout<<a[x]<<" ";
	ans.push(a[x]);
	if(f[x].sum!=0) print(f[x].sum);
}
int main()
{
//	freopen("1.in","r",stdin);
	int n;
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	a[0]=-1;
	for(i=1;i<=n;i++) {
		for(j=0;j<i;j++) {
			if(a[i]>=a[j]&&f[j].cmax+1>=f[i].cmax) {
//				if(f[j].cmax+1>f[i].cmax||(f[j].cmax+1==f[i].cmax&&a[j]<f[i].pre)) {
					f[i].cmax=f[j].cmax+1;
					f[i].sum=j;
//					f[i].pre=a[j];
//				}
			}
		}
	}
	int s=-1,s_=0;
	for(i=1;i<=n;i++) {
		if(s<f[i].cmax) {
			s=f[i].cmax;
			s_=i;
		}
	}
	cout<<"max="<<s<<endl;
//	cout<<a[s_]<<" ";
	print(s_);
	while(!ans.empty()) {
		cout<<ans.top()<<" ";
		ans.pop();
	}
	return 0;
}

