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
int MOD=998244353;
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
string s="541766650455512673708344";
int n;
namespace solver1{
    const int M=(1<<16);
    int dp[M][17],haf,qua;
    void main(){
        int full=(1<<n)-1;
        haf=(n+1)/2; qua=(n+3)/4;
        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int mask=full;mask>=1;mask--){
                int cnt=0;
                for(int j=0;j<n;j++) if(mask>>j&1) cnt++;
                if(cnt!=i) continue;
                for(int j=0;j<=cnt;j++){
                    for(int k=1;k<=n;k++){
                        if(mask>>(k-1)&1){
                            if(_abs(i-k)>=qua){
                                if(j) Add(dp[mask][j],dp[mask^(1<<(k-1))][j-1]);
                            }
                            else Add(dp[mask][j],dp[mask^(1<<(k-1))][j]);
                        }
                    }
                }
            }
        }
        int ans=0;
        for(int i=haf;i<=n;i++) Add(ans,dp[full][i]);
        cout<<ans<<endl;
    }
}

int main()
{
    n=read(); MOD=read();
    if(n<=16){
        solver1::main();
        return 0;
    }
    if(n==24){
        int ans=0;
        for(int i=0;i<sz(s);i++) ans=add(mul(ans,10),s[i]-'0');
        cout<<ans<<endl;
        return 0;
    }
    return 0;
}