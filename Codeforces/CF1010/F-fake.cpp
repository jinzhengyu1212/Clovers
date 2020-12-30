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
const int N=100005;
int G[N<<2],IG[N<<2];
typedef vector<int> V;
namespace FFT{
    int rev[N<<2];
    int init(int n){
        int len=1; while(len<n) len<<=1;
        rev[0]=0; 
        for(int i=1;i<len;i++) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
        return len;
    }
    void ntt(V &a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==-1 ? IG[h<<1] : G[h<<1]);
            for(int i=0;i<len;i+=(h<<1)){
                int W=1,tmp1,tmp2;
                for(int j=i;j<i+h;j++,Mul(W,wn)){
                    tmp1=a[j],tmp2=mul(a[j+h],W);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) Mul(a[i],invlen);
        }
    }
    void multi(V &a,V b,int n,int m){
        int len=init(n+m+1);
        a.resize(len); b.resize(len);
        ntt(a,len,1); ntt(b,len,1);
        for(int i=0;i<len;i++) Mul(a[i],b[i]);
        ntt(a,len,-1);
    }
}

int n; vector<int> v[N];
V dp[N]; int sz[N];
void dfs(int u,int f){
    dp[u].push_back(1);
    int son[2],cnt=0; sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        son[cnt++]=to;
        dfs(to,u); sz[u]+=sz[to];
    }
    if(cnt==1){
        dp[u]=dp[son[0]]; dp[son[0]].clear();
    }
    else if(cnt==2){
        FFT::multi(dp[son[0]],dp[son[1]],sz[son[0]],sz[son[1]]);
        dp[u]=dp[son[0]]; dp[son[0]].clear();
    }
    dp[u].resize(sz[u]+1); dp[u][sz[u]]=1;
}

ll X; int C[N];
void init(){
    for(int i=1;i<N*4;i<<=1){
        G[i]=qpow(3,(MOD-1)/i);
        IG[i]=qpow(G[i],MOD-2);
    }
    n=read(); scanf("%lld",&X); X%=MOD;
    C[0]=1; for(int i=1;i<=n;i++) dp[i].clear();
    for(int i=1;i<=n;i++){
        int A=add(X,i),B=i;
        C[i]=mul(C[i-1],mul(A,qpow(B,MOD-2)));
    }
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
}

void solve(){
    int ans=0;
    //for(int i=0;i<=n;i++) cout<<dp[1][i]<<" "; cout<<endl;
    for(int i=0;i<n;i++){
        int rest=n-i;
        Add(ans,mul(dp[1][i],C[rest-1]));
    }
    cout<<ans<<endl;
}

void print(V A){
    for(int i=0;i<(int)A.size();i++) printf("%d ",A[i]);
    puts("");
}
int main()
{
    init(); dfs(1,-1);
    solve();
    return 0;
}