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
const int N=1000005;
int n,a[N],nxt[N][4],tmp[4]; char s[N];
int dp[N];

int main()
{
    n=read();
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) a[i]=a[i-1]^(s[i]-'A'+1);
    for(int i=0;i<4;i++) tmp[i]=n+1;
    for(int i=n;i>=0;i--){
        for(int j=0;j<4;j++) nxt[i][j]=tmp[j];
        tmp[a[i]]=i;
    }
    sort(s+1,s+n+1);
    if(s[1]==s[n]){puts("1"); return 0;}
    int ans=0;
    dp[0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<4;j++){
            if(j==a[i]) continue;
            Add(dp[nxt[i][j]],dp[i]);
        }
        if(a[i]==a[n]&&i) Add(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}