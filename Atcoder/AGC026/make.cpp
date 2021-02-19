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
char ans[N];
int main()
{
    srand(time(NULL));
    int n=1000; cout<<n<<endl;
    for(int i=1;i<=n*2;i++) a[i]=i;
    random_shuffle(a+1,a+n+n+1);
    for(int i=1;i<=n;i++) ans[a[i]]='a';
    for(int i=n+1;i<=n+n;i++) ans[a[i]]='b';
    for(int i=1;i<=n+n;i++) printf("%c",ans[i]); puts("");
    return 0;
}