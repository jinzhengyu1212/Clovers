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
const int N=505;
const int M=200005;
#define int long long
int n,a[N][N];
int prime[M],tot=0,bl[M];
int lcm(int x,int y){return x/__gcd(x,y)*y;}
void init(){
    for(int i=2;i<M;i++){
        if(!bl[i]) prime[++tot]=i;
        for(int j=1;j<=tot;j++){
            if(i*prime[j]>=M) break;
            bl[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}

signed main()
{
    init();
    n=read();
    if(n==2){
        puts("4 7\n23 10");
        return 0;
    }
    int cnt=0;
    for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) a[i][j]=1;
    for(int s=2;s<=2*n;s+=2){
        int now=prime[++cnt];
        for(int i=1;i<=n;i++){
            int j=s-i;
            if(j>n||j<=0) continue;
            a[i][j]=now;
        }
    }
    for(int d=-n+1;d<=n-1;d++){
        int now=prime[++cnt];
        for(int i=1;i<=n;i++){
            int j=i-d;
            if(j>n||j<=0) continue;
            a[i][j]*=now;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%2==1){
                a[i][j]=lcm(lcm(a[i-1][j],a[i][j-1]),lcm(a[i+1][j],a[i][j+1]))+1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%lld ",a[i][j]);
        } puts("");
    }
    return 0;
}