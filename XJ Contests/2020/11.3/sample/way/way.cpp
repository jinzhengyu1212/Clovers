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
const int N=200005;
int n,a[N],q,x[N*10];
bool check(){for(int i=2;i<=n;i++) if(a[i]!=a[1]) return 0; return 1;}

int dis[N];
stack<int> stk;
void init(){
    memset(dis,-1,sizeof(dis));
    while(!stk.empty()) stk.pop();
    for(int i=n;i<n*2;i++) x[i]=x[i-n];
    if(x[n]>n) x[n]=n;
    for(int i=0;i<n*2;i++){
        int now=i%n;
        if(dis[now]!=-1||x[now]==n) continue;
        if(x[now]==n-1){
            if(!stk.empty()){
                int u=stk.top(); stk.pop();
                int to=u%n;
                dis[to]=i-u; dis[now]=i-u+(to>now);
            }
        } 
        else stk.push(i);
    }
    //for(int i=0;i<=n;i++) cout<<dis[i]<<" ";
}
void solve(ll X){
    int pos1=X%(n+1);
    int pos2=X%n;
    ll ret=n,step1=(X-pos1)/(n+1),step2=(X-pos2)/n;
    //out(pos1); out(pos2); out(step1); outln(step2);
    //out(dis[pos1]); outln(dis[pos2]);
    if((dis[pos1]>=step1||dis[pos1]==-1)&&x[pos1]==n+1&&pos1!=n) ret++;
    if((dis[pos2]>=step2||dis[pos2]==-1)&&x[pos2]==n-1) ret--;
    printf("%lld ",ret);
}

int main()
{
    int T; T=read();
    while(T--){
        n=read(); q=read();
        for(int i=0;i<n;i++) a[i]=read();
        if(check()){
            while(q--){
                ll X; scanf("%lld",&X);
                printf("%d ",a[1]);
            }
            puts(""); continue;
        }
        for(int i=0;i<n;i++) x[i]=a[i];
        init();
        for(int i=0;i<n;i++) x[i]=a[i];
        x[n]=n-(a[0]==n-1);
        for(int i=n+1;i<=1000000;i++){
            x[i]=n+(x[i-n-1]==n+1)-(x[i-n]==n-1);
        }
        while(q--){
            ll X;  scanf("%lld",&X);
            solve(X);
        }
        puts("");
    }
    return 0;
}