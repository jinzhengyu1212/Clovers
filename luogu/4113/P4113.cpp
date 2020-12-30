#include<bits/stdc++.h>
using namespace std;
inline char gc(){
    static char now[1<<20],*S,*T;
    if(T==S){
        T=(S=now)+fread(now,1,1<<20,stdin);
        if(T==S) return EOF;
    }
    return *S++;
}
inline int read(){
    int x=0,f=1; char c=gc();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=gc();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=gc();
    }
    return x*f;
}
const int N=2000005;
int n,m,c,a[N],ans[N],pre[N],now[N];

struct BIT{
    int a[N];
    void update(int x,int add){
        for(int i=x;i<=n;i+=(i&(-i))) a[i]+=add;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=(i&(-i))) ret+=a[i];
        return ret; 
    }
}tree;

struct QUERY{
    int l,r,id;
    bool operator < (const QUERY &rhs) const{
        return r<rhs.r;
    }
}Q[N];

void init(){
    n=read(); c=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++){
        Q[i].l=read(); Q[i].r=read();
        Q[i].id=i;
    }
    sort(Q+1,Q+m+1);
    for(int i=1;i<=n;i++){
        pre[i]=now[a[i]];
        now[a[i]]=i;
    }
}

void solve(){
    for(int i=1,j=0;i<=m;i++){
        while(j<Q[i].r){
            j++; if(!pre[j]) continue;
            if(pre[pre[j]]) tree.update(pre[pre[j]],-1);
            tree.update(pre[j],1);
        }
        ans[Q[i].id]=tree.query(Q[i].r)-tree.query(Q[i].l-1);
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}

int main(){
    init();
    solve();
    return 0;
}