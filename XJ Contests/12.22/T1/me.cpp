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
const int N=1000001;
#define int long long
int p,ans=0;
int cnt[22],tot=0,a[22];
void init(){
    int tmp=p;   
    for(int i=2;i*i<=p;i++){
        if(tmp%i==0){
            a[++tot]=i;
            while(tmp%i==0) cnt[tot]++,tmp/=i;
        }
    }
    if(tmp!=1){
        a[++tot]=tmp,cnt[tot]=1;
    }
    //for(int i=1;i<=tot;i++) out(a[i]),outln(cnt[i]);
}

int mx[N];
int calc(int rest,int val){//rest+k*p>val*val
    if(rest>val*val) return 0;
    int delta=val*val-rest;
    return delta/p+1;    
}
vector<int> v[N];
void ready(){
    for(int d=1;d<=tot;d++){
        int now=a[d];
        for(int i=0;i<p;i++) v[i].clear();
        for(int i=0;i<p;i++) v[i*i%now].push_back(i);
        for(int i=0;i<p;i++){
            int rest=cnt[d],j=0,rnd=0;
            if(v[i%now].empty()){mx[i]=INF; continue;}
            while(rest){
                int k=calc(i,v[i%now][j]);
                int delta=i+k*p-v[i%now][j]*v[i%now][j];
                int tmp=0; 
                while(delta%now==0) tmp++,delta/=now;
                rest-=tmp;
                if(rest<=0){
                    checkmax(mx[i],calc(i,rnd*p+v[i%now][j]));
                    break;
                }
                j++; if(j==sz(v[i%now])) j=0,rnd++;
            }
        }   
    }
}

int solve(int n){
    int ret=0;
    //outln(mx[1]);
    for(int i=0;i<p;i++){
        if(mx[i]==INF) continue;
        int pos=mx[i]*p+i; if(n<pos) continue;
        int delta=n-pos;
        ret+=delta/p+1;
    }
    return ret;
}

signed main()
{
    int l,r;
    scanf("%lld%lld%lld",&l,&r,&p);
    if(p==1){cout<<r-l+1<<endl; return 0;}
    init(); ready();
    printf("%lld\n",solve(r)-solve(l-1));
    return 0;
}