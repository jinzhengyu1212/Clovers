#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define il inline
using namespace std;
il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}
inline void write(int x){
	if(x<0) {x=~(x-1); putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=120000;
const int maxw=100001;
int n,a[N],q,typ,W;
int ans=0;
int decode(int x,int mod){
    if(!typ) return x;
    return (x^ans)%mod+1;
}
int sum[N<<5],ls[N<<5],rs[N<<5],cnt;
struct Segment_Tree{
    void update(int x,int y,int l,int r,int pos){
        if(l==r) {sum[x]=sum[y]+1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos){
            if(!ls[x]) ls[x]=++cnt,rs[x]=rs[y];
            update(ls[x],ls[y],l,mid,pos);
        }
        else{
            if(!rs[x]) rs[x]=++cnt,ls[x]=ls[y];
            update(rs[x],rs[y],mid+1,r,pos);
        }
        sum[x]=sum[ls[x]]+sum[rs[x]];
    }
    void query(int x,int y,int l,int r,int w){
        if(sum[x]==sum[y]) return;
        if(w/l==w/r) {ans+=(sum[x]-sum[y])*(w/l); return;}
        int mid=(l+r)>>1, ret=0;
        query(ls[x],ls[y],l,mid,w);
        query(rs[x],rs[y],mid+1,r,w);
    }
}tree;

void init(){
    scanf("%d%d%d%d",&n,&q,&typ,&W); cnt=n;
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]>maxw){
            sum[i]=sum[i-1]; ls[i]=ls[i-1];
            rs[i]=rs[i-1];
            continue;
        }
        tree.update(i,i-1,1,maxw,a[i]);
    }
}

void solve(){
    int l,r,w; 
    while(q--){
        l=read(); r=read(); w=read();
        l=decode(l,n); r=decode(r,n); w=decode(w,W);
        if(l>r) swap(l,r);
        ans=0;
        tree.query(r,l-1,1,maxw,w);
        printf("%d\n",ans);
    }
}

int main(){
    init();
    solve();
    return 0;
}