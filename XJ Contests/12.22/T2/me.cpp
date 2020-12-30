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
const int MOD=(int)1e9+7;
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
const int N=100005;
const int MOD1=19260817;
const int MOD2=1019260817;
const int B=100057;
#define fi first
#define se second
pii operator + (pii A,pii B){return mk((A.fi+B.fi)%MOD1,(A.se+B.se)%MOD2);}
pii operator - (pii A,pii B){return mk((A.fi-B.fi+MOD1)%MOD1,(A.se-B.se+MOD2)%MOD2);}
pii operator * (pii A,pii B){return mk(1ll*A.fi*B.fi%MOD1,1ll*A.se*B.se%MOD2;)}
pii operator * (pii A,int B){return mk(1ll*A.fi*B%MOD1,1ll*A.se*B%MOD2);}
int n,fa[N],m,Base[N],vis[N]; pii H[N],pown[N];
vector<int> v[N];
vector<int> cir; int incir[N];
bool cmp(int x,int y){return H[x]<H[y];}
void findcir(int u){
    vis[u]=1;
    for(auto &to : v[u]){
        if(vis[to]){
            if(incir[to]) continue;
            int x=u;
            while(x!=to) cir.push_back(x),incir[x]=1,x=fa[x];
            cir.push_back(to); incir[to]=1;
        }
        else dfs(to);
    }
}

int dp[N],sz[N],dep[N];
int uppow[N],inv[N],ifac[N];
void dfs(int u){
    sz[u]=1; H[u]=mk(dep[u],dep[u]);
    for(auto &to : v[u]){
        if(incir[to]) continue;
        dep[to]=dep[u]+1; dfs(to); sz[u]+=sz[to];
        H[u]=H[u]*pown[sz[to]]+H[to];
    }
    sort(v[u].begin(),v[u].end(),cmp);
    for(int i=0,j;i<sz(v[u]);i=j+1){
        j=i; while(H[j]==H[i]&&j<sz(v[u])) j++;
        Mul(dp[u],mul(dp[v[u][i]],mul(uppow[j-i+1],ifac[j-i+1])));
    }
}

void init(){
    n=read(); m=read();
    Base[0]=1; for(int i=1;i<=n;i++) Base[i]=mul(Base[i-1],m);
    pown[0]=mk(1,1); for(int i=1;i<=n;i++) pown[i]=pown[i-1]*B;
    inv[1]=1; for(int i=2;i<=n;i++) inv[i]=mul(MOD-MOD/i,inv[MOD%i]);
    ifac[0]=1; for(int i=1;i<=n;i++) ifac[i]=mul(ifac[i-1],inv[i]);
    uppow[0]=1; for(int i=1;i<=n;i++) uppow[i]=mul(uppow[i-1],m+i-1);
    for(int i=1;i<=n;i++) fa[i]=read(),v[fa[i]].push_back(i);
    findcir(1); memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]) dep[i]=1,dfs(i);
}
//先处理树上的点，然后在环上用burnside，统计出最小循环节以后直接枚举变换，然后取gcd计算不动点（剩下的一定要和某一个树相同）
int main()
{
    
    return 0;
}