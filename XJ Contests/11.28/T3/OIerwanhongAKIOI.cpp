#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
typedef long long ll;
typedef unsigned un;
int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();
    return f*x;
}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
inline void umax(int& a,int t){if(t>a)a=t;}
inline void umin(int& a,int t){if(t<a)a=t;}

#define MAXN 1000011
#define MAXQ 10000011
unsigned sd;
int a[MAXN],s[MAXN],pre[MAXN],n,m;
int rd(){return (sd^=sd<<13,sd^=sd>>17,sd^=sd<<5)%n+1;}
struct Query
{
    int l,r,dex;
    bool operator <(const Query& you)const{return r<you.r;}
}q[MAXQ];
int t[MAXN];
#define lowb (i&-i)
inline void modify(int i,int k)
{
    while(i<=n)t[i]+=k,i+=lowb;
}
inline int Qsum(int i)
{
    int res=0;
    while(i)res+=t[i],i-=lowb;
    return res;
}
const int mod=998244353;
int main()
{
    n=read(),m=read();scanf("%u",&sd);
    int top=0;
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        while(top&&a[s[top]]<a[i])--top;
        pre[i]=s[top];
        s[++top]=i;
    }
    for(int i=1;i<=m;++i)
    {
        q[i].l=rd(),q[i].r=rd(),q[i].dex=i;
        if(q[i].l>q[i].r)std::swap(q[i].l,q[i].r);
    }
    std::sort(q+1,q+m+1);
    int it=1,tot=0,ans=0;
    for(int i=1;i<=n;++i)
    {
        if(pre[i])modify(pre[i],-1),--tot;
        modify(i,1),++tot;
        while(it<=m&&q[it].r<=i)
        {
            ans=(ans+ll(q[it].dex)*(tot-Qsum(q[it].l-1)))%mod;
            ++it;
        }
    }
    printf("%d\n",ans);
    return 0;
}