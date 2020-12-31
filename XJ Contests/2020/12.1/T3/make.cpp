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
    int n=ran(1,100000);
    int m=ran(1,20);
    for(int i=1;i<=n;i++){
        int c=ran(0,25);
        printf("%c",'a'+c);
    }
    puts("");
    for(int i=1;i<=m;i++){
        int c=ran(0,25);
        printf("%c",'a'+c);
    }
    puts("");
    int Q=ran(1,100000);
    cout<<Q<<endl;
    while(Q--){
        int l=ran(1,n),r=ran(1,n);
        if(l>r) swap(l,r);
        printf("%d %d\n",l,r);
    }
    return 0;
}