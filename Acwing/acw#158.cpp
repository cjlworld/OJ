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

string minshow(string s)
{
	string ss=s+s;
	int i=0,j=1,k,len=s.length();
	while(i<len&&j<len) {
		for(k=0;k<len&&ss[i+k]==ss[j+k];k++);
		if(k==len) break;
		if(s[i+k]>s[j+k]) {
			i+=k+1;
			if(i==j) i++;
		}
		else {
			j+=k+1;
			if(i==j) j++;
		}
 	}
 	return ss.substr(min(i,j),len);
}

int main()
{
//	freopen("1.in","r",stdin);
	string a,b;
	getline(cin,a),getline(cin,b);
	a=minshow(a),b=minshow(b);
	if(a==b) printf("Yes\n%s\n",a.c_str());
	else printf("No\n");
	return 0;
}

