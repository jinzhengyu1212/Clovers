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
const int N=100005;
int n,k;
ll dp[2][1005][1005];

struct node{
    int w,s,p;
    bool operator < (const node &rhs) const{
        if(w==rhs.w) return p+(p==2)*3>rhs.p+(rhs.p==2)*3;
        return w<rhs.w;
    }
}a[N];

int main()
{
    n=read(); k=read();
    for(int i=1;i<=n;i++) a[i].w=read(),a[i].s=read(),a[i].p=read();
    sort(a+1,a+n+1);
    if(k*2>n){
        puts("-1");
        return 0;
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0]=0; int idx=0;
    for(int i=1;i<=n;i++){
        idx^=1;
        for(int j1=0;j1<=k;j1++)
            for(int j2=0;j2<=k;j2++) dp[idx][j1][j2]=dp[idx^1][j1][j2];
        for(int j2=0;j2<=min(i,k);j2++){
            for(int j1=0;j1<=j2&&j2+j1<=min(i,2*k);j1++){
                if(a[i].p==1){
                    if(j1) checkmin(dp[idx][j1][j2],dp[idx^1][j1-1][j2]+a[i].s);
                }
                else if(a[i].p==2){
                    if(j2) checkmin(dp[idx][j1][j2],dp[idx^1][j1][j2-1]+a[i].s);
                }
                else{
                    if(j1) checkmin(dp[idx][j1][j2],dp[idx^1][j1-1][j2]+a[i].s);
                    if(j2) checkmin(dp[idx][j1][j2],dp[idx^1][j1][j2-1]+a[i].s);
                }
                //out(i); out(j1); out(j2); outln(dp[idx][j1][j2]);
            }
        }
    }
    if(dp[idx][k][k]>1e15) puts("-1");
    else printf("%lld\n",dp[idx][k][k]);
    return 0;
}