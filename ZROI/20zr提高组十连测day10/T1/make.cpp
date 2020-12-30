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
int a[N],b[N],c[N],d[N];
int main()
{
    srand(time(NULL));
    int n=20000,m=2000;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<n;i++) a[i]=ran(1,3);
    for(int i=1;i<=m;i++) b[i]=ran(1,3);
    for(int i=1;i<=n;i++) c[i]=ran(1,3);
    for(int i=1;i<m;i++) d[i]=ran(1,3);
    sort(a+1,a+n); sort(b+1,b+m+1);
    sort(c+1,c+n+1); sort(d+1,d+m);
    for(int i=1;i<n;i++) printf("%d ",a[i]); puts("");
    for(int i=1;i<=m;i++) printf("%d ",b[i]); puts("");
    for(int i=1;i<=n;i++) printf("%d ",c[i]); puts("");
    for(int i=1;i<m;i++) printf("%d ",d[i]); puts("");
    return 0;
}