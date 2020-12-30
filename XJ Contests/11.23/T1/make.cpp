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
    int n=800,m=800;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%d ",ran(1,10));
        }
        puts("");
    }
    int Q=500000; cout<<Q<<endl;
    for(int i=1;i<=Q;i++){
        int lenx=ran(1,n);
        int sx=ran(1,n-lenx+1),ex=sx+lenx-1;
        int leny=ran(1,m);
        while(leny>lenx*2||leny*2<lenx) leny=ran(1,m);
        int sy=ran(1,m-leny+1),ey=sy+leny-1;
        int opt=ran(1,3);
        if(opt==1) printf("SUM ");
        else if(opt==2) printf("MAX ");
        else printf("MIN ");
        printf("%d %d %d %d\n",sx-1,sy-1,ex-1,ey-1);
    }
    return 0;
}