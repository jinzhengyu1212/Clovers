#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e6+10;typedef long long ll;char mde[N];int n;int nl;int nr;int m;
struct suffixautomaton//简易后缀自动机板子 
{
    int mp[N][27];int ct;int fa[N];int len[N];int n;
    inline int& operator [](const int& x){return len[x];}
    inline void ih(int x){n=x;for(int i=1;i<=n;i++)len[i]=i;ct=n+1;}
    inline void clr()
    {
        for(int i=1;i<=ct;i++)for(int j=1;j<=26;j++)mp[i][j]=0;
        for(int i=1;i<=ct;i++)fa[i]=0;for(int i=1;i<=ct;i++)len[i]=0;
    }
    inline void ins(int x,int c)
    {
        int p=(x==1)?n+1:x-1;for(;p&&mp[p][c]==0;p=fa[p])mp[p][c]=x;
        if(p==0){fa[x]=n+1;return;}int q=mp[p][c];
        if(len[q]==len[p]+1){fa[x]=q;return;}len[++ct]=len[p]+1;
        for(int i=1;i<=26;i++)mp[ct][i]=mp[q][i];
        for(;p&&mp[p][c]==q;p=fa[p])mp[p][c]=ct;fa[ct]=fa[q];fa[q]=fa[x]=ct;
    }
};
namespace SM
{
    suffixautomaton sam;int s[40*N][2];int va[40*N];int cnt;
    int v[N];int x[N];int al[N];int ct;
    inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
    # define mov(p,c) (p=sam.mp[p][c])
    # define jup(p) (p=sam.fa[p])
    inline void ins(int p,int l,int r,int pos) 
    {
        va[p]=pos;if(r-l==1){return;}int mid=(l+r)/2;
        if(pos<=mid)ins(s[p][0]=++cnt,l,mid,pos);else ins(s[p][1]=++cnt,mid,r,pos);
    }
    inline int mg(int p1,int p2,int isr)//这里的合并是可持久化的，不会销毁任意一颗线段树 
    {
        int nw=(isr)?p1:++cnt;
        if(s[p1][0]&&s[p2][0])s[nw][0]=mg(s[p1][0],s[p2][0],0);
            else s[nw][0]=(s[p2][0])?s[p2][0]:s[p1][0];
        if(s[p1][1]&&s[p2][1])s[nw][1]=mg(s[p1][1],s[p2][1],0);
            else s[nw][1]=(s[p2][1])?s[p2][1]:s[p1][1];
        va[nw]=max(va[s[nw][0]],va[s[nw][1]]);return nw;
    }
    inline int qry(int p,int l,int r,int dl,int dr)//查询区间最大值 
    {
        if((p==0)||(dl==l&&r==dr))return va[p];int mid=(l+r)/2;int res=0;
        if(dl<mid)res=max(res,qry(s[p][0],l,mid,dl,min(dr,mid)));
        if(mid<dr)res=max(res,qry(s[p][1],mid,r,max(dl,mid),dr));
        return res;
    }
    inline void dfs(int u){for(int i=al[u];i;i=x[i])dfs(v[i]),mg(u,v[i],1);}
    inline void build()
    {
        sam.ih(n);for(int i=1;i<=n;i++)sam.ins(i,mde[i]-'a'+1);
        cnt=sam.ct;for(int i=1;i<=sam.ct;i++)add(sam.fa[i],i);
        for(int i=1;i<=n;i++)ins(i,0,n,i);dfs(n+1);
    }
    inline void trs(int& p,const int& c,int& len)//暴力跳fail树进行转移 
    {
        for(;p!=n+1;jup(p),len=sam[p])
            if(sam.mp[p][c])
            {
                int mle=qry(sam.mp[p][c],0,n,0,nr)-nl+1;
                if(sam[sam.fa[p]]<mle){len=min(len+1,mle);mov(p,c);return;}
            }
        if(p==n+1&&(sam.mp[p][c]==0||qry(sam.mp[p][c],0,n,0,nr)<nl)){len=0;return;}
        mov(p,c);len++;
    }
    # undef mov
    # undef jup
}
namespace SM2
{
    suffixautomaton sam;char mde[N];int le;
    int v[N];int x[N];int al[N];int ct;int mx[N];
    inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
    # define mov(p,c) (p=sam.mp[p][c])
    # define jup(p) (p=sam.fa[p])
    inline void build()
    {
        for(int i=1;i<=sam.ct;i++)al[i]=0;ct=0;sam.clr();scanf("%s",mde+1);
        scanf("%d%d",&nl,&nr);le=1;for(;mde[le+1]!='\0';le++);sam.ih(le);
        for(int i=1;i<=le;i++)sam.ins(i,mde[i]-'a'+1);
        for(int i=1;i<=sam.ct;i++)add(sam.fa[i],i),mx[i]=sam[sam.fa[i]];
    }
    inline void aju(int p,const int& lim)//打标记 
    {
        for(;p!=le+1&&sam[sam.fa[p]]>=lim;jup(p));
        for(;p!=le+1&&sam[p]>mx[p];jup(p))mx[p]=max(mx[p],min(sam[p],lim));
    }
    inline ll dfs(int u)
    {ll ret=0;for(int i=al[u];i;i=x[i])ret+=mx[v[i]]-sam[u]+dfs(v[i]);return ret;}
    inline ll dfs2(int u)
    {ll ret=0;for(int i=al[u];i;i=x[i])ret+=sam[v[i]]-sam[u]+dfs2(v[i]);return ret;}
    inline void solve(int z)
    {
        for(int i=1,p1=n+1,p2=le+1,nle=0;i<=le;i++)
            mov(p2,mde[i]-'a'+1),SM::trs(p1,mde[i]-'a'+1,nle),aju(p2,nle);
        printf("%lld\n",dfs2(le+1)-dfs(le+1));
    }
    # undef mov
    # undef jup
}
int main()
{
    scanf("%s",mde+1);for(n=1;mde[n+1]!='\0';n++);SM::build();scanf("%d",&m);
    for(int i=1;i<=m;i++)SM2::build(),SM2::solve(i);return 0;//拜拜程序~ 
}