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
const int N=210005;

struct Trie{
    int son[N<<3][2],tot=1;
    #define ls son[x][0]
    #define rs son[x][1]
    int mi[N<<3],tag[N<<3],fa[N<<3];
    void init(){memset(mi,0x3f,sizeof(mi)); fa[1]=0;}
    void pushup(int x){mi[0]=inf; mi[x]=min(mi[ls],mi[rs]);}
    void pushall(int x){while(x) pushup(x),x=fa[x];}
    void pushdown(int x){
        if(!tag[x]) return;
        mi[ls]+=tag[x]; tag[ls]+=tag[x];
        mi[rs]+=tag[x]; tag[rs]+=tag[x];
        tag[x]=0;
    }
    void insert(char *c,int len,int val){
        int x=1;
        for(int i=len;i>=1;i--){
            pushdown(x);
            if(c[i]=='0'){
                if(!ls) ls=++tot;
                fa[ls]=x; x=ls;
            }
            else{
                if(!rs) rs=++tot;
                fa[rs]=x; x=rs;
            }
        }
        checkmin(mi[x],val);
        //cout<<x<<" "<<val<<" "<<mi[x]<<endl;
        pushall(fa[x]);
    }
    int query(char *c,int len){
        int x=1;
        for(int i=len;i>=1;i--){
            pushdown(x);
            if(c[i]=='0'){
                if(!ls) return inf;
                else x=ls;
            }
            else{
                if(!rs) return inf;
                else x=rs;
            }
        }
        return mi[x];
    }
}tree;

int n,len,dp[N],cal[N];
char s[N][25];
int f(int x,int y){
    for(int st=0;st<=len;st++){
        int bl=1;
        for(int i=1;i+st<=len;i++)
            if(s[x][st+i]!=s[y][i]) {bl=0; break;}
        if(bl) return st;
    }
}
 
void init(){
    scanf("%d%d",&n,&len);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<n;i++) cal[i]=f(i,i+1);
    cal[0]=len;
}

int emp=0;
void solve(){
    tree.init();
    for(int i=0;i<=n;i++) dp[i]=inf;
    dp[0]=cal[0]; emp=cal[0];
    for(int i=1;i<n;i++){
        //cout<<i<<endl;
        /*for(int j=0;j<=i-1;j++){
            dp[i]=min(dp[j]+f(j,i+1),dp[i]);
            dp[j]=dp[j]+cal[i];
        }*/
        int mi=inf;
        for(int le=0;le<=len;le++){
            checkmin(mi,tree.query(s[i+1],le)+len-le);
        }
        //cout<<"OK\n";
        checkmin(dp[i],emp+len);
        emp+=cal[i];
        checkmin(dp[i],mi);
        tree.mi[1]+=cal[i]; tree.tag[1]+=cal[i];
        tree.insert(s[i],len,dp[i]);
        //cout<<dp[i]<<endl;
    }
    cout<<min(emp,tree.mi[1])<<endl;
}
 
int main()
{
    init(); solve();
    return 0;
}