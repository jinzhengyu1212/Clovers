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
const int N=500005;
const int M=1005;

int n;
char AA[2],AB[2],BA[2],BB[2];

int f[N][2];
void init(){
    f[0][1]=1;
    for(int i=1;i<=n-3;i++){
        f[i][1]=add(f[i-1][1],f[i-1][0]);
        f[i][0]=f[i-1][1];
    }
}

int main()
{
    n=read();
    if(n<=3){
        puts("1");
        return 0;
    }
    init();
    scanf("%s%s%s%s",AA,AB,BA,BB);
    if(AB[0]=='B'){
        AA[0]='A'+('B'-BB[0]);
        BA[0]='A'+('B'-BA[0]);
    }
    if(AA[0]=='A'){
        puts("1");
        return 0;
    }
    if(BA[0]=='B'){
        printf("%d\n",qpow(2,n-3));
        return 0;
    }
    printf("%d\n",add(f[n-3][0],f[n-3][1]));
    return 0;
}