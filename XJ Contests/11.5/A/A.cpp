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
const int N=500005;
const int M=1005;
struct Complex {
	int x,y;
	Complex(int xx=0,int yy=0){x=xx,y=yy;}
	Complex operator + (const Complex &rhs) const
	{
		return Complex(x+rhs.x,y+rhs.y);
	}
	Complex operator - (const Complex &rhs) const 
	{
		return Complex(x-rhs.x,y-rhs.y);
	}
	Complex operator * (const Complex &rhs) const
	{
		return Complex(x*rhs.x-y*rhs.y,x*rhs.y+y*rhs.x);
	}
};

Complex qpow(Complex x,int y){
    Complex ret(1,0);
    while(y){
        if(y&1) ret=ret*x;
        x=x*x;
        y>>=1;
    }
    return ret;
}
int B=1500;
bool vis[3001][3001];

void dfs(int num,Complex x,int ch){
    if(num>20) return;
    if(!vis[x.x+B][x.y+B]&&ch%2==0) vis[x.x+B][x.y+B]=1;
    dfs(num+1,x+qpow(Complex(-1,1),num),ch+1);
    dfs(num+1,x,ch);    
}

int main()
{
    dfs(0,Complex(0,0),0);
    int T=read();
    while(T--){
        int l1=read(),r1=read(),l2=read(),r2=read();
        int ans=0;
        for(int i=l1;i<=r1;i++){
            for(int j=l2;j<=r2;j++){
                if(vis[i+B][j+B]) ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}