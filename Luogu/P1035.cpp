#include<iostream>
using namespace std;
int main()
{
    long double s=0,k;
    long long i;
    i=1;
    cin>>k;
    while(s<=k)
    {
        s=1.0/i+s;
        i++;
    }
    cout<<i-1;
}
