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
const int N=100005;
ll one[N],two[N],a[N];
int n; vector<int> v[N];
int in[N]; 

void dfs(int u,int f){
    ll sum=0,bl=0,mx=0;
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs(to,u); bl++;
        sum+=a[to]; checkmax(mx,a[to]);
    }
    if(bl){
        one[u]=2*a[u]-sum;
        two[u]=sum-a[u];
        //out(u); out(one[u]); outln(two[u]);
        if(one[u]<0||two[u]<0){
            puts("NO");
            exit(0);
        }
        if(sum-mx<two[u]){
            puts("NO");
            exit(0);
        }
        a[u]-=two[u];
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
        in[x]++; in[y]++;
    }
    int Rt;
    for(int i=1;i<=n;i++) if(in[i]==1) Rt=i;
    dfs(Rt,-1);
    puts("YES");
    return 0;
}