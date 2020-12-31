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
int add4(int x,int y,int p,int q){return add(add(x,y),add(p,q));}
int add3(int x,int y,int z){return add(x,add(y,z));}
int ADD(int &x,int y){x=add(x,y);}
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
const int N=5005;
struct Edge{
    int from,to;
}E[N];
int n,id[N],rk[N],in[N],sz[N];
vector<int> v[N],G[N];
int dp[4][N][N];
int tmp[4][N];
void dfs(int u,int f){
    dp[0][u][1]=1; sz[u]=1;
    for(auto to : v[u]){//down
        if(to==f) continue;
        dfs(to,u); sz[u]+=sz[to];
        for(int j1=1;j1<=sz[u];j1++){
            int u0=dp[0][u][j1],u1=dp[1][u][j1],u2=dp[2][u][j1],u3=dp[3][u][j1];
            if(!u0&&!u1&&!u2&&!u3) continue;
            for(int j2=1;j2<=sz[to];j2++){
                int v0=dp[0][to][j2],v1=dp[1][to][j2],v2=dp[2][to][j2],v3=dp[3][to][j2];
                if(!v0&&!v1&&!v2&&!v3) continue;
                ADD(tmp[0][j1+j2],mul(u0,add4(v0,v1,v2,v3)));
                ADD(tmp[1][j1+j2-1],(MOD-mul(u0,add(v0,v1)))%MOD);
                ADD(tmp[1][j1+j2],mul(u1,add4(v0,v1,v2,v3)));
            }
        }
        for(int j=1;j<=sz[u];j++){
            for(int id=0;id<4;id++){
                dp[id][u][j]=tmp[id][j];
            }
        }
        for(int j=1;j<=sz[u];j++){
            for(int id=0;id<4;id++){
                tmp[id][j]=0;
            }
        }
    }
    for(auto to : G[u]){//up
        if(to==f) continue;
        dfs(to,u); sz[u]+=sz[to];
        for(int j1=1;j1<=sz[u];j1++){
            int u0=dp[0][u][j1],u1=dp[1][u][j1],u2=dp[2][u][j1],u3=dp[3][u][j1];
            if(!u0&&!u1&&!u2&&!u3) continue;
            for(int j2=1;j2<=sz[to];j2++){
                int v0=dp[0][to][j2],v1=dp[1][to][j2],v2=dp[2][to][j2],v3=dp[3][to][j2];
                if(!v0&&!v1&&!v2&&!v3) continue;
                ADD(tmp[0][j1+j2],mul(u0,add4(v0,v1,v2,v3)));
                ADD(tmp[1][j1+j2],mul(u1,add4(v0,v1,v2,v3)));
                ADD(tmp[2][j1+j2-1],(MOD-mul(u0,add(v0,v2)))%MOD);
                ADD(tmp[2][j1+j2],mul(u2,add4(v0,v1,v2,v3)));
                ADD(tmp[3][j1+j2-1],(MOD-mul(u1,add(v0,v2)))%MOD);
                ADD(tmp[3][j1+j2],mul(u3,add4(v0,v1,v2,v3)));
            }
        }
        for(int j=1;j<=sz[u];j++){
            for(int id=0;id<4;id++){
                dp[id][u][j]=tmp[id][j];
            }
        }
        for(int j=1;j<=sz[u];j++){
            for(int id=0;id<4;id++){
                tmp[id][j]=0;
            }
        }
    }
}

int fac[N];
int main()
{
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    for(int i=1;i<n;i++){
        scanf("%d%d",&E[i].from,&E[i].to);
        v[E[i].from].push_back(E[i].to); 
        G[E[i].to].push_back(E[i].from);
    }
    dfs(1,-1);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<4;j++){
            ADD(ans,mul(dp[j][1][i],fac[i]));
        }
    cout<<ans<<endl;
    return 0; 
}