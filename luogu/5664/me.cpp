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
const int N=105;
const int M=2005;
int n,m,a[N][M],dp[N][N<<1],s[N];
const int B=100;
int sum=1;

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++) a[i][j]=read(),s[i]=add(s[i],a[i][j]);
    for(int i=1;i<=n;i++){
        sum=mul(sum,s[i]+1);
    }
    sum=sub(sum,1);
}

int calc(int col){
    int ret=0;
    memset(dp,0,sizeof(dp));
    dp[0][B]=1;
    for(int rnd=0;rnd<n;rnd++){
        int rest=sub(s[rnd+1],a[rnd+1][col]);
        for(int i=B-rnd;i<=rnd+B;i++){
            int tmp=dp[rnd][i];
            if(!tmp) continue;
            dp[rnd+1][i]=add(dp[rnd+1][i],tmp);
            dp[rnd+1][i-1]=add(dp[rnd+1][i-1],mul(tmp,rest));
            dp[rnd+1][i+1]=add(dp[rnd+1][i+1],mul(tmp,a[rnd+1][col]));
        }
    }
    for(int i=B+1;i<=n+B;i++) ret=add(ret,dp[n][i]); 
    return ret;
}

void solve(){
    for(int i=1;i<=m;i++) sum=sub(sum,calc(i)); 
    printf("%d\n",sum);
}

int main()
{
    //freopen("dinner.in","r",stdin);
    //freopen("dinner.out","w",stdout);
    init(); solve();
    fclose(stdin); fclose(stdout);
    return 0;
}