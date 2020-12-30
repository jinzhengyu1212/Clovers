/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9+5;
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
const int N=100005;
struct node{
    int opt,ti;
}a[N];
int n,val[N],m,fin,Len;
struct P{
    int val,mi,mx;
}K[N];
P merge(P L,P R){
    P ret;
    if(L.val==-inf) return R;
    if(R.val==-inf) return L;
    ret.val=L.val+R.val;
    ret.mi=max(L.mi+R.val,R.mi);
    ret.mx=min(L.mx+R.val,R.mx);
    if(ret.mi>ret.mx){
        if(R.val>0) ret.mi=ret.mx;
        else ret.mx=ret.mi;
    }
    return ret;
}
struct Segment_Tree{
    P a[N<<2];
    void build(int x,int l,int r){
        if(l==r){
            a[x].val=::a[l].opt; 
            a[x].mi=0; a[x].mx=Len; 
            if(a[x].val<0) a[x].mx=Len-1; else a[x].mi=1;
            return;
        }
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        a[x]=merge(a[x<<1],a[x<<1|1]);
    }
    void update(int x,int l,int r,int pos){
        if(l==r){a[x].val=-inf; a[x].mx=Len; a[x].mi=0; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) update(x<<1,l,mid,pos);
        else update(x<<1|1,mid+1,r,pos);
        a[x]=merge(a[x<<1],a[x<<1|1]);
    }
}tree;

pii A[N];
int main()
{
    n=read(); a[0].ti=-inf; Len=read(); fin=read();
    for(int i=1;i<=n;i++){
        char c[2]; scanf("%s",c);
        if(c[0]=='+') a[i].opt=1;
        else a[i].opt=-1;
        a[i].ti=read(); val[i]=a[i].ti-a[i-1].ti-1;
        A[i]=mk(a[i].ti-a[i-1].ti,i);
    }
    sort(val+1,val+n+1); m=unique(val+1,val+n+1)-val-1;
    sort(A+1,A+n+1);
    reverse(val+1,val+m+1); reverse(A+1,A+n+1);
    tree.build(1,1,n);
    for(int i=1,j=1;i<=m;i++){
        if(i==m){
            printf("%d %d\n",val[i],fin);
            return 0;
        }
        while(A[j].first>val[i]){
            tree.update(1,1,n,A[j].second);
            j++;
        }
        int aa=tree.a[1].val,bb=tree.a[1].mi,cc=tree.a[1].mx;
        int ans=-1;
        int R=Len+aa; checkmin(R,cc); checkmax(R,bb);
        int L=aa; checkmin(L,cc); checkmax(L,bb);
        if(L<=fin&&fin<=R){
            if(i==1){
                puts("infinity");
                return 0;
            }
            for(int pos=Len;pos>=0;pos--){
                int tmp=pos+aa; checkmax(tmp,bb); checkmin(tmp,cc);
                if(tmp==fin){
                    ans=pos;
                    break;
                }
            }
        }
        if(ans!=-1){printf("%d %d\n",val[i],ans); return 0;}
    }
    return 0;
}