#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

char ch[1600000];
struct Bignum
{
    int a[160000];
    int len;
    Bignum() { memset(a,0,sizeof a); len=0; }
    void output() 
    {
        for(int i=len;i>=1;i--) 
            printf("%d",a[i]);
        return;
    }
    void input()
    {
        scanf("%s",ch+1);
        len=strlen(ch+1);
        for(int i=1;i<=len;i++) 
            a[i]=ch[len-i+1]-'0';
        return;
    }
    friend Bignum operator+(const Bignum &a,const Bignum &b)
    {
        Bignum res;
        int i,x=0;
        res.len=max(a.len,b.len);
        for(i=1;i<=res.len;i++) {
            res.a[i]=a.a[i]+b.a[i]+x;
            x=res.a[i]/10;
            res.a[i]%=10;
        }
        if(x>0) res.len++,res.a[res.len]=x;
        return res;
    }
};

int main()
{
    Bignum a,b,c;
    a.input(); b.input();
    c=a+b;
    c.output();
    return 0;
}
