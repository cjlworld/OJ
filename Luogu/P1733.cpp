#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
int main()
{
	int res;
	int L=0,R=1e9+1,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		cout<<mid<<endl;
		cin>>res;
		switch(res) {
			case 1 : {
				R=mid;
				break;
			}
			case 0 : {
				return 0;
				break;
			}
			case -1 : {
				L=mid;
				break;
			}
		}
	}
	return 0;
}

