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
const int N=105;
const int M=5505;
int dp[N][M][N],n,m;

int main()
{
    scanf("%d%d",&n,&m); m=n+1-m;
    int K=n*(n+1)/2;
    for(int i=1;i<=m;i++) dp[i][0][0]=MOD-1;
    for(int i=1;i<=n;i++){
        for(int k=m;k>=1;k--){
            for(int t=0;t<i;t++){
                int del=i-t-1; 
                del=(del+1)*del/2;
                for(int j=i*(i+1)/2;j>=del;j--){
                    Add(dp[k][j][i],sub(dp[k-1][j-del][t],dp[k][j-del][t]));
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n*(n+1)/2;i++){
        for(int j=0;j<=n;j++){
            int tmp=i+(n-j)*(n-j+1)/2;
            int rest=n*(n+1)/2-tmp;
            Add(ans,mul(qpow(rest,MOD-2),dp[m][i][j]));
        }
    }
    cout<<mul(ans,n*(n+1)/2)<<endl;
    return 0;
}