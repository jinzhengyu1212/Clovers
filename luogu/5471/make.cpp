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
    int n=70000,m=150000;
    cout<<n<<" "<<m<<" "<<0<<" "<<0<<endl;
    for(int i=1;i<=n;i++){
        int x=ran(1,n),y=ran(1,n);
        printf("%d %d\n",x,y);
    }
    for(int i=1;i<=m;i++){
        int p=ran(1,n),t=ran(1,10000);
        int L=ran(1,n-1),D=ran(1,n-1);
        int R=ran(L,n),U=ran(D,n);
        printf("%d %d %d %d %d %d\n",p,t,L,R,D,U);
    }
    return 0;
}