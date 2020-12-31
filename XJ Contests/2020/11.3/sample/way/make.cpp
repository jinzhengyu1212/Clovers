#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
#define ran(l,r) 1ll*rand()*rand()%((r)-(l)+1)+(l)
int a[500005],vis[500005];
void make_permutation(int n){
    for(int i=1;i<=n;i++) a[i]=i;
    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++){
       printf("%lld ",a[i]);
    } puts("");
}
void make_tree(int n){
    for(int i=2;i<=n;i++){
        int fa=rand()%(i-1)+1;
        printf("%lld %lld\n",fa,i);
    }
}
void make_seq(int n,int maxn){
    for(int i=1;i<=n;i++) printf("%lld ",ran(1,maxn));
    puts("");
}
const int N=500005;
const int M=1005;
const int V=100;
signed main()
{
    srand(time(NULL));
    cout<<10<<endl;
    for(int myyakioi=1;myyakioi<=10;myyakioi++){
        int n=ran(10,20),q=30;
        cout<<n<<" "<<q<<endl;
        for(int i=1;i<=n;i++) printf("%lld ",ran(n-1,n+1));
        puts("");
        for(int i=1;i<=q;i++) printf("%lld ",ran(1,100));
        puts("");
    }
    return 0;
}