#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=1e9+7;
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
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=3005;
int Base[N],a[N],n;
pii q[N]; int Q;
int dp[N][N],lst[N][N],pre10[N],pre11[N],pre20[N],pre21[N];

int main()
{
    n=read(); Q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=Q;i++) q[i].first=read(),q[i].second=read();
    Base[0]=1; for(int i=1;i<=Q;i++) Base[i]=mul(Base[i-1],2);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) dp[i][j]=(a[i]>a[j]);
    }
    for(int i=1;i<=Q;i++){
        int pos1=q[i].first,pos2=q[i].second;
        if(pos1>pos2) swap(pos1,pos2);
        for(int j=1;j<=n;j++){
            if(j!=pos1){
                dp[pos1][j]=mul(dp[pos1][j],Base[i-lst[pos1][j]-1]);
                lst[pos1][j]=i;
                pre10[j]=dp[pos1][j];
                dp[j][pos1]=mul(dp[j][pos1],Base[i-lst[j][pos1]-1]);
                lst[j][pos1]=i;
                pre11[j]=dp[j][pos1];
            }

            if(j!=pos2&&j!=pos1){
                dp[pos2][j]=mul(dp[pos2][j],Base[i-lst[pos2][j]-1]);
                lst[pos2][j]=i;
                pre20[j]=dp[pos2][j];
                dp[j][pos2]=mul(dp[j][pos2],Base[i-lst[j][pos2]-1]);
                lst[j][pos2]=i;
                pre21[j]=dp[j][pos2];
            }
        }
        for(int j=1;j<=n;j++){
            if(j==pos1||j==pos2) continue;
            dp[pos1][j]=add(dp[pos1][j],pre20[j]);
            dp[j][pos1]=add(dp[j][pos1],pre21[j]);
            dp[pos2][j]=add(dp[pos2][j],pre10[j]);
            dp[j][pos2]=add(dp[j][pos2],pre11[j]);
        }
        dp[pos1][pos2]=add(pre10[pos2],pre11[pos2]);
        dp[pos2][pos1]=add(pre10[pos2],pre11[pos2]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=mul(dp[i][j],Base[Q-lst[i][j]]);
            //cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
            if(i<j) ans=add(ans,dp[i][j]);
        }
    }
    cout<<ans<<endl;
    return 0;
}