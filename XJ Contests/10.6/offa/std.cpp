#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn=5E6+5;//?!?!?!
const ll inf=1E18;
int n,m,a[maxn],b[maxn],what[maxn],q[maxn];
ll f[maxn],g[maxn],h[maxn],val[maxn];
inline char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}//getchar
inline int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}//read a signed interger
int main()
{
//  freopen("offa6.in","r",stdin);
    n=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    for(int i=1;i<=n;++i)
        val[i]=read();
    m=read();
    for(int i=1;i<=m;++i)
    {
        b[i]=read();
        what[b[i]]=i;
    }
    n+=1,m+=1;
    a[n]=n,b[m]=n;
    what[n]=m;
    for(int i=0;i<=m;++i)
        g[i]=inf;
    ll now=inf,x=0;
    g[0]=0;
    for(int i=1,j=1;i<=n;q[i++]=j)
        if(b[j]<i)
            ++j;
    for(int i=1;i<=n;++i)
    {
        int pos=what[a[i]];
        if(pos)
            f[i]=(g[pos-1]<now)?g[pos-1]+h[pos]+x:now;
        if(val[i]>=0)
            h[q[a[i]]]+=val[i];
        else
            x+=val[i];
        if(pos&&f[i]<now)
            g[pos]=min(g[pos],f[i]-x);
    }
    if(f[n]<now)
        cout<<f[n]<<endl;
    else
        cout<<"Impossible"<<endl;
    return 0;
}