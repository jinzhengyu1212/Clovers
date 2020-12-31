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
const int N=60;
int mp[N][N][4105];
int n,m,S,T,p;
vector<int> v[N];

void dfs(int u,int dis,int from){
    if(mp[from][u][dis]!=-1||dis>4096) return;
    mp[from][u][dis]=1;
    for(int i=0;i<v[u].size();i++){
        int to=v[u][i]; dfs(to,dis+1,from);
    }
}

int split(int x){
    int ret=0;
    for(int i=0;(1<<i)<=x;i++){
        if(x>>i&1){
            if(i<p) ret++;
            else ret+=qpow(2,i-p+1);
        }
    }
    return ret;
}

int dis[N][N];
int main()
{
    scanf("%d%d%d%d%d",&n,&m,&p,&S,&T);
    memset(mp,-1,sizeof(mp));
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y);
    }
    for(int i=1;i<=n;i++) dfs(i,0,i);
    memset(dis,0x3f,sizeof(dis));
    for(int from=1;from<=n;from++){
        dis[from][from]=0;
        for(int to=1;to<=n;to++) if(from!=to){
            for(int k=1;k<=1024;k++) if(mp[from][to][k]!=-1){
                checkmin(dis[from][to],split(k));
            }
        }
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                checkmin(dis[i][j],dis[i][k]+dis[k][j]);
    cout<<dis[S][T]<<endl;
    return 0;
}