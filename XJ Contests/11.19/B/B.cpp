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
const int N=10005;
int n,k,dp[N][55];
int p[N][55],sum[N];
char s[N];
vector<int> v;

int main()
{
    n=read(); k=read();
    scanf("%s",s+1);
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            int bl=((i+j)%10==0&&s[i]=='0');
            for(int pre=0;pre<=j;pre++){
                if(dp[i-1][pre]+bl>dp[i][j]){
                    dp[i][j]=dp[i-1][pre]+bl;
                    p[i][j]=pre;
                }
            }
        }        
    }
    int ans=inf,y;
    for(int j=0;j<=k;j++){
        if((n+j)/10-dp[n][j]<ans){
            ans=(n+j)/10-dp[n][j];
            y=j;
        }
    }
    for(int i=n;i>=1;i--){
        sum[i]=y-p[i][y];
        y=p[i][y];
    }
    int cnt=0; v.clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sum[i];j++) v.push_back(++cnt);
        cnt++;
    }
    cout<<ans<<endl;
    printf("%d ",sz(v));
    for(int i=0;i<(sz(v));i++) printf("%d ",v[i]); cout<<endl;
    
    /*assert(sz(v)<=k);
    static int vis[N];
    memset(vis,0,sizeof(vis));
    for(auto &to : v) vis[to]=1;
    int i=1;cnt=0;
    string str="2";
    while(i<=n){
        cnt++;
        if(vis[cnt]) str+='0';
        else str+=s[i++]; 
    }
    int S=0;
    for(int i=1;i<str.size();i++) S+=(str[i]=='1'&&i%10==0);
    assert(S==ans);
    cerr<<str<<endl;
    cerr<<"Accepted!"<<endl;*/
    return 0;
}