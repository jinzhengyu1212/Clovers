#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
#define ran(l,r) rand()%((r)-(l)+1)+(l)
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
int n,a[N],b[N],val[N];

int main()
{
    srand(time(NULL));
    n=ran(1,50);
    cout<<n<<" "<<1<<endl;
    for(int i=1;i<=n;i++){
        a[i]=ran(0,1); b[i]=ran(a[i],1);
        printf("%d %d ",a[i],b[i]);
    } puts("");
    for(int i=1;i<n;i++){
        printf("%d ",ran(1,100));
    }
    puts("");
    return 0;
}