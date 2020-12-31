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
const int N=705;
int n,dep[N];
vector<int> v[N];

int dp1[N];
void dfs(int u,int f,int D){
    if(dep[u]==D) dp1[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dep[to]=dep[u]+1;
        dfs(to,u,D);
        Add(dp1[u],dp1[to]);
    }
}

int ans[N],dp2[N];
void solve(int from){
    for(int D=1;D<=n;D++){
        memset(dp1,0,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        dep[from]=0; dfs(from,-1,D); dp2[0]=1;
        for(auto &to : v[from]){
            for(int j=sz(v[from]);j>=1;j--){
                Add(dp2[j],mul(dp2[j-1],dp1[to]));
            }
        }
        for(int i=3;i<=sz(v[from]);i++) Add(ans[i],dp2[i]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++) solve(i);
    for(int i=3;i<n;i++) printf("%d\n",ans[i]);
    return 0;
}