#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
#define ran(l,r) rand()%((r)-(l)+1)+(l)
int a[500005],vis[500005];
void make_permutation(int n){
    for(int i=1;i<=n;i++) a[i]=i;
    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++){
       printf("%d ",a[i]);
    } puts("");
}
const int N=500005;
vector<int> v[N];
int sz[N],S=0;
void dfs(int u,int f){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        sz[u]+=sz[to];
    }
}
void make_tree(int n){
    for(int i=2;i<=n;i++){
        int fa=rand()%(i-1)+1;
        printf("%d %d\n",fa,i);
        v[fa].push_back(i);
    }
}
void make_seq(int n,int maxn){
    for(int i=1;i<=n;i++) printf("%d ",ran(1,maxn));
    puts("");
}
const int M=1005;
const int V=100;
int main()
{
    srand(time(NULL));
    int n=100000,m=100000,Q=100;
    ll now=n;
    cout<<n<<" "<<m<<" "<<Q<<endl;
    make_tree(n);
    dfs(1,-1); puts("");
    for(int i=1;i<=m;i++){
        int x=ran(1,n),y=ran(1,now);
        now+=sz[x];
        printf("%d %d\n",x,y);
    }    puts("");
    for(int i=1;i<=Q;i++){
        int x=ran(1,now),y=ran(1,now);
        while(x==y) y=ran(1,now);
        printf("%d %d\n",x,y);
    }
    return 0;
}