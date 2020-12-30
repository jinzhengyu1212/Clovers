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
const int N=200005;
int trans[N][26],link[N],maxlen[N],tot=1,lst;
struct SAM{
    void init(){
        for(int i=1;i<=tot;i++){
            link[i]=0; maxlen[i]=0; f[i]=0; vis[i]=0;
            for(int j=0;j<26;j++) trans[i][j]=0;
        }
        tot=1; lst=1;
    }
    void extend(int id){
        int cur=++tot,p;
        maxlen[cur]=maxlen[lst]+1;
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int y=++tot; maxlen[y]=maxlen[p]+1; f[tot]=1;
                copy(trans[q],trans[q]+26,trans[y]);
                link[y]=link[q]; link[q]=link[cur]=y;
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=y;
            }
        }
        lst=cur;
    }
}tree;
int T,n;
char s[N];

int main()
{
    T=read();
    while(T--){
        init(); solve();
    }
    return 0;
}