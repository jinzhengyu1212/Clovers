//Author: ReseeCher
#include<bits/stdc++.h>
#define LL long long
#define F(x,y,z) for(int x=y;x<=z;++x)
#define D(x,y,z) for(int x=y;x>=z;--x)
#define ckmax(a,b) (a)=max(a,b)
#define ckmin(a,b) (a)=min(a,b)
#define pb push_back
using namespace std;
const int N=2250010;
const int Inf=1000000;
inline int R(){
    int ans=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar()) ans=ans*10+c-'0';
    return ans;
}
inline char Rc(){
    char c=getchar();
    for(;!isalpha(c);c=getchar());
    return c;
}
int n,m,M;
int nxt[N],w[N],an[N];
int ID(int x,int y){return (x-1)*m+y;}
void Inss(int x,int y,char fx){
    int xx=x,yy=y;
    if(fx=='U')--xx;
    if(fx=='D')++xx;
    if(fx=='L')--yy;
    if(fx=='R')++yy;
    if(xx<1||xx>n||yy<1||yy>m)nxt[ID(x,y)]=0;
    else nxt[ID(x,y)]=ID(xx,yy);
}
int fa[N],len[N];
int ff[N],fw[N],mw[N];
bool In[N];
int vv[N][4],pp[N];
void Ads(int x,int y){vv[x][pp[x]++]=y;}
int sw,ccc;
int Find(int x){                    //并查集
    if(ff[x]==x){sw=0;return x;}
    ff[x]=Find(ff[x]);
    sw+=fw[x];fw[x]=sw;
    ++ccc;
    return ff[x];
}
int t[Inf+5],q[N];
void Qsort(){
    F(i,1,M)t[w[i]]++;
    F(i,1,Inf)t[i]+=t[i-1];
    F(i,1,M)q[t[w[i]]--]=i;
}
int stk[N],tp,now;
bool gg[N];
void dfs(int u,int ss){
    if(gg[u])return;
    if(!In[u])return;
    ff[u]=now;
    fw[u]=ss;
    ckmax(mw[now],ss);
    for(int i=0;i<pp[u];++i)
        dfs(vv[u][i],ss+1);
}
void SolC(int u){                   //处理u所在的环
    stk[tp=1]=u;gg[u]=1;
    int x=nxt[u];
    while(x!=u)gg[x]=1,stk[++tp]=x,x=nxt[x];
    F(i,1,tp){
        now=stk[i];
        ff[now]=now;
        fw[now]=tp;
        mw[now]=0;
        for(int k=0;k<pp[stk[i]];++k)
            dfs(vv[stk[i]][k],1);
        ckmin(an[mw[now]+fw[now]],w[u]);
    }
     
}
void Ins(int u){                    //把u插入图中
    In[u]=1;
    for(int i=0;i<pp[u];++i){
        int v=vv[u][i];
        if(In[v]){
            ff[v]=u;
            ckmax(mw[u],mw[v]+fw[v]);
        }
    }
    if(Find(fa[u])==Find(u)){
        SolC(u);
        return;
    }
    if(In[fa[u]]){
        ff[u]=fa[u];
        int y=Find(u);
        ckmax(mw[y],mw[u]+fw[u]);
        ckmin(an[mw[y]+fw[y]],w[u]);
    }
    else ckmin(an[mw[u]+fw[u]],w[u]);
}
void Work(){
    F(i,1,M)if(fa[i])Ads(fa[i],i);
    Qsort();
    F(i,1,M)fw[i]=1,ff[i]=i;
    F(i,1,M)Ins(q[i]);
}
 
int main(){
    ios::sync_with_stdio(0);
    //freopen("domino.in","r",stdin);
    //freopen("domino.out","w",stdout);
    R();
    n=R();m=R();M=ID(n,m);
    F(i,0,N-1)an[i]=77777777;
    F(i,1,n)F(j,1,m)Inss(i,j,Rc());
    F(i,1,n)F(j,1,m)w[ID(i,j)]=R();
     
    F(i,1,M)fa[i]=nxt[i];
    Work();
    D(i,N-2,0)ckmin(an[i],an[i+1]);
    int T=R();
    while(T--)cout<<an[R()]<<'\n';
    puts("");
    return 0;
}