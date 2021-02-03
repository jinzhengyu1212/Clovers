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
typedef vector<int> vec;
typedef vector<vec> matrix;
const int N=1000005;
int dx[]={0,0,1,-1,0};
int dy[]={-1,1,0,0,0};
int n,m,Q,tot; pii pos[N];
matrix a;
int checkBlack(int x,int y){
    int ret=tot-1;
    if(x>=1) checkmin(ret,a[x-1][y]-1);
    if(y>=1) checkmin(ret,a[x][y-1]-1);
    return ret;
}
int checkWhite(int x,int y){
    int t[5],top=0;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<0||xx>=n||yy<0||yy>=m) continue;
        t[++top]=a[xx][yy];
    }   
    sort(t+1,t+top+1);
    int ret=tot;
    if(top>=2) checkmin(ret,t[2]);
    return ret;
}

struct Segment_Tree{
    int mi[N<<2],num[N<<2],tag[N<<2];
    void pushup(int x){
        mi[x]=min(mi[x<<1],mi[x<<1|1]); num[x]=0; 
        if(mi[x]==mi[x<<1]) num[x]+=num[x<<1];
        if(mi[x]==mi[x<<1|1]) num[x]+=num[x<<1|1];
    }
    void pushdown(int x){
        if(!tag[x]) return;
        mi[x<<1]+=tag[x]; tag[x<<1]+=tag[x];
        mi[x<<1|1]+=tag[x]; tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
    void build(int x,int l,int r){
        if(l==r){mi[x]=0; tag[x]=0; num[x]=1; return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void update(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            tag[x]+=val; mi[x]+=val;
            return;
        } 
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x);
    }
    int query(int x,int l,int r,int pos){
        if(l==r) return mi[x];
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos) return query(x<<1,l,mid,pos);
        else return query(x<<1|1,mid+1,r,pos);
    }
}tree;

void Contribute(int x,int y,int typ){
    int r=checkBlack(x,y);
    if(a[x][y]<=r) tree.update(1,0,tot-1,a[x][y],r,typ);
    int l=checkWhite(x,y);
    if(l<=a[x][y]-1) tree.update(1,0,tot-1,l,a[x][y]-1,typ);
}

void init(){
    n=read(); m=read(); Q=read();
    a.resize(n); tot=n*m;
    for(int i=0;i<n;i++) a[i].resize(m);
    for(int i=0;i<n*m;i++){
        pos[i].first=read(),pos[i].second=read();
        a[pos[i].first][pos[i].second]=i;
    }
    tree.build(1,0,tot-1);
}

void solve(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) Contribute(i,j,1);
    }
    while(Q--){
        int x=read(),y=read();
        vector<pii> tmp;
        for(int i=0;i<5;i++){
            int xx=pos[x].first+dx[i],yy=pos[x].second+dy[i];
            if(xx<0||xx>=n||yy<0||yy>=m) continue;
            tmp.push_back(mk(xx,yy));
        }
        for(int i=0;i<5;i++){
            int xx=pos[y].first+dx[i],yy=pos[y].second+dy[i];
            if(xx<0||xx>=n||yy<0||yy>=m) continue;
            tmp.push_back(mk(xx,yy));
        }
        sort(tmp.begin(),tmp.end()); 
        tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
        //删初始贡献的时候每个点只能删1次！所以要去重
        for(auto &u : tmp) Contribute(u.first,u.second,-1);
        swap(a[pos[x].first][pos[x].second],a[pos[y].first][pos[y].second]);
        swap(pos[x],pos[y]);
        for(auto &u : tmp) Contribute(u.first,u.second,1);
        printf("%d\n",tree.num[1]);
    }
}

int main()
{
    init(); solve();    
    return 0;
}