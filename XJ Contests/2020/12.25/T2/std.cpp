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
const ll INF=(ll)5e16;
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
const int N=100005;
char s[N];
int a[N],K,n;
namespace solver1{
    ll dp[105][105][105];
    void main(){
        memset(dp,0x3f,sizeof(dp)); 
        dp[0][0][0]=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<=K;j++){
                for(int k=0;k<=i;k++){
                    //if(dp[i][j][k]<inf) out(i),out(j),out(k),outln(dp[i][j][k]);
                    checkmin(dp[i+1][j][k],dp[i][j][k]);
                    if(s[i+1]=='(') checkmin(dp[i+1][j][k+1],dp[i][j][k]+a[i+1]);
                    else if(k) checkmin(dp[i+1][j+1][k-1],dp[i][j][k]+a[i+1]);
                }
            }
        }
        if(dp[n][K][0]>=INF) puts("-1");
        else printf("%lld\n",dp[n][K][0]);
    }
}
bool check(){for(int i=1;i<n;i++) if(a[i]<a[i+1]) return 0; return 1;}
namespace solver2{
    ll ans=0;
    void main(){
        int cnt=0,tot=0;
        for(int i=n;i>=1;i--){
            if(s[i]==')'&&cnt+tot<K) ans+=a[i],cnt++;
            else if(s[i]=='('&&cnt) ans+=a[i],cnt--,tot++;
        }
        cout<<ans<<endl;
    }
}

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++) a[i]=read();
    scanf("%d",&K);
    if(K&1){puts("-1"); return 0;}
    K/=2;
    if(n<=100){
        solver1::main();
        return 0;
    }
    if(check()){
        solver2::main();
        return 0;
    }
    return 0;
}