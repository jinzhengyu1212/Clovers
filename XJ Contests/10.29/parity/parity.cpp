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
const int N=205;
int T,n,a[N];
ll m,S;
void init(){
    scanf("%lld%lld%d",&m,&S,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
}

bitset<250000> dp,tmp;
void solve(){
    dp.reset(); tmp.reset(); dp.set(0);
    for(ll i=0;i<=61;i++){
        if(m>>i&1){
            tmp=dp;
            for(int j=0;j<=n;j++) dp^=(tmp<<a[j]);
        }
        tmp.reset();
        if(S>>i&1){
            for(int j=0;j<=100000;j++) tmp[j]=dp[j*2+1];
        }
        else
            for(int j=0;j<=100000;j++) tmp[j]=dp[j*2];
        dp=tmp;
    }
    cout<<dp[0]<<endl;
}

int main()
{
    scanf("%d",&T);
    while(T--){
        init(); 
        solve();
    }
    return 0;
}