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
int _abs(int x){return x<0 ? -x : x;}
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
const int N=750005;
int n,q,Rt,h[N],st[N][20],lg[N];
int ls[N],rs[N]; 
pii Con[N]; ll dp[N],ans[N];
int query(int l,int r){
    int sz=r-l+1,to=r-(1<<lg[sz])+1;
    return h[st[l][lg[sz]]]>h[st[to][lg[sz]]] ? st[l][lg[sz]] : st[to][lg[sz]];
}
struct Query{int l,r,id;};
vector<Query> Q[N];

int build(int l,int r){
    if(l>r) return 0;
    int mid=query(l,r); Con[mid]=mk(l,r);
    ls[mid]=build(l,mid-1); rs[mid]=build(mid+1,r);
    if(!ls[mid]) dp[mid]=dp[rs[mid]]+h[mid];
    else if(!rs[mid]) dp[mid]=dp[ls[mid]]+h[mid];
    else dp[mid]=min(dp[ls[mid]]+1ll*(r-mid+1)*h[mid],
                    dp[rs[mid]]+1ll*(mid-l+1)*h[mid]);
    return mid;
}

struct Segment_Tree{//chafen
    ll sum[N<<2],tag[N<<2]; int tui[N<<2];
    void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
    void pushdown(int x,int l,int mid,int r){
        if(tui[x]){
            sum[x<<1]=0; sum[x<<1|1]=0;
            tag[x<<1]=0; tag[x<<1|1]=0;
            tui[x<<1]=1; tui[x<<1|1]=1; tui[x]=0;
        }
        sum[x<<1]+=1ll*(mid-l+1)*tag[x]; tag[x<<1]+=tag[x];
        sum[x<<1|1]+=1ll*(r-mid)*tag[x]; tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
    void update(int x,int l,int r,int L,int R,ll val){
        if(L>R||R>n||L<1) return;
        if(L<=l&&r<=R){sum[x]+=1ll*(r-l+1)*val; tag[x]+=val; return;} 
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if(L>R||R>n||L<1) return 0;
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        ll ret=0;
        if(mid>=L) ret+=query(x<<1,l,mid,L,R);
        if(mid<R) ret+=query(x<<1|1,mid+1,r,L,R);
        return ret; 
    }
    void Tui(int x,int l,int r,int L,int R){
        if(L>R||R>n||L<1) return;
        if(L<=l&&r<=R){tui[x]=1; tag[x]=0; sum[x]=0; return;}
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        if(mid>=L) Tui(x<<1,l,mid,L,R);
        if(mid<R) Tui(x<<1|1,mid+1,r,L,R);
        pushup(x);
    }
}treel,treer;
//l:左端点为i，右端点在上界

void init(){
    n=read(); q=read();
    for(int i=1;i<=n;i++) h[i]=read(),st[i][0]=i;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            int to=i+(1<<(j-1));
            if(h[st[i][j-1]]>h[st[to][j-1]]) st[i][j]=st[i][j-1];
            else st[i][j]=st[to][j-1];
        }
    }
    Rt=build(1,n);
    for(int i=1;i<=q;i++){
        int l=read()+1,r=read()+1;
        Q[query(l,r)].push_back({l,r,i});
    }
}

ll calc(int l,int r,int mid,ll vall,ll valr){
    if(l==mid) return valr+h[mid];
    else if(r==mid) return vall+h[mid];
    else return min(vall+1ll*(r-mid+1)*h[mid],
                    valr+1ll*(mid-l+1)*h[mid]);
}

int findl(int u){
    int l=Con[u].first,r=u,mid,best=u;
    while(l<=r){
        mid=(l+r)>>1;
        ll vall=treel.query(1,1,n,1,mid);
        ll valr=dp[rs[u]];
        if(valr+1ll*(u-mid+1)*h[u]<=vall+1ll*(Con[u].second-u+1)*h[u])
            r=mid-1,best=mid;
        else l=mid+1;
    }
    return best;
}

int findr(int u){
    int l=u,r=Con[u].second,mid,best=u;
    while(l<=r){
        mid=(l+r)>>1;
        ll valr=treer.query(1,1,n,1,mid);
        ll vall=dp[ls[u]];
        if(vall+1ll*(mid-u+1)*h[u]<=valr+1ll*(u-Con[u].first+1)*h[u])
            l=mid+1,best=mid;
        else r=mid-1;
    }
    return best;
}

void dfs(int u){
    if(ls[u]) dfs(ls[u]); if(rs[u]) dfs(rs[u]);
    for(auto &t : Q[u]){
        if(t.l==Con[u].first&&t.r==Con[u].second){ans[t.id]=dp[u]; continue;}
        int l=t.l,r=t.r;
        ll vall=treel.query(1,1,n,1,l),valr=treer.query(1,1,n,1,r);
        ans[t.id]=calc(l,r,u,vall,valr);
    }
    int posr=findr(u),posl=findl(u);
    //posl~posr 时朝反方向覆盖 
    int l=Con[u].first,r=Con[u].second;
    ll S1=treel.query(1,1,n,1,u),S2,S3;
    treel.update(1,1,n,l,l,1ll*(Con[u].second-u+1)*h[u]);
    treel.update(1,1,n,posl,posl,-1ll*(r-u+1)*h[u]);
    treel.Tui(1,1,n,posl,u); ll pre=treel.query(1,1,n,1,posl-1);
    treel.update(1,1,n,posl,posl,dp[rs[u]]+1ll*(u-posl+1)*h[u]-pre); 
    treel.update(1,1,n,posl+1,u,-h[u]);
    S2=treel.query(1,1,n,1,u);
    treel.update(1,1,n,u+1,u+1,S1-S2);

    S2=treer.query(1,1,n,1,posr);
    treer.Tui(1,1,n,u,posr); pre=treer.query(1,1,n,1,u-1);
    treer.update(1,1,n,u,u,dp[ls[u]]+h[u]-pre);
    treer.update(1,1,n,u+1,posr,h[u]);
    S3=treer.query(1,1,n,1,posr); 
    treer.update(1,1,n,posr+1,posr+1,S2-S3+1ll*(u-l+1)*h[u]);
    treer.update(1,1,n,r+1,r+1,-1ll*(u-l+1)*h[u]);
}

void solve(){
    dfs(Rt);
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}

signed main()
{
    init(); solve();
    return 0;
}