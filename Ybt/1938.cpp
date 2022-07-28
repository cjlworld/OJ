#include<bits/stdc++.h>
using namespace std;
struct student 
{
	int c;
	int m;
	int e;
	int mark;
	int o;
}a[100000];
bool rule(const student &a,const student &b)
{
	if(a.mark>b.mark) return true;
	else if(a.mark<b.mark) return false;
	else {
		if(a.c>b.c) return true;
		else if(a.c<b.c) return false;
		else {
			if(a.o<b.o) return true;
			else return false;
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	int n;
	cin>>n;
	int i,j;
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&a[i].c,&a[i].m,&a[i].e);
		a[i].mark=a[i].c+a[i].m+a[i].e;
		a[i].o=i;
	}
	sort(a+1,a+n+1,rule);
	for(i=1;i<=5;i++) {
		cout<<a[i].o<<" "<<a[i].mark<<endl;
	}
	return 0;
}
