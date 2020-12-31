/*
the vast starry sky,
bright for those who chase the light.
*/
#pragma GCC optimize(3)
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
const int N=100005;
int n,a[N],col[N],q; vector<int> v[N];
int dfn_clock=0,cnt=0,dfn[N],outdfn[N],id[N];
int in[N],out[N];
void dfs(int u,int f){
    in[u]=++dfn_clock;
    dfn[u]=++cnt; id[cnt]=u;
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs(to,u);
    }
    out[u]=++dfn_clock; outdfn[u]=cnt;
}
 
struct QUERY{
    int pos,val,ti;
};
vector<QUERY> Q[N];
 
struct BIT1{
    int a[N];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) a[i]+=val;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=(i&(-i))) ret+=a[i];
        return ret;
    }
}T1[21][2];
 
struct BIT2{
    int a[N<<1];
    void update(int x,int val){
        for(int i=x;i<=n+n;i+=(i&(-i))) a[i]+=val;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=(i&(-i))) ret+=a[i];
        return ret;
    }
}T2[21][2];
 
void init(){
    n=read();
    for(int i=1;i<=n;i++) col[i]=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs(1,-1);
    q=read();
    for(int i=1;i<=n;i++){
        Q[col[i]].push_back({i,a[i],0});
    }
    for(int i=1;i<=q;i++){
        int opt=read(),x=read(),y=read();
        if(opt==1){
            a[x]=y;
            Q[col[x]].push_back({x,a[x],i});
        }
        else{
            Q[col[x]].push_back({x,-1,i});
            col[x]=y;
            Q[col[x]].push_back({x,a[x],i});
        }
    }
}
 
int now[N],sum[21][2];
ll ans[N],S[N];
void change(int x,int val,int ti,int bl){
    if(now[x]!=-1) for(int i=0;i<20;i++){
        if(now[x]>>i&1){
            if(bl){
                ans[ti]-=1ll*(T1[i][0].query(outdfn[x])-T1[i][0].query(dfn[x]))*(1ll<<i);
                ans[ti]-=1ll*T2[i][0].query(in[x]-1)*(1ll<<i);
                S[ti]-=1ll*sum[i][0]*(1ll<<i);
            }
            T1[i][1].update(dfn[x],-1);
            T2[i][1].update(in[x],-1), T2[i][1].update(out[x],1);
            sum[i][1]--;
        }
        else{
            if(bl){
                ans[ti]-=1ll*(T1[i][1].query(outdfn[x])-T1[i][1].query(dfn[x]))*(1ll<<i);
                ans[ti]-=1ll*T2[i][1].query(in[x]-1)*(1ll<<i);
                S[ti]-=1ll*sum[i][1]*(1ll<<i);
            }
            T1[i][0].update(dfn[x],-1);
            T2[i][0].update(in[x],-1), T2[i][0].update(out[x],1);
            sum[i][0]--;
        }
    }
    now[x]=val;
    if(now[x]!=-1) for(int i=0;i<20;i++){
        if(now[x]>>i&1){
            if(bl){
                ans[ti]+=1ll*(T1[i][0].query(outdfn[x])-T1[i][0].query(dfn[x]))*(1ll<<i);
                ans[ti]+=1ll*T2[i][0].query(in[x]-1)*(1ll<<i);
                S[ti]+=1ll*sum[i][0]*(1ll<<i);
            }
            T1[i][1].update(dfn[x],1);
            T2[i][1].update(in[x],1), T2[i][1].update(out[x],-1);
            sum[i][1]++;
        }
        else{
            if(bl){
                ans[ti]+=1ll*(T1[i][1].query(outdfn[x])-T1[i][1].query(dfn[x]))*(1ll<<i);
                ans[ti]+=1ll*T2[i][1].query(in[x]-1)*(1ll<<i);
                S[ti]+=1ll*sum[i][1]*(1ll<<i);
            }
            T1[i][0].update(dfn[x],1);
            T2[i][0].update(in[x],1), T2[i][0].update(out[x],-1);
            sum[i][0]++;
        }
    }
}
 
void solve(int C){
    for(int i=0;i<sz(Q[C]);i++){
        QUERY u=Q[C][i];
        change(u.pos,u.val,u.ti,1);
    }   
    for(int i=sz(Q[C])-1;i>=0;i--){
        QUERY u=Q[C][i];
        change(u.pos,u.val,u.ti,0);
    }
    for(int i=0;i<sz(Q[C]);i++) change(Q[C][i].pos,-1,0,0);
}
 
signed main()
{
    init();
    memset(now,-1,sizeof(now));
    for(int i=1;i<=n;i++) solve(i);
    printf("%lld\n",S[0]-ans[0]);
    for(int i=1;i<=q;i++){
        ans[i]+=ans[i-1]; S[i]+=S[i-1];
        printf("%lld\n",S[i]-ans[i]);
    }
    return 0;
}