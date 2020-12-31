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
const int N=500005;
int n,H,R,D,w[N];
struct node{
    double x,y;
}a[N];
double sqr(double x){return x*x;}

int main()
{ 
    n=read(); H=read(); R=read(); D=read();
    for(int i=0;i<=H;i++) w[i]=read();
    for(int i=1;i<=n;i++){
        a[i].x=read(); a[i].y=read();
    }
    double ans=1e15,ansx,ansy,ansr; int ansh;
    if(H==0){
        solver1::main();
        return 0;
    }
    for(int h=0;h<=H;h++){
        if(h>D) continue;
        for(int x=0;x<=50;x++){
            for(int y=0;y<=50;y++){
                double r=R;
                for(int i=1;i<=n;i++){
                    double dis=sqrt(sqr(1.0*x-a[i].x)+sqr(1.0*y-a[i].y));
                    r=max(r,dis-sqrt(D*D-h*h));
                }
                if(ans>r*w[h]){
                    ans=r*w[h]; ansx=x;
                    ansy=y; ansh=h; ansr=r;
                }
            }
        }
    }
    printf("%.8lf\n",ans);
    printf("%.8lf %.8lf %d %.8lf\n",ansx,ansy,ansh,ansr);
    return 0;
}