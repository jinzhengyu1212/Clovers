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
const int MOD=1e9+7;
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
const int N=100005;
int n,a[N];
int fac[N],ifac[N],in[N],Base[N],inv2[N];
int C(int n,int m){return mul(fac[n],mul(ifac[n-m],ifac[m]));}
int cir[N],tot=0,num[N],vis[N],foot[N],ans=1;
void work_tree(int P){
    int ed=0,now=0,flen,fpos,x=P;
    do{
        now++;
        if(foot[x]){
            if(!ed) ed=fpos=now,flen=foot[x];
            else{
                int tmp=(foot[x]<=now-ed)+(foot[x]<now-ed);
                if(!tmp){puts("0"); exit(0);}
                Mul(ans,tmp); ed=now;
            }
        }
        x=a[x];
    }while(x!=P);
    int tmp=(now-ed+fpos>=flen)+(now-ed+fpos>flen);
    if(!tmp){puts("0"); exit(0);}
    Mul(ans,tmp);
}

void solve(){
    memset(vis,0,sizeof(vis));
    queue<int> q;
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i),foot[i]=0;
    while(!q.empty()){
        int u=q.front(); q.pop();
        vis[u]=1;
        foot[a[u]]=foot[u]+1;
        if(!--in[a[u]]) q.push(a[u]); 
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        int cnt=0,x=i,sum=0;
        do{
            cnt++,vis[x]=1,sum+=foot[x],x=a[x];
        }while(x!=i);
        if(sum) work_tree(i);
        else num[cnt]++;
    }
    for(int i=1;i<=n;i++) if(num[i]){
        int sum=0;
        for(int j=0;j<=num[i]/2;j++){
            int tmp1=mul(C(num[i],j*2),C(2*j,j));
            Mul(tmp1,mul(fac[j],inv2[j]));
            Mul(tmp1,qpow(i,j));
            if(i&1&&i!=1) Mul(tmp1,Base[num[i]-2*j]);//!!!
            Add(sum,tmp1);
        }
        Mul(ans,sum);
    }
}

int main()
{
    n=read();
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    Base[0]=1; for(int i=1;i<=n;i++) Base[i]=mul(Base[i-1],2);
    inv2[0]=1; for(int i=1;i<=n;i++) inv2[i]=mul(inv2[i-1],(MOD+1)/2);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=1;i<=n;i++){
        a[i]=read();
        in[a[i]]++;
    }
    for(int i=1;i<=n;i++) if(!vis[i]){
        int x=i; while(!vis[x]) vis[x]=i,x=a[x];
        if(vis[x]!=i) continue;
        int tmp=x;
        while(!cir[x]) cir[x]=1,x=a[x];
        x=i; while(x!=tmp) cir[x]=0,x=a[x];
    }
    //for(int i=1;i<=n;i++) cout<<cir[i]<<" "; cout<<endl;
    for(int i=1;i<=n;i++) if(in[i]>=3||(in[i]==2&&!cir[i])){puts("0"); return 0;}
    solve();
    cout<<ans<<endl;
    return 0;
}
