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
const int N=500005;
int dp[N][3][2],f[3][2];
int tranN[3][2]={{3,1},{2,0},{1,3}};
int tranC[3][2]={{0,1},{1,0},{0,1}};
char s[N]; int n; vector<int> v[N];
int bl[N];
void dfs1(int u,int f){
    bl[u]=(s[u]=='0');
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs1(to,u); bl[u]+=bl[to];
    }
}

void dfs2(int u,int fa){
    for(int i=0;i<=2;i++) dp[u][i][(s[u]-'0')^1]=1; 
    for(auto &to : v[u]){
        if(!bl[to]||to==fa) continue;
        dfs2(to,u);
        memset(f,0x3f,sizeof(f));
        for(int numu=0;numu<=2;numu++){
            for(int colu=0;colu<=1;colu++){
                for(int numto=0;numto+numu<=2;numto++){
                    for(int colto=0;colto<=1;colto++){
                        checkmin(f[numu+numto][colu^tranC[numto][colto]],
                        dp[u][numu][colu]+dp[to][numto][colto]+tranN[numto][colto]);
                    }
                }
            }
        }
        memcpy(dp[u],f,sizeof(f));
    }
}

int main()
{
    memset(dp,0x3f,sizeof(dp));
    n=read(); scanf("%s",s+1);
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs1(1,-1); dfs2(1,-1);
    int ans=inf;
    for(int i=1;i<=n;i++) if(bl[i]==bl[1]) checkmin(ans,dp[i][2][1]);
    cout<<ans<<endl;
    return 0;
}