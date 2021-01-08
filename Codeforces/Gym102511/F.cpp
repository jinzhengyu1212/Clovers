/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9+1;
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
vector<int> v[N];
int nowx,n,LL,RR;
struct Line{
    int lx,ly,rx,ry,id,dir;
    double P(int pos){
        double k=1.0*(ly-ry)/(lx-rx);
        return ly+k*(pos-lx);
    }
}a[N],b[N]; 
bool operator < (Line A,Line B){
    if(A.id==B.id) return 0;
    return A.P(nowx)<B.P(nowx);
}
set<Line> st;
struct Point{
    int x,id,typ;
    bool operator < (const Point &rhs) const{
        return x<rhs.x;
    }
}P[N<<1];
typedef set<Line>::iterator stL;
set<int> E[N];
void topo(){
    int top=0;
    static int deg[N]; queue<int> q;
    for(int i=1;i<=n;i++){
        for(auto &to : E[i]) deg[to]++;
    }    
    for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front(); q.pop();
        b[++top]=a[u];
        for(auto &to : E[u]) if(!--deg[to]) q.push(to);
    }
    for(int i=1;i<=n;i++) a[i]=b[i];
}
void init(){
    LL=read(); RR=read(); n=read();
    for(int i=1;i<=n;i++){
        a[i].lx=read(); a[i].ly=read();
        a[i].rx=read(); a[i].ry=read(); a[i].id=i;
        if(a[i].lx>a[i].rx){
            swap(a[i].lx,a[i].rx),swap(a[i].ly,a[i].ry);
            a[i].dir=2;
        }
        else a[i].dir=1;
    }
    for(int i=1;i<=n;i++){
        P[i*2-1]={a[i].lx,i,1};
        P[i*2]={a[i].rx,i,0};
    }
    sort(P+1,P+n+n+1);
    for(int i=1;i<=n+n;i++){
        nowx=P[i].x;
        if(P[i].typ==0) st.erase(a[P[i].id]);
        else{
            stL it=st.lower_bound(a[P[i].id]);
            if(it!=st.begin()&&!st.empty()){
                stL it2=it; it2--;
                E[it->id].erase(it2->id);
                E[P[i].id].insert(it2->id);
            }
            if(it!=st.end()) E[it->id].insert(P[i].id);
            st.insert(a[P[i].id]);
        }
    }
    topo();
    // for(int i=1;i<=n;i++){
    //     cout<<a[i].lx<<" "<<a[i].ly<<" "<<a[i].rx<<" "<<a[i].ry<<endl;
    // }
}

set<int> Pos,Neg;
int dp[N<<1],val[N<<1],m=0;
typedef set<int>::iterator sti;
void print(){
    static int ret[N];
    for(int i=1;i<=m;i++) ret[i]=ret[i-1]+dp[i];
    for(int i=1;i<=m;i++) cout<<ret[i]<<" "; cout<<endl;
}
void solve(){
    for(int i=1;i<=n;i++) val[++m]=a[i].lx,val[++m]=a[i].rx;
    val[++m]=LL; val[++m]=RR;
    sort(val+1,val+m+1); m=unique(val+1,val+m+1)-val-1;
    for(int i=1;i<=n;i++){
        a[i].lx=lower_bound(val+1,val+m+1,a[i].lx)-val;
        a[i].rx=lower_bound(val+1,val+m+1,a[i].rx)-val;
    }
    LL=lower_bound(val+1,val+m+1,LL)-val;
    RR=lower_bound(val+1,val+m+1,RR)-val;
    if(LL!=1){
        dp[1]=inf; dp[LL]=-inf;
        Pos.insert(1); Neg.insert(LL);
    }
    if(RR!=m){
        dp[RR+1]=inf; Pos.insert(RR+1);
    }
    for(int rnd=1;rnd<=n;rnd++){
        int l=a[rnd].lx,r=a[rnd].rx;
        if(a[rnd].dir==2){
            sti i=Pos.lower_bound(l+1);
            while(i!=Pos.end()&&*i<=r){
                sti j=i; j++;
                sti k=Neg.lower_bound(*i+1);
                int pos=r+1;
                if(j!=Pos.end()&&pos>*j) pos=*j;
                if(k!=Neg.end()&&pos>*k) pos=*k;
                dp[pos]+=dp[*i]; int tmp=dp[*i]; 
                dp[*i]=0; Pos.erase(i); 
                if(dp[pos]-tmp<0&&dp[pos]>=0) Neg.erase(pos);
                if(dp[pos]-tmp<=0&&dp[pos]>0) Pos.insert(pos);
                i=Pos.lower_bound(l+1);
            }
            if(l+1<=r-1){
                dp[l+1]++; 
                if(dp[l+1]==0) Neg.erase(l+1); if(dp[l+1]==1) Pos.insert(l+1);
                dp[r]--;
                if(dp[r]==0) Pos.erase(r); if(dp[r]==-1) Neg.insert(r);
            }
        }
        else{
            sti i=Neg.upper_bound(r);
            while(i!=Neg.begin()&&*(--i)>=l+1){
                sti j=i;
                sti k=Pos.lower_bound(*i+1);
                int pos=l;
                if(j!=Neg.begin()&&*(--j)>pos) pos=*j;
                if(k!=Pos.begin()&&*(--k)>pos) pos=*k;
                dp[pos]+=dp[*i]; int tmp=dp[*i]; 
                dp[*i]=0; Neg.erase(i); 
                if(dp[pos]-tmp>0&&dp[pos]<=0) Pos.erase(pos);
                if(dp[pos]-tmp>=0&&dp[pos]<0) Neg.insert(pos);
                i=Neg.upper_bound(r);
            }
            if(l+1<=r-1){
                dp[l+1]++; 
                if(dp[l+1]==0) Neg.erase(l+1); if(dp[l+1]==1) Pos.insert(l+1);
                dp[r]--;
                if(dp[r]==0) Pos.erase(r); if(dp[r]==-1) Neg.insert(r);
            }
        }
    }
    for(int i=1;i<=m;i++) dp[i]+=dp[i-1];
    int mi=inf;
    for(int i=LL;i<=RR;i++) checkmin(mi,dp[i]);
    cout<<mi<<endl;
}

int main()
{
    init(); solve();
    return 0;
}//