#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
using namespace std;
struct vol
{
	int id;
	int mark;
}c[10000];
int main()
{
	double m;
	int i,j,n,k;
	int line,num;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>c[i].id>>c[i].mark;
	}
	for(i=n-1;i>=1;i--)
	for(j=1;j<=i;j++)
	{
		if(c[j].mark<c[j+1].mark) 
			swap(c[j],c[j+1]);
		else if(c[j].mark==c[j+1].mark)
		{
			if(c[j].id>c[j+1].id)
				swap(c[j],c[j+1]);
		}
	}
	k=floor(m*1.5);
	cout<<c[k].mark<<" ";
	i=1;
	while(c[i].mark>=c[k].mark)
	{
		i++;
	}
	i--;
	cout<<i<<endl;
	for(j=1;j<=i;j++)
	{
		cout<<c[j].id<<" "<<c[j].mark<<endl;
	}
}
