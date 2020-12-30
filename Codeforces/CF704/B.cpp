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
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=5005;
int n,S,T;
ll dp[2][N][4],a[N],b[N],c[N],d[N],x[N];
void init(){
    scanf("%d%d%d",&n,&S,&T);
    for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=x[i];
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]),b[i]-=x[i];
    for(int i=1;i<=n;i++) scanf("%lld",&c[i]),c[i]+=x[i];
    for(int i=1;i<=n;i++) scanf("%lld",&d[i]),d[i]-=x[i];
}
ll calc(ll i,ll j){
    return i<j ? d[i]+a[j] : c[i]+b[j];
}

int main()
{
    init();
    if(n==2){
        printf("%lld\n",calc(S,T));
        return 0;
    }
    memset(dp,0x3f,sizeof(dp));
    int lst=n; if(S==lst||T==lst) lst--;
    if(S==lst||T==lst) lst--;
    int flagS=0,flagT=0;
    int idx=0;
    dp[0][2][0]=0;
    for(int i=1;i<=n;i++){
        if(i==S) flagS=1; if(i==T) flagT=1;
        if(i==S||i==T) continue;
        idx^=1; 
        memset(dp[idx],0x3f,sizeof(dp[idx]));
        int conS,conT;
        if(flagS==0) conS=c[S]+b[i]; else conS=d[S]+a[i];
        if(flagT==0) conT=a[T]+d[i]; else conT=b[T]+c[i];
        for(int j=1;j<=n;j++){
            if(i!=lst&&j==1) continue;
            if(n==3){
                checkmin(dp[idx][j][3],dp[idx^1][j+1][0]+conS+conT);
            }
            for(int k=0;k<=3;k++){
                if(j>=2||i==lst) checkmin(dp[idx][j][k],dp[idx^1][j+1][k]+a[i]+c[i]);
                if(j>=3||k&1)checkmin(dp[idx][j][k],dp[idx^1][j][k]+a[i]+d[i]);
                if(j>=3||k&2) checkmin(dp[idx][j][k],dp[idx^1][j][k]+c[i]+b[i]);
                checkmin(dp[idx][j][k],dp[idx^1][j-1][k]+b[i]+d[i]);
                if(k&1){
                    if(j>=2) checkmin(dp[idx][j][k],dp[idx^1][j+1][k^1]+conS+c[i]);
                    checkmin(dp[idx][j][k],dp[idx^1][j][k^1]+conS+d[i]);
                }
                if(k&2){
                    checkmin(dp[idx][j][k],dp[idx^1][j][k^2]+conT+b[i]);
                    if(j>=2) checkmin(dp[idx][j][k],dp[idx^1][j+1][k^2]+conT+a[i]);
                }
            }
        }
    }   
    printf("%lld\n",dp[idx][1][3]);
    return 0;
}