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
const int N=20005;
int n,m,visa[N],visb[N],A,B,cnt[N];

void init(){
    n=read(); m=read(); 
    A=read();
    for(int i=1;i<=A;i++){
        int x=read();
        visa[x]=1;
    }
    B=read();
    for(int i=1;i<=B;i++){
        int x=read();
        visb[x]=1;
    }
    for(int i=1;i<=n;i++){
        int x=read();
        if(x<=m) cnt[x]++;
    }
}

int vala[N],valb[N];
void solve(){
    vala[1]=0; valb[1]=0;
    for(int i=2;i<=m;i++){
        if(visa[i]){
            for(int x=1;x<i;x++){
                int y=i-x;
                if(y<x) break;
                int tmp1=0,tmp2=0;
                if(visa[x]) tmp1=vala[x];
                else if(visb[x]) tmp1=-valb[x];
                if(visa[y]) tmp2=vala[y];
                else if(visb[y]) tmp2=-valb[y];
                checkmax(vala[i],tmp1+tmp2+1);
            }
        }
        else if(visb[i]){
            for(int x=1;x<i;x++){
                int y=i-x;
                if(y<x) break;
                int tmp1=0,tmp2=0;
                if(visb[x]) tmp1=valb[x];
                else if(visa[x]) tmp1=-vala[x];
                if(visb[y]) tmp2=valb[y];
                else if(visa[y]) tmp2=-vala[y];
                checkmax(valb[i],tmp1+tmp2+1);
            }
        }
    }
    ll suma=0,sumb=0;
    for(int i=1;i<=m;i++){
        if(visa[i]){
            suma+=1ll*max(0,vala[i])*cnt[i];
        }
        else if(visb[i]){
            sumb+=1ll*max(0,valb[i])*cnt[i];
        }
    }
    if(suma<=sumb) puts("Orange");
    else puts("Pomegranate");
}

int main()
{
    init(); solve();
    return 0;
}