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
const int N=300005;
int n,Q,a[N];
int tag[N];
int dep[N*25],ls[N*25],rs[N*25],cnt[N*25],tim[N*25];

int tot=0;
vector<int> ans;
struct Trie{
    void pushdown(int x){
        if((tag[dep[x]]-tim[x])%2==1) swap(ls[x],rs[x]);
        tim[x]=tag[dep[x]];
    }
    void insert(int val){
        int now=0;
        for(int i=0;i<30;i++){
            int bl=(val>>i&1);
            pushdown(now);
            if(!bl){
                if(!ls[now]) ls[now]=++tot,dep[tot]=i+1;
                now=ls[now];
            }
            else{
                if(!rs[now]) rs[now]=++tot,dep[tot]=i+1;
                now=rs[now];
            }
        }
        cnt[now]++;
    }
    void del(int val){
        int now=0;
        for(int i=0;i<30;i++){
            int bl=(val>>i&1);
            pushdown(now);
            if(!bl) now=ls[now];
            else now=rs[now];
        }
        cnt[now]--;
    }
    void add(){
        pushdown(0); swap(ls[0],rs[0]);
        int now=ls[0];
        while(now){
            pushdown(now);
            swap(rs[now],ls[now]);
            now=ls[now];
        }
    }
    void Xor(int val){
        for(int i=0;(1<<i)<=val;i++) 
            if(val>>i&1) tag[i]++;
    }
    void print(int x,int val,int Dep){
        for(int i=1;i<=cnt[x];i++) ans.push_back(val);
        pushdown(x);
        if(ls[x]) print(ls[x],val,Dep+1);
        if(rs[x]) print(rs[x],val+(1<<Dep),Dep+1);
    }
}tree;

int main()
{
    n=read(); Q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        tree.insert(a[i]);
    }
    while(Q--){
        int opt=read(),x;
        if(opt!=3) x=read();
        if(opt==1) tree.insert(x);
        else if(opt==2) tree.del(x);
        else if(opt==3) tree.add();
        else if(opt==4) tree.Xor(x);
    }
    tree.print(0,0,0);
    sort(ans.begin(),ans.end());
    for(auto &to : ans) printf("%d ",to);
    cout<<endl;
    return 0;
}