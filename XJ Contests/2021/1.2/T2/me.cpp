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
const int N=1005;
int n,dp[N][N],match[N],a[N],top=0,vis[N],tmp[N];
void init(){
    n=read(); top=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) tmp[i]=read();
    for(int i=1;i<=n;i++){
        int x=read();
        match[tmp[i]]=x;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        int x=match[i],len=1; top++;
        while(x!=i){
            len++;
            vis[x]=1;
            x=match[x];
        }
        a[top]=len; vis[i]=1;
    }
}

void solve(){
    int ans=0;
    for(int i=1;i<=n;i++) if(match[i]==i) ans++;
    for(int l=2;l<=n;l++){
        dp[l][l]=l-1;
        for(int i=l+1;i<=n;i++){
            dp[l][i]=max(dp[l][i-l]+l-1,dp[l][i-l-1]+l);
        }
        int sum=0;
        for(int i=1;i<=top;i++) sum+=dp[l][a[i]];
        checkmax(ans,sum);
    }
    printf("%d\n",ans);
}

int main()
{
    int T=read();
    while(T--){
        init();
        solve();
    }
    return 0;
}