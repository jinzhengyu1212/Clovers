#pragma GCC opitimize(2)
#pragma GCC opitimize(3)
#pragma GCC opitimize("-O2")
#pragma GCC opitimize("-O3")
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 100005
#define M 4000005
#define ll long long
using namespace std;
int n,q,x,y,o1,o2,o3,o4,a[N];
int ct=0,cc,tot,fa[N],fr[N],nxt[N << 1],d[N << 1];
int c[N << 1],e[N][2];
ll ans,tr[M],tr2[M];
int cnt=0,t[N],tr3[M],ls[M],rs[M],tag[M];
inline int read()
{
    int s=0;
    char c=getchar();
    while (c<'0' || c>'9')
        c=getchar();
    while ('0'<=c && c<='9')
        s=(s << 1)+(s << 3)+c-'0',c=getchar();
    return s;
}
void write(ll x)
{
    if (x>9)
        write(x/10);
    putchar(x%10+'0');
}
inline int mx(int x,int y)
{
    return (x>y)?x:y;
}
inline void add(int x,int y)
{
    tot++;
    d[tot]=y;
    nxt[tot]=fr[x];
    fr[x]=tot;
}
inline void push_tag(int p,int z)
{
    if (z==1)
        tr[p]=0; else
        tr[p]=tr2[p];
    tag[p]=z;
}
inline void push_down(int p)
{
    if (tag[p])
    {
        push_tag(ls[p],tag[p]);
        push_tag(rs[p],tag[p]);
        tag[p]=0;
    }
}
inline void update(int p)
{
    tr[p]=tr[ls[p]]+tr[rs[p]];
}
void modify(int &p,int l,int r,int x)
{
    if (!p)
        p=++cnt;
    push_down(p);
    tr[p]+=o1;
    tr2[p]+=o2;
    tr3[p]+=o3;
    if (l==r)
        return;
    int mid=(l+r) >> 1;
    if (x<=mid)
        modify(ls[p],l,mid,x); else
        modify(rs[p],mid+1,r,x);
}
int calc(int p,int l,int r,int x,int y)
{
    if (!p)
        return 0;
    if (l==x && r==y)
        return tr3[p];
    push_down(p);
    int mid=(l+r) >> 1;
    if (y<=mid)
        return calc(ls[p],l,mid,x,y); else
    if (x>mid)
        return calc(rs[p],mid+1,r,x,y); else
        return calc(ls[p],l,mid,x,mid)+calc(rs[p],mid+1,r,mid+1,y);
}
void modify2(int p,int l,int r,int x,int y,int z)
{
    if (!p)
        return;
    if (l==x && r==y)
    {
        push_tag(p,z);
        return;
    }
    push_down(p);
    int mid=(l+r) >> 1;
    if (y<=mid)
        modify2(ls[p],l,mid,x,y,z); else
    if (x>mid)
        modify2(rs[p],mid+1,r,x,y,z); else
        {
            modify2(ls[p],l,mid,x,mid,z);
            modify2(rs[p],mid+1,r,mid+1,y,z);
        }
    update(p);
}
void dfs(int u)
{
    for (int i=fr[u];i;i=nxt[i])
    {
        int v=d[i];
        if (v==fa[u])
            continue;
        fa[v]=u;
        if (a[u]<a[v])
            ans+=c[a[v]]-c[a[u]];
        o1=((a[v]>a[u])?c[a[v]]:0);
        o2=c[a[v]];
        o3=1;
        modify(t[u],1,cc,a[v]);
        dfs(v);
    }
}
int main()
{
    n=read(),q=read();
    for (int i=1;i<=n;i++)
        a[i]=read(),c[++ct]=a[i];
    for (int i=1;i<n;i++)
    {
        x=read(),y=read();
        add(x,y),add(y,x);
    }
    for (int i=1;i<=q;i++)
        e[i][0]=read(),e[i][1]=read(),c[++ct]=e[i][1];
    sort(c+1,c+ct+1);
    cc=unique(c+1,c+ct+1)-c-1;
    for (int i=1;i<=n;i++)
        a[i]=lower_bound(c+1,c+cc+1,a[i])-c;
    for (int i=1;i<=q;i++)
        e[i][1]=lower_bound(c+1,c+cc+1,e[i][1])-c;
    ans=c[a[1]];
    dfs(1);
    for (int i=1;i<=q;i++)
    {
        x=e[i][0],y=e[i][1];
        ans-=tr[t[x]];
        if (a[x]<cc)
        {
            o4=calc(t[x],1,cc,a[x]+1,cc);
            ans+=(ll)o4*c[a[x]];
        }
        //u->fa
        if (fa[x])
        {
            if (a[x]>a[fa[x]])
                ans=ans-(c[a[x]]-c[a[fa[x]]]);
            o1=((a[x]>a[fa[x]])?-c[a[x]]:0);
            o2=-c[a[x]];
            o3=-1;
            modify(t[fa[x]],1,cc,a[x]);
            a[x]=y;
            o1=((a[x]>a[fa[x]])?c[a[x]]:0);
            o2=c[a[x]];
            o3=1;
            if (a[x]>a[fa[x]])
                ans=ans+(c[a[x]]-c[a[fa[x]]]);
            modify(t[fa[x]],1,cc,a[x]);
        } else
            ans=ans-c[a[x]]+c[y],a[x]=y;
        //u->son
        modify2(t[x],1,cc,1,a[x],1);
        if (a[x]<cc)
            modify2(t[x],1,cc,a[x]+1,cc,2);
        ans+=tr[t[x]];
        if (a[x]<cc)
        {
            o4=calc(t[x],1,cc,a[x]+1,cc);
            ans-=(ll)o4*c[a[x]];
        }
        write(ans),putchar('\n');
    }
    return 0;
}
