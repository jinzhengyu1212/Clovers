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
const int N=405;
int n,a[N],b[N];
int dp[N][N][N],suma=0,sumb=0,S=0,inv[N],fac[N],ifac[N];
int C(int n,int m){return mul(fac[n],mul(ifac[m],ifac[n-m]));}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),S+=a[i],b[i]=read();
    for(int i=1;i<=400;i++) inv[i]=qpow(i,MOD-2);
    fac[0]=1; for(int i=1;i<=400;i++) fac[i]=mul(fac[i-1],i);
    for(int i=0;i<=400;i++) ifac[i]=qpow(fac[i],MOD-2);
    dp[0][0][0]=MOD-1;
    for(int i=0;i<=n;i++){
        suma+=a[i]; sumb+=b[i];
        for(int j=0;j<=suma;j++){
            for(int k=0;k<=sumb;k++){
                if(!dp[i][j][k]) continue;
                Add(dp[i+1][j][k],dp[i][j][k]);
                int sumT=j+a[i+1];
                for(int t=0,p=1;t<b[i+1];t++,Mul(p,a[i+1])){
                    int sumC=k+t;
                    int tmp=mul(dp[i][j][k],mul(p,ifac[t]));
                    Add(dp[i+1][sumT][sumC],mul(MOD-1,tmp));
                }
            }
        }
    }
    int ans=0;
    dp[n][0][0]=0;
    for(int i=0;i<=suma;i++){
        for(int j=0;j<=sumb;j++){
            int tmp=mul(dp[n][i][j],mul(S,inv[i]));
            Mul(tmp,fac[j]); int tmp2=qpow(i,j);
            Mul(tmp,qpow(tmp2,MOD-2));
            Add(ans,tmp);
        }
    }
    cout<<ans<<endl;
    return 0;
}