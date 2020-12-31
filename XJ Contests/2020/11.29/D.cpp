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
const int M=1001;
char str[M];
int a[M],b[M],c[M],cnta=0,cntb=0,cntc=0;
int bl[27][27],m,ans=0,vis[27];

void dfs(int pos,int flag){
    if(pos==cntc+1) {
        if(!flag){
            ans++; 
        }
        return;
    }
    if(vis[a[pos]]==-1){
        for(int i=0;i<10;i++){
            if(!bl[a[pos]][i]) continue;
            vis[a[pos]]=i; int tmpa=i;
            if(vis[b[pos]]==-1){
                for(int j=0;j<10;j++){
                    if(!bl[b[pos]][j]) continue;
                    int tmpb=j; vis[b[pos]]=j;
                    int kkk=(vis[c[pos]]==-1);         
                    if((tmpa+tmpb+flag)%10!=vis[c[pos]]&&vis[c[pos]]!=-1){
                        if(b[pos]!=a[pos]) vis[b[pos]]=-1;
                        continue;
                    }
                    if(!bl[c[pos]][(tmpa+tmpb+flag)%10]){
                        if(b[pos]!=a[pos]) vis[b[pos]]=-1;
                        continue;
                    }
                    if(vis[c[pos]]==-1) vis[c[pos]]=(tmpa+tmpb+flag)%10;
                    dfs(pos+1,tmpa+tmpb+flag>=10);
                    if(c[pos]!=b[pos]&&c[pos]!=a[pos]) 
                        if(kkk) vis[c[pos]]=-1;
                    if(b[pos]!=a[pos]) vis[b[pos]]=-1;
                }
            }     
            else{
                int tmpb=vis[b[pos]];
                int kkk=(vis[c[pos]]==-1); 
                if((tmpa+tmpb+flag)%10!=vis[c[pos]]&&vis[c[pos]]!=-1) continue;
                if(!bl[c[pos]][(tmpa+tmpb+flag)%10]) continue;
                if(vis[c[pos]]==-1) vis[c[pos]]=(tmpa+tmpb+flag)%10;
                dfs(pos+1,tmpa+tmpb+flag>=10);
                if(c[pos]!=a[pos]) 
                    if(kkk) vis[c[pos]]=-1;
            }  
        }
        vis[a[pos]]=-1;
    }
    else{
        if(vis[b[pos]]==-1){
            int tmpa=vis[a[pos]];
            for(int i=0;i<10;i++){
                if(!bl[b[pos]][i]) continue;
                int kkk=(vis[c[pos]]==-1); 
                int tmpb=i; vis[b[pos]]=i;
                if((tmpa+tmpb+flag)%10!=vis[c[pos]]&&vis[c[pos]]!=-1) continue;
                if(!bl[c[pos]][(tmpa+tmpb+flag)%10]) continue;
                if(vis[c[pos]]==-1) vis[c[pos]]=(tmpa+tmpb+flag)%10;
                dfs(pos+1,tmpa+tmpb+flag>=10);
                if(c[pos]!=b[pos]) 
                    if(kkk) vis[c[pos]]=-1;
            }
            vis[b[pos]]=-1;
        }
        else{
            int tmpa=vis[a[pos]],tmpb=vis[b[pos]];
            int kkk=(vis[c[pos]]==-1); 
            if((tmpa+tmpb+flag)%10!=vis[c[pos]]&&vis[c[pos]]!=-1) return;
            if(!bl[c[pos]][(tmpa+tmpb+flag)%10]) return;
            if(vis[c[pos]]==-1) vis[c[pos]]=(tmpa+tmpb+flag)%10;
            dfs(pos+1,tmpa+tmpb+flag>=10);
            if(kkk) vis[c[pos]]=-1;
        }
    }
}

void init(){
    scanf("%s",str+1);
    memset(vis,-1,sizeof(vis));
    for(int i=1;i<M;i++) a[i]=26,b[i]=26,c[i]=26; vis[26]=0;
    int now=1;
    for(int i=1;i<=strlen(str+1);i++){
        if(str[i]=='+') now=2;
        else if(str[i]=='=') now=3;
        else{
            if(now==1) a[++cnta]=str[i]-'A';
            else if(now==2) b[++cntb]=str[i]-'A';
            else c[++cntc]=str[i]-'A';
        }
    } 
    m=read();
    for(int i=0;i<26;i++)
        for(int j=0;j<10;j++) bl[i][j]=1;
    for(int i=1;i<=m;i++){
        scanf("%s",str); int V=read();
        bl[str[0]-'A'][V]=0;
    }
    reverse(a+1,a+cnta+1); reverse(b+1,b+cntb+1);
    reverse(c+1,c+cntc+1);
    bl[a[cnta]][0]=0; bl[b[cntb]][0]=0; bl[c[cntc]][0]=0;
}

int main()
{
    init();
    // out(vis[a[2]]); outln(vis[b[2]]); outln(vis[c[2]]);
    // outln(bl[c[2]][0]);
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}