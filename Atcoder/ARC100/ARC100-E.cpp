#include<bits/stdc++.h>
using namespace std;
const int N=300005;
typedef pair<int,int> pii;
#define mk make_pair
int n,a[N],cnt=0,k;
struct Trie{
    int son[N][2],fa[N];
    pii mx[N];
    pii merge(pii X,pii Y){
        int A[5];
        A[1]=X.first; A[2]=X.second;
        A[3]=Y.first; A[4]=Y.second;
        sort(A+1,A+5);
        return mk(A[4],A[3]);
    }
    void pushup(int x){
        mx[0]=mk(0,0); 
        mx[x]=merge(mx[son[x][1]],mx[son[x][0]]);
    }
    void insert(int x,int val){
        int now=0;
        for(int i=17;i>=0;i--){
            if(x>>i&1){
                if(!son[now][1]) son[now][1]=++cnt,fa[cnt]=now;
                now=son[now][1];
            }
            else{
                if(!son[now][0]) son[now][0]=++cnt,fa[cnt]=now;
                now=son[now][0];
            }
        }
        mx[now]=mk(0,0);
        while(fa[now]!=0) pushup(fa[now]), now=fa[now];
    }
    pii query(int x){
        pii ret=mk(0,0); int now=0;
        for(int i=17;i>=0;i--){
            if(x>>i&1){
                ret=merge(ret,mx[son[now][0]]);
                now=son[now][1];
            }
            else{
                now=son[now][0];
            }
        }
        return ret;
    }
}tree;

int main(){
    scanf("%d",&n);
    for(int i=0;i<(1<<n);i++) scanf("%d",&a[i]);
    for(int i=0;i<(1<<n);i++){
        int ans=0;
        tree.insert(i,a[i]);
        if(!i) continue;
        pii ret=tree.query(i);
        ans=max(ans,ret.first+ret.second);
        ans=max(ans,a[i]+ret.first);
        tree.insert(i,a[i]);
        printf("%d\n",ans); 
    }
    return 0;
}