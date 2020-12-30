#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define il inline
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
#define mk make_pair
const int N=452000;
const int M=150000;
const int inf=(int)1e9;
int n,a[N],t[N],val[N],q,R;

int mi[N<<2],num[N<<2],tag[N<<2];
struct Segment_Tree{
    pii merge(pii x,pii y){
        pii ret;
        if(x.first<y.first) ret.first=x.first,ret.second=x.second;
        else if(x.first>y.first) ret.first=y.first,ret.second=y.second;
        else ret.first=x.first,ret.second=y.second+x.second;
        return ret;
    }
    void pushdown(int x){
        tag[x<<1]+=tag[x]; mi[x<<1]+=tag[x];
        tag[x<<1|1]+=tag[x]; mi[x<<1|1]+=tag[x];
        tag[x]=0;
    }
    void pushup(int x){
        pii tmp=merge(mk(mi[x<<1],num[x<<1]),mk(mi[x<<1|1],num[x<<1|1]));
        mi[x]=tmp.first; num[x]=tmp.second;
    }
    void build(int x,int l,int r){
        if(l==r){
            mi[x]=val[l];
            num[x]=1;
            return;
        }
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void update(int x,int l,int r,int L,int R,int add){
        if(L<=l&&r<=R){
            tag[x]+=add;
            mi[x]+=add;
            return;
        }
        pushdown(x);
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R,add);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,add);
        pushup(x);
    }
    pii query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return mk(mi[x],num[x]);
        int mid=(l+r)>>1; pushdown(x);
        pii ret=mk(inf,0);
        if(mid>=L) ret=merge(ret,query(x<<1,l,mid,L,R));
        if(mid<R) ret=merge(ret,query(x<<1|1,mid+1,r,L,R));
        return ret;
    }
}tree;

void init(){
    n=read(); q=read();
    for(int i=1;i<=n;i++) a[i]=read(),t[a[i]+M]++;
    for(int i=M+1;i<=n+M;i++){
        for(int j=i;j>=i-t[i]+1;j--) val[j]++;
    }
    R=n+M+M;
    tree.build(1,1,R);
}

int nowpos=M+1;//nowpos~nowpos+n-1
void solve(){
    while(q--){
        int opt=read(),x=read();
        if(opt>=1){
            int pos=a[opt]+M-t[a[opt]+M]+1;
            if(a[opt]+M<=nowpos+n-1) tree.update(1,1,R,pos,pos,-1);
            t[a[opt]+M]--;
            a[opt]=x+nowpos-M-1;
            t[a[opt]+M]++;
            pos=a[opt]+M-t[a[opt]+M]+1;
            if(a[opt]+M<=nowpos+n-1) tree.update(1,1,R,pos,pos,1);
            pii ans=tree.query(1,1,R,nowpos,nowpos+n-1);
            if(ans.first!=0) puts("0");
            else printf("%d\n",ans.second);
        }
        else{
            if(x==1){
                if(t[nowpos+n-1]!=0)
                  tree.update(1,1,R,nowpos+n-t[nowpos+n-1],nowpos+n-1,-1);
            }
            nowpos-=x;
            if(x==-1){
                if(t[nowpos+n-1]!=0)
                  tree.update(1,1,R,nowpos+n-t[nowpos+n-1],nowpos+n-1,1);
            }
            pii ans=tree.query(1,1,R,nowpos,nowpos+n-1);
            if(ans.first!=0) puts("0");
            else printf("%d\n",ans.second);
        }
    }
}

int main(){
    init(); solve();
    return 0;
}