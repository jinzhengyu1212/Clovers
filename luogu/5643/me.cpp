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
const int N=19;
int dp[1<<N];
int A[N],B[N],F[1<<N],deg[N],n,Q,Rt;
vector<int> v[N];

void dfs(int u,int f,int S){
    if(S>>(u-1)&1) return;
    int suma=0,sumb=deg[u];
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs(to,u,S);
        Add(suma,A[to]);
        Add(sumb,B[to]);
    }
    A[u]=qpow(sub(deg[u],suma),MOD-2); B[u]=mul(sumb,A[u]);
}

void FWT_or(int *a,int len){
    for(int h=1;h<len;h<<=1){
        for(int i=0;i<len;i+=(h<<1)){
            for(int j=i;j<i+h;j++) Add(a[j+h],a[j]);
        }
    }
}

int count(int x){
    int ret=0;
    for(int i=0;i<n;i++) if(x>>i&1) ret++;
    return ret;
}

int main()
{
    n=read(); Q=read(); Rt=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        deg[x]++; deg[y]++;
        v[x].push_back(y); v[y].push_back(x);
    }
    int full=(1<<n)-1;
    for(int S=1;S<=full;S++){
        for(int i=1;i<=n;i++) A[i]=B[i]=0;
        dfs(Rt,-1,S);
        F[S]=mul((count(S)&1 ? 1 : MOD-1),B[Rt]);
    }
    F[0]=0;
    FWT_or(F,1<<n);
    while(Q--){
        int S=0,C=read();
        for(int i=1;i<=C;i++){
            int x=read(); S|=(1<<(x-1));
        }
        printf("%d\n",F[S]);
    }
    return 0;
}