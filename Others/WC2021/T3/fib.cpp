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
int n,m;

namespace solver1{
    const int N=1005;
    int dp[N][N],vis[N][N];    
    int dfs(int x,int y){
        if(dp[x][y]!=-1) return dp[x][y];
        if(vis[x][y]) return -1;
        vis[x][y]=1;
        int ret=dfs(y,(x+y)%m);
        if(ret!=-1) ret++;
        return dp[x][y]=ret;
    }
    void main(){
        memset(dp,-1,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int i=0;i<=m;i++) dp[0][i]=0;
        for(int i=1;i<=m;i++) dp[i][0]=1;
        for(int i=1;i<=n;i++){
            int x=read(),y=read();
            printf("%d\n",dfs(x,y));
        }
    }
}

namespace solver2{
    int x,y;
    void main(){
        while(n--){
            x=read(); y=read();
            if(x==0){
                puts("0"); continue;
            }
            if(y==0){
                puts("1"); continue;
            }
            int flag=0;
            for(int now=2;now<=m*m;now++){
                int tmp=(x+y)%m; x=y; y=tmp;
                if(y==0){
                    printf("%d\n",now); flag=1;
                    break;
                }
            }
            if(!flag) puts("-1");
        }
    }
}

void solve(){
    n=read(); m=read();
    if(m<=1000){
        solver1::main();
        return;
    }
    else{
        solver2::main();
        return;
    }
}

int main()
{
    freopen("fib.in","r",stdin);
    freopen("fib.out","w",stdout);
    solve();
    fclose(stdin); fclose(stdout);
    return 0;
}