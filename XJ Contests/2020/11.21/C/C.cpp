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
const int MOD=1e9+7;
int add(int x,int y){x+=y; return x>=MOD ? x%MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x%=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x=(x%MOD)+MOD;}
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
const int N=1000005;
int n,fa[N],w[N];
vector<int> v[N];
char opt[5];

void init(){
    scanf("%lld",&n); scanf("%s",opt);
    for(int i=1;i<=n;i++) w[i]=read();
    for(int i=2;i<=n;i++){
        fa[i]=read();
        v[fa[i]].push_back(i);
    }
}

int Opt(int x,int y){
    if(opt[0]=='X') return (x^y);
    else if(opt[0]=='A') return (x&y);
    else if(opt[0]=='O') return (x|y);
}

namespace solver1{
    int dp[N];
    void main(){
        int ans=0;
        for(int i=1;i<=n;i++){
            int pre=fa[i];
            if(pre) dp[i]=dp[pre]+Opt(w[pre],w[i]);
            ans=(ans+(dp[i]+w[i])%MOD*i%MOD)%MOD;
        }
        cout<<ans<<endl;
    }
}

namespace solver2{
    int pre[N][30],dp[N];
    void main(){
        memset(pre,0,sizeof(pre));
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<30;j++) if(pre[fa[i]][j]){
                int pos=pre[fa[i]][j];
                checkmax(dp[i],dp[pos]+Opt(w[pos],w[i]));
            }
            for(int j=0;j<30;j++){
                pre[i][j]=pre[fa[i]][j];
                if(w[i]>>j&1) pre[i][j]=i;
            }
            ans=(ans+(dp[i]+w[i])%MOD*i%MOD)%MOD;
        }
        cout<<ans<<endl;
    }
}

void solve(){
    if(opt[0]=='X'||opt[0]=='O'){
        solver1::main();
        return;
    }
    else solver2::main();
}

signed main()
{
    init();
    solve();
    return 0;
}