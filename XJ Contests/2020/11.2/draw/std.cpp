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
const int N=501;
const int M=1005;
int dp[2][N][N];
int n,m,a[N];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) dp[1][i][1]=1;
    for(int i=1;i<n;i++){
        memset(dp[(i%2)^1],0,sizeof(dp[(i%2)^1]));
        int idx=i%2;
        for(int j=1;j<=m;j++){
            int sum=0;
            for(int k=1;k<=min(i,a[j]);k++){
                //out(i); out(j); out(k); outln(dp[i][j][k]);
                sum=add(sum,dp[idx][j][k]);
                int tmp=dp[idx][j][k];
                if(k<a[j]) dp[idx^1][j][k+1]=add(dp[idx^1][j][k+1],tmp);
            }
            for(int to=1;to<=m;to++){
                if(to==j) continue;
                dp[idx^1][to][1]=add(dp[idx^1][to][1],sum);
            }
        }
    }
    int ans=0;
    for(int j=1;j<=m;j++){
        for(int k=1;k<=a[j];k++) ans=add(ans,dp[n%2][j][k]);
    }
    cout<<ans<<endl;
    return 0;
}