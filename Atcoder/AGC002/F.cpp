#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=(int)1e9+7;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){c=getchar(); if(c=='-') f=-1;}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=500005;
const int M=2005;
int n,k,dp[M][M],fac[M*M],inv[M*M];
int C(int X,int Y){
    return mul(fac[X],mul(inv[X-Y],inv[Y]));
}

int main()
{
    n=read(); k=read();
    if(k==1){
        puts("1");
        return 0;
    }
    fac[0]=1;
    for(int i=1;i<=n*k;i++) fac[i]=mul(fac[i-1],i);
    inv[n*k]=qpow(fac[n*k],MOD-2);
    for(int i=n*k-1;i>=0;i--) inv[i]=mul(inv[i+1],i+1);
    dp[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(i<n) dp[i+1][j]=add(dp[i][j],dp[i+1][j]);
            if(j<n&&j!=i){
                int rest=n*k-j*k-(i-j)-1;
                dp[i][j+1]=add(dp[i][j+1],mul(n-j,mul(dp[i][j],C(rest,k-2))));
            }
        }
    }
    cout<<dp[n][n]<<endl;
    return 0;
}