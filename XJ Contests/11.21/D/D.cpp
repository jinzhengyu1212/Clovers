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
const int N=5005;
int Base[N],f[N][N],n,K,m;

int calc(int x,int y){
    return sub(f[x][y],f[x][y-1]);
}

int main()
{
    n=read(); K=read(); m=read();
    for(int i=1;i<=n;i++) Base[i]=qpow(i,m);
    for(int i=0;i<=K;i++) f[0][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=K;j++){
            if(i<j) f[i][j]=f[i][j-1];
            else f[i][j]=add(f[i][j-1],f[i-j][j]);
        }
    }
    int ans=0;
    for(int x=1;x<=n;x++){
        for(int i=1;i*x<=n&&i<=K;i++){
            Add(ans,mul(calc(n-i*x,K-i),Base[x]));
        }
    }
    cout<<ans<<endl;
    return 0;
}