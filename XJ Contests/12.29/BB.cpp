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
const int N=505;
int n,k,a[N];
int dp[N][N][N],sum[N][N][N],pos[N],L[N],R[N];
 
int main()
{
    n=read(); k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++){
        L[i]=i; R[i]=i;
        for(int j=i-1;j>=1;j--){
            if(a[i]>a[j]) L[i]=j;
            else break;
        }
        for(int j=i+1;j<=n;j++){
            if(a[i]>a[j]) R[i]=j;
            else break;
        }
    }
    dp[1][0][1]=1;
    for(int i=2;i<=n;i++){
        if(L[i]>1) continue;
        dp[1][1][i]=1;
    }
    for(int t=1;t<=n;t++){
        for(int j=0;j<=1;j++){
            sum[1][t][j]=add(dp[1][j][t],sum[1][t-1][j]);
        }
    }
    a[0]=inf;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=min(i,k);j++){
            for(int t=1;t<i;t++){
                if(R[t]<i) continue;
                Add(dp[i][j+1][t],sum[i-1][t-1][j]);
                if(t!=i-1) Add(dp[i][j][t],dp[i-1][j][t]);
                else{
                    if(a[i-1]<a[i-2]){
                        Add(dp[i][j+1][t],dp[i-1][j][t]);
                    }
                    else{
                        Add(dp[i][j+1][t],sum[i-2][j][i-2]);
                        Add(dp[i][j][t],dp[i-2][j][t]);
                    }
                }
            }
            for(int t=1;t<=i;t++) Add(dp[i][j][i],dp[i-1][j][t]);
            for(int t=i+1;t<=n;t++){
                if(L[t]>i) continue;
                Add(dp[i][j+1][t],sum[i-1][t-1][j]);
                Add(dp[i][j][t],dp[i-1][j][t]);
            }
        }
        for(int t=1;t<=n;t++){
            for(int j=0;j<=min(i,k);j++){
                sum[i][t][j]=add(dp[i][j][t],sum[i][t-1][j]);
                //if(dp[i][j][t]) out(i),out(j),out(t),outln(dp[i][j][t]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=k;i++){
        for(int j=1;j<=n;j++) Add(ans,dp[n][i][j]);
    }
    cout<<ans<<endl;
    return 0;
}
