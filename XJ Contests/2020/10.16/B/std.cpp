#include<bits/stdc++.h>
using namespace std;
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
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
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
        pushup(x);
    }
    int query(int x,int y,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x]-sum[y];
        int mid=(l+r)>>1, ret=0;
        if(mid>=L) ret+=query(ls[x],ls[y],l,mid,L,R);
        if(mid<R) ret+=query(rs[x],rs[y],mid+1,r,L,R);
        return ret;
    }
}tree;

void init(){
    scanf("%d%d%d%d",&n,&q,&typ,&W); cnt=n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]),a[i]=min(a[i],maxw);
        tree.update(i,i-1,1,maxw,a[i]);
    }
}

void solve(){
    while(q--){
        int l,r,w; scanf("%d%d%d",&l,&r,&w);
        l=decode(l,n); r=decode(r,n); w=decode(w,W);
        if(l>r) swap(l,r);
        ans=0;
        for(int i=l;i<=r;i++) ans+=w/a[i];
        printf("%d\n",ans);
    }
}

int main(){
    init();
    solve();
    return 0;
}