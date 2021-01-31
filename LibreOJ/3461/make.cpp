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
void make_tree(int n){
    for(int i=2;i<=n;i++){
        int fa=rand()%(i-1)+1;
        printf("%d %d\n",fa,i);
    }
}
void make_seq(int n,int maxn){
    for(int i=1;i<=n;i++) printf("%d ",ran(1,maxn));
    puts("");
}
const int N=500005;
const int M=1005;
const int V=100;
int main()
{
    srand(time(NULL));
    int n=38,m=38,Q=1000;
    cout<<n<<" "<<m<<" "<<Q<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=ran(1,2);
            if(x==1) printf("A");
            else if(x==2) printf("B");
        } puts("");
    }
    while(Q--){
        int lx=ran(1,n),rx=ran(1,n),ly=ran(1,m),ry=ran(1,m);
        if(lx>rx) swap(lx,rx);
        if(ly>ry) swap(ly,ry);
        printf("%d %d %d %d\n",lx,ly,rx,ry);
    }
    return 0;
}