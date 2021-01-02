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
const int N=500005;
int a[N],b[N],aa[N],bb[N],n,p[N];
int dp[11][11];

void solve(){
    n=read(); int ans=0;
    for(int i=1;i<=n;i++) aa[i]=read();
    for(int i=1;i<=n;i++) bb[i]=read();
    for(int i=1;i<=n;i++) p[i]=i;
    do{
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++) a[i]=aa[p[i]],b[i]=bb[p[i]];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
                checkmax(ans,dp[i][j]);
            }
        }
    }while(next_permutation(p+1,p+n+1));
    printf("%d\n",ans);
}

int main()
{
    int T=read();
    while(T--){
        solve();
    }
    return 0;
}