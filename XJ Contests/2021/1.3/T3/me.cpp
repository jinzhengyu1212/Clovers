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
const int M=500001*33+5;
int tot,n; 
ui a[N]; ll k,ans=0,kkk=0;
struct Trie{
    int ch[M][2],sz[M];
    int cnt[60000*33+5][32],vis[60000*33+5];
    void insert(int x,int y,ui val){
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            ch[x][d]=++tot; ch[x][d^1]=ch[y][d^1];
            x=ch[x][d]; y=ch[y][d]; sz[x]=sz[y]+1;
        }
        if(n<=60000){
            for(int i=31;i>=0;i--){
                if(val>>i&1) cnt[x][i]=sz[x];
            }
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
    void dfs(int x,int bit){
        vis[x]=1; 
        int ls=ch[x][0],rs=ch[x][1];
        if(ls&&!vis[ls]) dfs(ls,bit-1);
        if(rs&&!vis[rs]) dfs(rs,bit-1);
        for(int i=0;i<32;i++) cnt[x][i]+=cnt[ls][i]+cnt[rs][i];
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
    ll SUM(int x,ui val,int bit){
        if(!x) return 0;
        ll ret=0;
        for(int i=0;i<32;i++){
            if(val>>i&1){
                ret+=1ll*(sz[x]-cnt[x][i])*(1ll<<i);
            }
            else ret+=1ll*cnt[x][i]*(1ll<<i);
        }
        return ret;
    }
    ll calc(int x,ui val,ui mid){
        ll ret=0;
        for(int i=31;i>=0;i--){
            int d=val>>i&1;
            if(mid>>i&1){
                x=ch[x][d^1];
            }
            else{
                ret+=SUM(ch[x][d^1],val,i);
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
    void write(__int128_t x){
        int b[101],top=0;
        while(x){
            b[++top]=x%10;
            x/=10;
        }
        for(int i=top;i>=1;i--) printf("%d",b[i]);
        puts("");
    }
    void main(){
        ll sum=0;
        for(int i=1;i<=n;i++) sum+=(i+1)/2;
        write((__int128_t)min(sum,k)*a[1]);       
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
        for(int i=1;i<=n;i++){
            T.dfs(i,32);
        }
        for(int i=1;i<=n;i++){
            ans+=T.calc(i,a[i],best);
        }
        ans+=(k-kkk)*best;
        cout<<ans<<endl;
    }
}

int main()
{
    n=read(); scanf("%lld",&k);
    for(int i=1;i<=n;i++) scanf("%u",&a[i]);
    if(n<=60000){
        solver3::main();
        return 0;
    }
    if(check()){
        solver2::main();
        return 0;
    }
    if(k<=200000){
        solver1::main();
        return 0;
    }
    return 0;
}