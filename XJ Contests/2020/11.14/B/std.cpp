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
const int MOD=1e9+7;
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
const int M=1005;
const int inv2=qpow(2,MOD-2);
int n,A[N<<1];
double a[2001][2001],sum[2001][2001],Base[N<<1];
void init(){
    a[1][1]=2; a[2][1]=4; a[2][2]=4;
    sum[2][1]=4; sum[2][2]=8;
    Base[0]=1;
    for(int i=1;i<=n*2;i++) Base[i]=Base[i-1]*2;
    for(int i=3;i<=n;i++){
        double rest=Base[i*2-1];
        for(int j=i;j>=3;j--){
            a[i][j]=rest/2-sum[i-1][j-2];
            rest-=a[i][j];
        }
        a[i][1]=a[i][2]=rest/2.0;
        for(int j=1;j<=i;j++) sum[i][j]=sum[i][j-1]+a[i][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++) printf("%lf ",a[i][j]);
        puts("");
    }
}

int main()
{
    n=read();
    init();
    return 0;
}