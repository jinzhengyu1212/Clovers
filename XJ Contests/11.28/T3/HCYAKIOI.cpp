	
/*
after dusk passed,
there is a starry sky.
*/
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
#define mod 998244353
using namespace std;
const int N=1e6+100,M=1e7+100;
int n,m,a[N],q[N],w,p[N],ans[M],s[N];
struct node
{
    int l,r,id;
}sh[M];
inline int cmp(node a,node b){return a.r<b.r;}
long long tmp;
unsigned sd ;
inline int rd (){return( sd^=sd <<13,sd^=sd >>17,sd^=sd<<5)%n+1;}
inline char gc()
{
    static char now[1<<20],*s,*t;
    if (s==t)
    {
        t=(s=now)+fread(now,1,1<<20,stdin);
        if (s==t) return EOF;
    }
    return *s++;
}
inline int read()
{
    int f=1,x=0;char s=gc();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=gc();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=gc();}
    return x*f;
}
inline int lowbit(int x){return (x&(-x));}
inline void change(int x,int v){while(x)s[x]+=v,x-=lowbit(x);}
inline int query(int x){int ans=0;while(x<=n)ans+=s[x],x+=lowbit(x);return ans;}
signed main()
{
//  freopen("C.in","r",stdin);
    n=read();m=read();sd=read();
    for (int i=1;i<=n;i++) a[i]=read();
    w=0;
    for (int i=n;i>=1;i--)
    {
        while (w&&a[q[w]]<=a[i]) p[q[w]]=i,w--;
        q[++w]=i;
    }
    int l,r;
    for (int i=1;i<=m;i++)
    {
        l=rd(),r=rd();
        if (l>r) swap(l,r);
        sh[i]=(node){l,r,i};
    }
    sort(sh+1,sh+1+m,cmp);
    long long ans=0;
    int num;
    for (int i=1,pos=1;i<=m;i++)
    {
        while (pos<=sh[i].r) change(p[pos++],1);
        num=query(sh[i].l);
        ans=(ans+(long long)sh[i].id*(sh[i].r-sh[i].l+1-num))%mod;
    }
    printf("%lld\n",ans);
}