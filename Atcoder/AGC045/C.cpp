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
const int N=5005;
int dp[N][2],f[N][N][2],n,A,B,g[N];

int main()
{
    n=read(); A=read(); B=read();
    if(A>B) swap(A,B);
    f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        f[i][0][1]=f[i-1][0][1];
        for(int j=A;j<=i;j++) f[i][0][1]=add(f[i-1][j][1],f[i][0][1]);
        f[i][0][0]=f[i-1][0][0];
        for(int j=1;j<=i;j++){
            if(j<A) f[i][j][0]=add(f[i][j][0],f[i-1][j-1][0]);
            else f[i][j][1]=add(f[i][j][1],f[i-1][j-1][0]);
            f[i][j][1]=add(f[i][j][1],f[i-1][j-1][1]);
        }
        g[i]=f[i][0][1];
        for(int j=A;j<=i;j++) g[i]=add(g[i],f[i][j][1]);
    }
    dp[0][0]=dp[0][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j>=max(0,i-A+1);j--) 
            dp[i][0]=add(dp[i][0],dp[j][1]);
        for(int j=i-1;j>=max(0,i-B+1);j--)
            dp[i][1]=add(dp[i][1],dp[j][0]);
        if(i>=A+1){
            if(i-B+1<=0){
                dp[i][1]=add(dp[i][1],g[i-1]);
            }
            if(i!=n) for(int j=i-A-2;j>=max(1,i-B+1);j--){
                int len=i-j;
                dp[i][1]=add(dp[i][1],mul(dp[j][0],g[len-2]));
            }
            else{
                for(int j=i-A-1;j>=max(1,i-B+1);j--){
                    int len=i-j;
                    dp[i][1]=add(dp[i][1],mul(dp[j][0],g[len-1]));
                }
            }
        }
    }
    //for(int i=1;i<=n;i++) cout<<dp[i][0]<<" "<<dp[i][1]<<endl;
    printf("%d\n",sub(qpow(2,n),add(dp[n][0],dp[n][1])));
    return 0;
}