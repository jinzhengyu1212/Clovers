/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
ll _abs(ll x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
#define int long long
const int N=100005;
int n,m;
vector<pii> v[N];
int fa[N],top[N],son[N],sz[N],bot[N],dep[N];
ll dis[N],fl[N],fr[N],w[N],a[N];
int pre[N],suf[N],P[N][20],S[N][20];
int dfn_clock=0,dfn[N],id[N];
void dfs1(int u){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to.first==fa[u]) continue; fa[to.first]=u;
        dep[to.first]=dep[u]+1; dis[to.first]=dis[u]+to.second;
        dfs1(to.first); sz[u]+=sz[to.first];
        if(sz[son[u]]<sz[to.first]) son[u]=to.first;
    }
}
void dfs2(int u){
    dfn[u]=++dfn_clock; id[dfn_clock]=u;
    if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
    else bot[top[u]]=u; 
    for(auto &to : v[u]){
        if(to.first==fa[u]||to.first==son[u]) continue;
        top[to.first]=to.first; dfs2(to.first);
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
        else y=fa[top[y]];
    }
    return (dep[x]>dep[y] ? y : x);
}
int st[N][20],lg[N];
int query(int l,int r){
    int sz=r-l+1,S=lg[sz];
    return min(st[l][S],st[r-(1<<S)+1][S]);
}
int findl(int L,int val){
    int l=L,r=n,mid,best=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(query(L,mid)<val) best=mid,r=mid-1;
        else l=mid+1;
    }
    return best;
}
int findr(int R,int val){
    int l=1,r=R,mid,best=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(query(mid,R)<val) best=mid,l=mid+1;
        else r=mid-1;
    }
    return best;
}

void ready(int l,int r){
    stack<int> stk; while(!stk.empty()) stk.pop();
    a[0]=-inf; stk.push(0);
    for(int i=l;i<=r;i++){
        while(a[stk.top()]>a[i]) suf[stk.top()]=i,stk.pop();
        pre[i]=stk.top(); stk.push(i);
    }
    for(int i=l;i<=r;i++) if(pre[i]) 
        fl[i]=fl[pre[i]]+_abs(dis[id[i]]-dis[id[pre[i]]])*a[i];
    for(int i=r;i>=l;i--) if(suf[i])
        fr[i]=fr[suf[i]]+_abs(dis[id[i]]-dis[id[suf[i]]])*a[i];
    for(int i=l;i<=r;i++) P[i][0]=pre[i],S[i][0]=suf[i];
    for(int j=1;j<20;j++){
        for(int i=l;i<=r;i++){
            P[i][j]=P[P[i][j-1]][j-1];
            S[i][j]=S[S[i][j-1]][j-1];
        }
    }
    // out(l); outln(r);
    // for(int i=l;i<=r;i++) out(i),out(pre[i]),outln(suf[i]);
}

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) w[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read(),z=read();
        v[x].push_back(mk(y,z)); v[y].push_back(mk(x,z));
    }
    dfs1(1); top[1]=1; dfs2(1);
    for(int i=1;i<=n;i++) a[i]=w[id[i]];
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++) st[i][0]=a[i];
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            int to=i+(1<<(j-1));
            st[i][j]=min(st[i][j-1],st[to][j-1]);
        }
    }
    //for(int i=1;i<=n;i++) out(i),out(top[i]),outln(bot[i]);
    for(int i=1;i<=n;i++) if(i==top[i]) 
        ready(dfn[i],dfn[i]+dep[bot[i]]-dep[i]);
    //outln(P[3][1]);
}

ll jumprl(int from,int to,ll val){//suf
    ll ret=0;
    int pos=findr(from,val);
    if(pos>=to&&pos<=from){
        ret+=val*(dis[id[from]]-dis[id[pos]]);
        from=pos;
    }
    else return val*(dis[id[from]]-dis[id[to]]);
    if(from==to) return ret;
    for(int i=19;i>=0;i--){
        if(P[from][i]>=to){
            ret+=fl[from]-fl[P[from][i]];
            from=P[from][i];
        }
    }
    ret+=a[from]*(dis[id[from]]-dis[id[to]]);
    return ret;
}
ll jumplr(int from,int to,ll val){
    ll ret=0;
    int pos=findl(from,val);
    if(pos>=from&&pos<=to){
        ret+=val*(dis[id[pos]]-dis[id[from]]);
        from=pos;
    }
    else return val*(dis[id[to]]-dis[id[from]]);
    if(from==to) return ret;
    for(int i=19;i>=0;i--){
        if(S[from][i]<=to&&S[from][i]!=0){
            ret+=fr[from]-fr[S[from][i]];
            from=S[from][i];
        }
    }
    ret+=a[from]*(dis[id[to]]-dis[id[from]]);
    return ret;
}

ll val;
ll jumpup(int x,int F){
    if(x==F) return 0;
    ll ret=0;
    while(top[x]!=top[F]){
        ret+=jumprl(dfn[x],dfn[top[x]],val);
        checkmin(val,query(dfn[top[x]],dfn[x]));
        ret+=val*(dis[top[x]]-dis[fa[top[x]]]);
        x=fa[top[x]];
        checkmin(val,w[x]);
    }
    ret+=jumprl(dfn[x],dfn[F],val);
    checkmin(val,query(dfn[F],dfn[x]));
    return ret;
}

ll jumpdown(int x,int to){
    if(x==to) return 0;
    ll ret=0;
    vector<int> T; T.clear();
    int tmp=to;
    while(top[tmp]!=top[x]) T.push_back(top[tmp]),tmp=fa[top[tmp]];
    for(int i=sz(T)-1;i>=0;i--){
        int s=T[i],u=fa[s];
        ret+=jumplr(dfn[x],dfn[u],val);
        checkmin(val,query(dfn[x],dfn[u]));
        ret+=val*(dis[s]-dis[u]);
        x=s;
        checkmin(val,w[x]);
    }
    ret+=jumplr(dfn[x],dfn[to],val);
    return ret;
}

signed main()
{
    init();
    while(m--){
        int x=read(),y=read();
        int lca=LCA(x,y); val=w[x];
        ll tmp1=jumpup(x,lca);
        ll tmp2=jumpdown(lca,y);
        printf("%lld\n",tmp1+tmp2);
    }
    return 0;
}