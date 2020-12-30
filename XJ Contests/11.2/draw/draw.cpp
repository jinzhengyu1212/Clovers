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
int mul3(int x,int y,int z){return mul(mul(x,y),z);}
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
const int N=5005;
const int M=100005;
int n,m,a[M],cnt[N],sum[N],ssum[N];
int dp[N][N],pre[N][N];

int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        a[i]=read();
    }
    for(int i=1;i<=m;i++) cnt[a[i]]++;
    //cout<<cnt[1]<<endl;
    dp[0][0]=1; sum[0]=1; ssum[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5000;j++) if(cnt[j]) {
            int tmp1=sub(ssum[i-1],(i-j-1>=0 ? ssum[i-j-1] : 0));
            int tmp2=sub(pre[j][i-1],(i-j-1>=0 ? pre[j][i-j-1] : 0));
            dp[i][j]=sub(tmp1,tmp2);
            pre[j][i]=add(pre[j][i-1],dp[i][j]);
            sum[i]=add(sum[i],mul(dp[i][j],cnt[j]));
        }
        ssum[i]=add(ssum[i-1],sum[i]);
    }
    int ans=0;
    for(int i=1;i<=5000;i++) ans=add(ans,mul(cnt[i],dp[n][i]));
    cout<<ans<<endl;
    return 0;
}