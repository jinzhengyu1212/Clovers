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
const int N=55;
const int M=1005;
#define int long long
int n,m,k;
int a[N],dis[N][N];

signed main()
{
    n=read(),m=read(),k=read();
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),w=read();
        checkmin(dis[x][y],w);
        checkmin(dis[y][x],w);
    }
    for(int i=1;i<=k;i++) a[i]=read();
    for(int mid=1;mid<=n;mid++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) checkmin(dis[i][j],dis[i][mid]+dis[mid][j]);
        }
    }
    int ans=INF;
    for(int l1=1;l1<=k;l1++){
        for(int r1=l1+1;r1<=k;r1++){
            for(int l2=1;l2<=k;l2++){
                for(int r2=l2+1;r2<=k;r2++){
                    if(l1==l2||l1==r2||r1==l2||r1==r2) continue;
                    checkmin(ans,dis[a[l1]][a[r1]]+dis[a[l2]][a[r2]]);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}