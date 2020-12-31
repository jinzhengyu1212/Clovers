#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
const int inv2=499122177;
inline int read(){
    int x=0; char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x%MOD :x;}
int sub(int x,int y){x-=y; return x<0 ? (x%MOD+MOD) : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int first[N],nxt[N<<1],point[N<<1],w[N<<1],e=0,deg[N];
void add_edge(int x,int y,int z){
    e++; w[e]=z%MOD;
    nxt[e]=first[x]; first[x]=e;
    point[e]=y;
}
struct Edge{
    int from,to,cost;
}E[N];

int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}

int n,m,ANS=0;
void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y,z; x=read(); y=read(); z=read();
        add_edge(x,y,z); add_edge(y,x,z);
        E[i].from=x; E[i].to=y; E[i].cost=z;
        deg[x]++; deg[y]++;
        ANS=add(ANS,z);
    }
}
bool check(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(deg[i]>2) return 0;
        if(deg[i]==1) cnt++;
    }
    return cnt==2;
}

int ans=0,sum=0,Base[N];
long long dp[2050];

void solve(){
    if(check()){
        cout<<ANS<<endl;
        return;
    }
    int fulln=(1<<n)-1; int fullm=(1<<m)-1;
    for(int mask=1;mask<=fulln;mask++){
        int flag=0;
        for(int mask1=1;mask1<=fullm;mask1++){
            for(int i=1;i<=n;i++) deg[i]=0;
            long long tmp=0;
            for(int i=1;i<=m;i++){
                if(mask1>>(i-1)&1){
                    deg[E[i].from]++;
                    deg[E[i].to]++;
                    tmp=tmp+E[i].cost;
                }
            }
            if(!check()) continue;
            int bl=0;
            for(int i=1;i<=n;i++){
                if(mask>>(i-1)&1){
                    if(deg[i]==0) bl=1; 
                } 
            }
            if(bl) continue;
            flag=1; dp[mask]=max(dp[mask],tmp);
        }
        sum+=flag;
        ans=add(ans,dp[mask]%MOD);
    }
    printf("%d\n",mul(ans,qpow(sum,MOD-2)));
}   

int main(){
    Base[0]=1; 
    for(int i=1;i<N;i++) Base[i]=mul(Base[i-1],2);
    init();
    solve();
    return 0;
}