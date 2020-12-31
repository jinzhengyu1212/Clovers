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
const int M=1005;
#define int long long

double vx,vy,Sx; ll k;
map<pair<double,double>,int> mp;
pair<double,double> P[N*2];

void solve(int k){
    mp.clear();
    double x,y; int flag=0;
    x=0; y=Sx;
    if(vx<vy) swap(vx,vy),flag=1,x=100-Sx,y=100;
    int step=1;
    double dis=y-x,T=dis/(vx+vy);
    y-=vy*T,x=y;
    mp[mk(x,y)]=1; k--;
    P[step]=mk(x,y);
    int rep=-1;
    while(k){
        step++;
        double delta=2*x,Ty=(100-y)/vy;
        if(delta/(vx-vy)<Ty){
            T=delta/(vx-vy);
            y+=vy*T;
            x=y;
            if(mp.count(mk(x,y))){
                rep=mp[mk(x,y)];
                break;
            }
            mp[mk(x,y)]=step;
        }
        else{
            T=200.0/(vx+vy);
            x=T*vx-x; y=x;
            if(mp.count(mk(x,y))){
                rep=mp[mk(x,y)];
                break;
            }
            mp[mk(x,y)]=step;
        }
        P[step]=mk(x,y);
        k--;
    }
    if(!k){
        if(flag) printf("%.6lf\n",100.0-y);
        else printf("%.6lf\n",x);
    }
    else{
        ll rnd=step-rep;
        k%=rnd; if(k==0) k=rnd;
        ll now=rep+k-1;
        x=P[now].first,y=P[now].second;
        if(flag) printf("%.6lf\n",100.0-y);
        else printf("%.6lf\n",x);
    }
}

signed main()
{
    int T=read();
    while(T--){
        scanf("%lld%lf%lf%lf",&k,&vx,&vy,&Sx);
        solve(k);
    }
    return 0;
}