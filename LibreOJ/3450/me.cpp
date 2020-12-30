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
const int N=3005;
int dp[2][N][2],n;
pii a[N<<1];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=0;
    for(int i=1;i<=n;i++) a[i+n].first=read(),a[i+n].second=1;
    sort(a+1,a+n+n+1); reverse(a+1,a+n+n+1);
    dp[0][0][0]=1;
    for(int i=1;i<=n+n;i++){
        int pre=(i-1)&1,cur=i&1;
        memset(dp[cur],0,sizeof(dp[cur]));
        if(a[i].second==1){
            for(int j=0;j<=n;j++) Add(dp[cur][j+1][0],dp[pre][j][0]);
            for(int j=0;j<=n;j++) Add(dp[cur][j+1][1],dp[pre][j][1]);
            for(int j=0;j<=n;j++) Add(dp[cur][j][1],add(dp[pre][j][0],dp[pre][j][1]));
        }
        else{
            for(int j=1;j<=n;j++) Add(dp[cur][j-1][0],mul(j,dp[pre][j][0]));
            for(int j=0;j<=n;j++) Add(dp[cur][j][0],dp[pre][j][0]);
            for(int j=1;j<=n;j++) Add(dp[cur][j-1][1],mul(j,dp[pre][j][1]));
        }
    }
    cout<<add(dp[0][0][0],dp[0][0][1])<<endl;
    return 0;
}