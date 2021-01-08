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
const int N=300005;
set<pii> st;
int n,m; pii P[N],B[N];
struct Line{
    int y,id,typ;
    bool operator < (const Line &rhs) const{
        if(y==rhs.y) return typ>rhs.typ;
        return y>rhs.y;
    }
}L[N<<1];//0:B 1:P
namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=m;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){//x->y
        x=getfather(x); y=getfather(y);
        fa[x]=y;
    }
}

typedef set<pii>::iterator sti;
int ans[N],fa[N];
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        B[i].first=read(),B[i].second=read();
        L[i]={B[i].second,i,0};  
    }
    m=read();
    for(int i=1;i<=m;i++){
        P[i].first=read(),P[i].second=read();
        L[n+i]={P[i].second,i,1};
    }
    sort(L+1,L+n+m+1);
    st.clear();
    for(int i=1;i<=n+m;i++){
        if(L[i].typ==0){
            int x=B[L[i].id].first;
            sti it=st.lower_bound(mk(x,-inf));
            if(it!=st.end()) ans[it->second]++;
        }
        else{
            int x=P[L[i].id].first;
            sti it=st.lower_bound(mk(x,-inf));
            vector<int> tmp; tmp.clear();
            if(it!=st.end()) fa[L[i].id]=it->second;
            if(it!=st.begin()) do{
                it--;
                if(it->second<L[i].id) break;
                else tmp.push_back(it->second);
            }while(it!=st.begin());
            for(auto &u : tmp){
                st.erase(st.lower_bound(mk(P[u].first,-inf)));
            }
            st.insert(mk(x,L[i].id));
        }
    }
    DSU::init();
    for(int i=m;i>=1;i--){
        assert(i==DSU::getfather(i));
        int F=DSU::getfather(fa[i]);
        if(!F||F>i) continue;
        ans[F]+=ans[i];
        DSU::unite(i,F);
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}