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
const int inv4=qpow(4,MOD-2);

int a[2001][2001],sum[2001][2001],n,A[N<<1],Base[N<<1],m;
void init(){
    a[1][1]=2; a[2][1]=4; a[2][2]=4;
    sum[2][1]=4; sum[2][2]=8;
    Base[0]=1;
    for(int i=1;i<=n*2;i++) Base[i]=mul(Base[i-1],2);
    for(int i=3;i<=n;i++){
        int rest=Base[i*2-1];
        for(int j=i;j>=3;j--){
            a[i][j]=mul(sub(rest,mul(4,sum[i-1][j-2])),inv2);
            Sub(rest,a[i][j]);
        }
        a[i][1]=a[i][2]=mul(rest,inv2);
        for(int j=1;j<=i;j++) sum[i][j]=add(sum[i][j-1],a[i][j]);
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=i;j++) printf("%d*%d ",Base[j],a[i][j]/Base[j]);
    //     puts("");
    // }
}

int _abs(int x){return x>0 ? x : -x;}

void solve(){
    while(scanf("%d",&A[++m])!=EOF); 
    m--;
    int now=n,cnt=0,win=0;
    for(int i=1;i<=m;i++){
        printf("%lld ",mul(a[now][_abs(win)+1],Base[cnt]));
        if(A[i]==0){
            if(win>0) cnt+=2,now--;
            win--;
        }
        else{
            if(win<0) cnt+=2,now--;
            win++;
        }
    }
}

int main()
{
    n=read();
    init();
    solve();
    return 0;
}