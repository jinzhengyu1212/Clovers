/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200005;
int n,m,lim[N],a[N],b[N],Len,ans[N];
struct Person{
    int pos,dir;
}P[N];
struct node{
    int dis,id;
    bool operator < (const node &rhs) const{
        if(dis==rhs.dis) return id>rhs.id;
        else return dis>rhs.dis;
    }
};
struct Node{
    int dis,id,to;
    bool operator < (const Node &rhs) const{
        if(dis==rhs.dis) return id>rhs.id;
        else return dis>rhs.dis;
    }
};
int head1[N],head2[N],lst1[N],lst2[N],belong[N];
priority_queue<node> Q1[N],Q2[N];
priority_queue <Node> Q;

inline int dist(int i,int hole){
    if(P[i].dir==0) return (a[hole]-P[i].pos+Len)%Len;
    else return (P[i].pos-a[hole]+Len)%Len;
}
struct List{
    int pre[N],nxt[N];
    inline void build(){
        pre[1]=m; nxt[m]=1;
        for(int i=1;i<m;i++) pre[i+1]=i,nxt[i]=i+1;
    }
    inline void del(int x){
        pre[nxt[x]]=pre[x];
        nxt[pre[x]]=nxt[x];
    }
    inline void Del(int x,int to){
        int dir=P[x].dir;
        if(pre[x]==-1){
            if(dir==0){
                head1[to]=nxt[x];
                if(nxt[x]!=-1)
                    belong[nxt[x]]=to,Q.push({dist(nxt[x],to),nxt[x],to});
            }
            else if(dir==1){
                head2[to]=nxt[x];
                if(nxt[x]!=-1)
                    belong[nxt[x]]=to,Q.push({dist(nxt[x],to),nxt[x],to});
            }
        }
        if(nxt[x]==-1){
            if(dir==0) lst1[to]=pre[x];
            else lst2[to]=pre[x];
        }
        if(nxt[x]!=-1) pre[nxt[x]]=pre[x];
        if(pre[x]!=-1) nxt[pre[x]]=nxt[x];
    }
    inline void link(int x,int y){pre[y]=x; nxt[x]=y;}
}L,T;
inline void del_Q(int x){
    int r=L.pre[x],l=L.nxt[x];
    if(l==x) return;
    if(head1[x]!=-1){
        if(lst1[l]==-1){
            Q.push({dist(head1[x],l),head1[x],l});
            head1[l]=head1[x],lst1[l]=lst1[x];
        }
        else T.link(lst1[l],head1[x]),lst1[l]=lst1[x];
    }
    if(head2[x]!=-1){
        if(lst2[r]==-1){
            Q.push({dist(head2[x],r),head2[x],r});
            head2[r]=head2[x],lst2[r]=lst2[x];
        }
        else T.link(lst2[r],head2[x]),lst2[r]=lst2[x];
    }
    L.del(x);
}

inline void init(){
    n=read(); m=read(); Len=read();
    a[1]=0; for(int i=2;i<=m;i++) a[i]=read();
    for(int i=1;i<=m;i++) lim[i]=read();
    for(int i=1;i<=n;i++) P[i].dir=read(),P[i].pos=read();
    L.build();
    for(int i=1;i<=n;i++){
        if(P[i].dir==0){
            int to=lower_bound(a+1,a+m+1,P[i].pos)-a;
            if(to==m+1) to=1;
            Q1[to].push({dist(i,to),i});
        }
        else{
            int to=upper_bound(a+1,a+m+1,P[i].pos)-a-1;
            if(!to) to=1;
            Q2[to].push({dist(i,to),i});
        }
    }
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    for(int i=1;i<=n;i++) T.pre[i]=-1,T.nxt[i]=-1;
    for(int i=1;i<=m;i++){
        lst1[i]=-1,lst2[i]=-1;
        while(!Q1[i].empty()){
            int u=Q1[i].top().id;
            if(lst1[i]==-1) head1[i]=u,belong[u]=i;
            else T.link(lst1[i],u);
            lst1[i]=u;
            Q1[i].pop();
        }
        while(!Q2[i].empty()){
            int u=Q2[i].top().id;
            if(lst2[i]==-1) head2[i]=u,belong[u]=i;
            else T.link(lst2[i],u);
            lst2[i]=u;
            Q2[i].pop();
        }
    }
}

int vis[N];
inline void solve(){
    int resth=m,restp=n;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=m;i++){
        if(head1[i]!=-1) Q.push({dist(head1[i],belong[head1[i]]),head1[i],i});
        if(head2[i]!=-1) Q.push({dist(head2[i],belong[head2[i]]),head2[i],i});
    }
    while(resth&&restp){
        Node now=Q.top(); Q.pop();
        if(vis[now.to]) continue;
        ans[now.id]=now.to; T.Del(now.id,now.to);
        restp--; 
        if(!--lim[now.to]) resth--,del_Q(now.to),vis[now.to]=1;
    }
    ll ret=0;
    for(int i=1;i<=n;i++){
        ret^=(1ll*i*ans[i]);
    }
    cout<<ret<<endl;
}

int main()
{
    init(); solve();
    return 0;
}