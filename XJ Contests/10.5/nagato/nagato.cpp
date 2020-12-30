#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
const int N=200005;
struct QU{
    int id,l,r,flag;
}Q[N];
int n,m,a[N];
bool check1(){for(int i=1;i<=n;i++) if(Q[i].flag==1&&Q[i].l!=Q[i].r) return 0; return 1;}
bool check2(){for(int i=1;i<=n;i++) if(Q[i].flag==2&&Q[i].l!=Q[i].r) return 0; return 1;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}

namespace solver1{
    void main(){
        for(int i=1;i<=m;i++){
            if(Q[i].flag==1){
                for(int j=Q[i].l;j<=Q[i].r;j++) a[j]=mul(a[j],a[j]);
            }
            else{
                int ans=0;
                for(int j=Q[i].l;j<=Q[i].r;j++) ans=add(ans,a[j]);
                printf("%d\n",ans);
            }
        }
    }
}

namespace solver2{
    int sum[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int flag){
        if(!flag){
            for(int i=x;i<=n;i+=lowbit(i)) sum[i]=add(sum[i],a[x]);
            return;
        }
        int ad=sub(mul(a[x],a[x]),a[x]);
        for(int i=x;i<=n;i+=lowbit(i)) sum[i]=add(sum[i],ad);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) ret=add(ret,sum[i]);
        return ret;
    }

    void main(){
        for(int i=1;i<=n;i++) update(i,0);
        for(int i=1;i<=m;i++){
            if(Q[i].flag==1){
                int pos=Q[i].l;
                update(pos,1);
                a[pos]=mul(a[pos],a[pos]);
            }
            else{
                int ret=sub(query(Q[i].r),query(Q[i].l-1));
                printf("%d\n",ret);
            }
        }
    }
}

namespace solver3{
    int tag[N<<2];
    void build(int x,int l,int r){
        tag[x]=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    }
    void pushdown(int x){
        if(tag[x]==1) return;
        tag[x<<1]=(1ll*tag[x<<1]*tag[x])%(MOD-1);
        tag[x<<1|1]=(1ll*tag[x<<1|1]*tag[x])%(MOD-1);
        tag[x]=1;
    }
    void update(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R){
            tag[x]=1ll*tag[x]*2%(MOD-1);
            return;
        }
        pushdown(x);
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R);
        if(mid<R) update(x<<1|1,mid+1,r,L,R);
    }
    int query(int x,int l,int r,int pos){
        if(l==r){
            return qpow(a[l],tag[x]);
        }
        int mid=(l+r)>>1;
        pushdown(x);
        if(mid>=pos) return query(x<<1,l,mid,pos);
        else return query(x<<1|1,mid+1,r,pos);
    }

    void main(){
        build(1,1,n);
        for(int i=1;i<=m;i++){
            if(Q[i].flag==1){
                update(1,1,n,Q[i].l,Q[i].r);
            }
            else{
                printf("%d\n",query(1,1,n,Q[i].l));
            }
        }
    }
}

void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&Q[i].flag,&Q[i].l,&Q[i].r),Q[i].id=i;
    // if(n<=5000&&m<=5000){
    //     solver1::main();
    //     return;
    // }
    if(check1()){
        solver2::main();
        return;
    }
    if(check2()){
        solver3::main();
        return ;
    }
}

int main(){
    solve();
    return 0;
}