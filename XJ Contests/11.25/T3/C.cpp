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
const int N=50005;
int n,m,a[6][N],b[6][N],heng[6][N],shu[6][N];

void init(){
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++) a[i][j]=read(),b[i][j]=read();
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<n;j++) heng[i][j]=read();
    }
    for(int i=1;i<m;i++){
        for(int j=1;j<=n;j++) shu[i][j]=read();
    }
}

namespace solver1{
    ll dp[N][65]; int vis[N][65];
    ll calc1(int id,int mask){
        static int A[6];
        for(int i=1;i<=m;i++){
            if(mask>>(i-1)&1) A[i]=1;
            else A[i]=0;
        }
        ll ret=0;
        for(int i=1;i<m;i++){
            ret+=_abs(A[i]-A[i+1])*shu[i][id];
        }     
        return ret;  
    }
    ll calc2(int pre,int mask1,int mask2){
        static int A[6],B[6];
        for(int i=1;i<=m;i++){
            if(mask1>>(i-1)&1) A[i]=1;
            else A[i]=0;
            if(mask2>>(i-1)&1) B[i]=1;
            else B[i]=0;
        }
        ll ret=0;
        for(int i=1;i<=m;i++){
            ret+=_abs(A[i]-B[i])*heng[i][pre];
        }
        return ret;
    }
    void main(){
        int full=(1<<m)-1;
        memset(dp,0x3f,sizeof(dp));
        for(int mask=0;mask<=full;mask++){
            static int A[6];
            int flag=1;
            for(int i=1;i<=m;i++){
                if(mask>>(i-1)&1) A[i]=1;
                else A[i]=0;
                if(A[i]>b[i][1]||A[i]<a[i][1]) flag=0;
            }
            if(flag) dp[1][mask]=calc1(1,mask);
            vis[1][mask]=flag;
        }
        ll ans=INF;
        for(int i=2;i<=n;i++){
            for(int mask=0;mask<=full;mask++){
                static int A[6];
                int flag=1;
                for(int j=1;j<=m;j++){
                    if(mask>>(j-1)&1) A[j]=1;
                    else A[j]=0;
                    if(A[j]>b[j][i]||A[j]<a[j][i]) flag=0;
                }
                if(!flag) continue;
                vis[i][mask]=1;
                for(int mask2=0;mask2<=full;mask2++){
                    if(!vis[i-1][mask2]) continue;
                    ll tmp=calc1(i,mask)+calc2(i-1,mask2,mask);
                    checkmin(dp[i][mask],dp[i-1][mask2]+tmp);
                }
                if(i==n) checkmin(ans,dp[i][mask]);
            }
        }
        cout<<ans<<endl;
    }
}

bool check01(){
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j]>1) return 0;
        }
    }
    return 1;
}

namespace solver2{
    pii E[N];
    int L[N],R[N],vis[N];
    namespace DSU{
        int fa[N];
        int getfather(int x){
            if(x==fa[x]) return x;
            return fa[x]=getfather(fa[x]);
        }
        void unite(int x,int y){
            x=getfather(x); y=getfather(y);
            if(x==y) return;
            checkmax(L[x],L[y]); checkmin(R[x],R[y]);
            fa[y]=x;
        }
    }
    void init(){
        for(int i=1;i<n;i++) E[i]=mk(heng[1][i],i);
        for(int i=1;i<=n;i++) L[i]=a[1][i],R[i]=b[1][i];
        sort(E+1,E+n);
        reverse(E+1,E+n);
    }
    bool Cross(int x,int y){
        int l=max(L[x],L[y]);
        int r=min(R[x],R[y]);
        return l<=r;
    }
    int Close(int x,int val){
        if(L[x]<=val&&R[x]>=val) return val;
        if(R[x]<val) return R[x];
        return L[x];
    }
    void main(){
        init();
        for(int i=1;i<=n;i++) DSU::fa[i]=i;
        memset(vis,0,sizeof(vis));
        ll ans=0;
        for(int i=1;i<n;i++){
            int x=DSU::getfather(E[i].second),
                y=DSU::getfather(E[i].second+1);
            if(vis[x]&&vis[y]){
                ans+=_abs(vis[x]-vis[y])*E[i].first;
            }
            else if(vis[x]){
                vis[y]=Close(y,vis[x]);
                ans+=_abs(vis[x]-vis[y])*E[i].first;
            }
            else if(vis[y]){
                vis[x]=Close(x,vis[y]);
                ans+=_abs(vis[x]-vis[y])*E[i].first;
            }
            else{
                if(!Cross(x,y)){
                    if(L[x]>R[y]) vis[x]=L[x],vis[y]=R[y];
                    else vis[x]=R[x],vis[y]=L[y];
                    ans+=_abs(vis[x]-vis[y])*E[i].first;
                }
                else DSU::unite(x,y);
            }
        }
        cout<<ans<<endl;
    }
}

void solve(){
    if(n==1&&m==1){
        puts("0");
        return;
    }
    if(check01()){
        solver1::main();
        return;
    }
    if(m==1){
        solver2::main();
        return;
    }
}

int main()
{
    init();
    solve();
    return 0;
}