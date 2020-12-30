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
const int M=205;
int n,m,q,s[N],lst[N],beg[N];
int Q[N][M];
struct QUERY{
    int pos,id;
    bool operator < (const QUERY &rhs) const{
        return pos<rhs.pos;
    }
}le[N],ri[N];

void init(){
    n=read(); m=read(); q=read();
    for(int i=1;i<=n;i++) s[i]=read();
    for(int i=1;i<=q;i++){
        int b=read(); beg[i]=read(),lst[i]=read();
        le[i].pos=b-1; ri[i].pos=b+1;
        le[i].id=i; ri[i].id=i;
    }
    sort(le+1,le+q+1); sort(ri+1,ri+q+1);
    reverse(ri+1,ri+q+1);
    memset(Q,0,sizeof(Q));
    for(int i=1;i<=q;i++){
        Q[i][beg[i]]=1; Q[i][m+1]=1;
    }
}

int a[M][M],sum[M],ans[N],ad[N];
void multi1(int id){
    for(int i=1;i<=m;i++) 
        Q[id][i]=add(add(ad[i],a[beg[id]][i]),add(ad[i],a[m+1][i]));
}
void multi2(int id){
    ans[id]=0;
    for(int i=1;i<=m+1;i++) Add(ans[id],mul(Q[id][i],a[i][lst[id]]));
}
void print(int flag){
    for(int i=1;i<=m+1;i++){
        for(int j=1;j<=m+1;j++) printf("%d ",add(a[i][j],ad[j]*flag));
        puts("");
    }
}
void process_left(){
    memset(a,0,sizeof(a));
    for(int i=1;i<=m+1;i++) a[i][i]=1,sum[i]=1;
    int now=1;
    while(!le[now].pos&&now<=q){
        int id=le[now].id;
        ans[id]=Q[id][lst[id]];
        now++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+1;j++){
            int tmp=sum[j];
            Sub(sum[j],a[j][s[i]]);
            a[j][s[i]]=tmp;
            Add(sum[j],a[j][s[i]]);
        }
        while(le[now].pos==i&&now<=q){
            multi2(le[now].id);
            now++;
        }
    }
}


void process_right(){
    memset(a,0,sizeof(a));
    int now=1;
    for(int i=1;i<=m+1;i++) a[i][i]=1,ad[i]=0;
    while(ri[now].pos==n+1&&now<=q) now++;
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m+1;j++){
            int tmp=add(ad[j],a[s[i]][j]);
            Add(ad[j],tmp);
            Sub(a[s[i]][j],tmp);
        }
        //print(1);
        //cout<<endl;
        while(ri[now].pos==i&&now<=q){
            multi1(ri[now].id);
            now++;
        }
    }
    // cout<<"now=";
    // for(int i=1;i<=m+1;i++) cout<<Q[1][i]<<" "; cout<<endl;
}

void solve(){
    process_right();
    process_left();
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}

int main()
{
    init(); solve();
    return 0;
}