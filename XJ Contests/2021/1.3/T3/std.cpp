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
#define ui unsigned int
const int N=750005;
const int M=500005*32;
int tot,n; 
ui a[N]; ll k,ans=0,kkk=0;
struct Trie{
    int ch[M][2],sz[M];
    void insert(int x,int y,ui val){
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            ch[x][d]=++tot; ch[x][d^1]=ch[y][d^1];
            x=ch[x][d]; y=ch[y][d]; sz[x]=sz[y]+1;
        }
    }
    ui query(int x,int k,ui val){
        ui ret=0;
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            if(k>sz[ch[x][d^1]]){
                k-=sz[ch[x][d^1]];
                x=ch[x][d];
            }
            else{
                ret|=(1ll<<i);
                x=ch[x][d^1];
            }
        }
        return ret;
    }
    ll find(int x,ui val,ui mid){
        ll ret=0;
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            if(mid>>i&1){
                x=ch[x][d^1];
            }
            else{
                ret+=sz[ch[x][d^1]];
                x=ch[x][d];
            }
        }
        return ret+sz[x];
    }
    ll calc(int x,ui val,ui mid){
        ll ret=0;
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            if(mid>>i&1){
                x=ch[x][d^1];
            }
            else{
                ret+=sz[ch[x][d^1]]*(1ll<<i);
                kkk+=sz[ch[x][d^1]];
                x=ch[x][d];
            }
        }
        return ret;
    }
}T;
namespace solver1{
    struct node{
        ui val; int id,rk;
        bool operator < (const node &rhs) const{
            return val<rhs.val;
        }
    };
    priority_queue<node> q;
    void main(){
        tot=n;
        for(int i=2;i<=n;i++) a[i]^=a[i-1];
        for(int i=1;i<=n;i++){
            T.insert(i,i-1,a[i-1]);
            ui val=T.query(i,1,a[i]);
            q.push({val,i,1});
        }
        while(k--){
            node now=q.top(); q.pop();
            ans+=now.val;
            if(now.rk==now.id) continue;
            ui val=T.query(now.id,now.rk+1,a[now.id]);
            q.push({val,now.id,now.rk+1});
        }
        cout<<ans<<endl;
    }
}

bool check(){for(int i=2;i<=n;i++) if(a[i]!=a[i-1]) return 0; return 1;}
namespace solver2{
    void main(){
        ll sum=0;
        for(int i=1;i<=n;i++) sum+=(i+1)/2;
        printf("%lld\n",min(sum,k)*a[1]);       
    }
}

namespace solver3{
    bool check(ui mid){
        ll sum=0;
        for(int i=1;i<=n;i++) sum+=T.find(i,a[i],mid);
        return sum>=k;
    }
    void main(){
        tot=n;
        for(int i=2;i<=n;i++) a[i]^=a[i-1];
        for(int i=1;i<=n;i++){
            T.insert(i,i-1,a[i-1]);
        }
        ll l=0,r=(1ll<<32)-1; ui mid,best;
        while(l<=r){
            mid=(l+r)>>1;
            if(check(mid)) l=mid+1,best=mid;
            else r=mid-1;
        }
        for(int i=1;i<=n;i++) ans+=T.calc(i,a[i],best);
        ans+=(k-kkk)*best;
        cout<<ans<<endl;
    }
}

int main()
{
    n=read(); scanf("%lld",&k);
    for(int i=1;i<=n;i++) scanf("%u",&a[i]);
    if(k<=200000){
        solver1::main();
        return 0;
    }
    if(check()){
        solver2::main();
        return 0;
    }
    if(n<=60000){
        solver3::main();
        return 0;
    }
    return 0;
}