#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200005;
int n,a[N],sum=0,b[N],val[N],t[N],m,vis[N],ans=0;
int cnt=0;
namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=m;i++) fa[i]=i;}
    int getfather(int x){
        if(x==fa[x]) return x;
        return fa[x]=getfather(fa[x]);
    }
    void unite(int x,int y){
        x=getfather(x),y=getfather(y);
        if(x==y) return;
        fa[x]=y; cnt--;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum^=a[i];
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) val[i]=a[i];
    val[n+1]=sum; a[n+1]=sum;
    sort(val+1,val+n+2);
    m=unique(val+1,val+n+2)-val-1;
    for(int i=1;i<=n+1;i++){
        int pos=lower_bound(val+1,val+m+1,a[i])-val;
        t[pos]++;
    }
    for(int i=1;i<=n;i++){
        int pos=lower_bound(val+1,val+m+1,b[i])-val;
        if(b[i]!=val[pos]||!t[pos]){
            puts("-1");
            exit(0);
        }
        t[pos]--; 
    }
    int pos;
    for(int i=1;i<=m;i++) if(t[i]) pos=i,t[i]=0;
    for(int i=1;i<=n+1;i++){
        int pos=lower_bound(val+1,val+m+1,a[i])-val;
        if(i==n+1||b[i]!=a[i]) t[pos]++;
    }
    if(t[pos]==1&&val[pos]==sum) ans++;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(val+1,val+m+1,a[i])-val;
        b[i]=lower_bound(val+1,val+m+1,b[i])-val;
    }
    DSU::init();
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]) continue;
        if(!vis[a[i]]) vis[a[i]]=1,cnt++;
        if(!vis[b[i]]) vis[b[i]]=1,cnt++;
        ans++; DSU::unite(a[i],b[i]);
    }
    if(ans==0) puts("0");
    else printf("%d\n",ans+cnt-1);
    return 0;
}