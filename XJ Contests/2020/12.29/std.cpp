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
typedef vector<int> V;
set<V> st;
int n;
void dfs(V v,int k){
    if(!k){
        st.insert(v);
        return;
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            int mx=0;
            for(int t=i;t<=j;t++) checkmax(mx,v[t]);
            V tmp=v;
            for(int t=i;t<=j;t++) tmp[t]=mx;
            dfs(tmp,k-1);
        }
    }
}

int main()
{
    n=read(); int k=read();
    V v;
    for(int i=1;i<=n;i++){
        int x=read();
        v.push_back(x);
    }
    dfs(v,k);
    cout<<sz(st)<<endl;
    // for(auto &v : st){
    //     for(auto &to : v) cout<<to<<" "; cout<<endl;
    // }
    return 0;
}