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
const int N=11;
int n,m; ll k,ans=0;
char s1[N],s2[N];//shu heng
ll dp[N][N];

void init(){
    dp[1][1]=k;
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++) 
            dp[i+1][j]+=dp[i][j]/2,dp[i][j+1]+=dp[i][j]/2,dp[i][j]&=1;
    }
    for(int i=1;i<=n;i++) ans+=dp[i][m]*(s1[i]=='1'),dp[i][m]&=1;
    for(int i=1;i<=m;i++) ans+=dp[n][i]*(s2[i]=='1'),dp[n][i]&=1;
}

const int B=71;
int Base[N*N];
const int _MOD=777787;
struct HashTable{
    int e=0,first[_MOD],nxt[_MOD<<1],point[_MOD<<1];
    vector<int> used;
    void add_edge(int )
    void clear(){
        e=0;
        for(auto &u : used) first[u]=-1;
        used.clear();
    }
}

void solve(){

}

int main()
{
    scanf("%d%d%lld",&n,&m,&k);
    scanf("%s",s1+1); scanf("%s",s2+1);
    init();
    return 0;
}