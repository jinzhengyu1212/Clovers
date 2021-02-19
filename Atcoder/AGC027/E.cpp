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
const int N=100005;
int n,a[N],sum[N],dp[N],Nxt[N][3],nxt[N][3],able[N]; 
char s[N];

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++) a[i]=s[i]-'a'+1;
    for(int i=1;i<=n;i++) sum[i]=(sum[i-1]+a[i])%3;
    for(int i=0;i<3;i++) Nxt[n][i]=n+1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<3;j++) Nxt[i][j]=Nxt[i+1][j];
        Nxt[i][sum[i+1]]=i+1;
    }
    able[n]=n;
    for(int i=n-1;i>=1;i--) able[i]=(s[i]==s[i+1] ? i : able[i+1]);
    able[0]=able[1];
    for(int i=2;i<=n;i++){
        if(able[1]<i) able[i]=i;
    }
    for(int i=0;i<=n;i++)
        for(int j=0;j<3;j++){
            nxt[i][j]=Nxt[able[i]][j];
        } 
    dp[0]=1;
    int ans=0; 
    for(int i=0;i<n;i++){
        if(sum[n]==sum[i]&&able[i]<n&&i) Add(ans,dp[i]);
        Add(dp[i+1],dp[i]); 
        int num=(sum[i]+3-a[i+1])%3;
        Add(dp[nxt[i][num]],dp[i]);
    }
    cout<<add(ans,dp[n])<<endl;
    return 0;
}