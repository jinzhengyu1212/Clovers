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
const int M=1005;
int n,Q; char s[N];
int getdir(char c){
    if(c=='R') return 0;
    else if(c=='L') return 1;
    else if(c=='D') return 2;
    else if(c=='U') return 3;
}
int dx[]={1,-1,0,0};
int dy[]={0,0,-1,1};

void solve(int x,int y){
    int nowx=x,nowy=y;
    for(int i=1;i<=n;i++){
        int dir=getdir(s[i]);
        int xx=nowx+dx[dir],yy=nowy+dy[dir];
        if(!xx&&!yy) continue;
        nowx=xx,nowy=yy;
    }
    printf("%d %d\n",nowx,nowy);
}

int main()
{
    n=read(); scanf("%s",s+1);
    Q=read();
    while(Q--){
        int x=read(),y=read();
        solve(x,y);
    }
    return 0;
}