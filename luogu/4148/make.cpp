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
    cout<<500000<<endl;
    int n=8000;
    while(n--){
        int opt=rand()%2+1;
        printf("%d ",opt);
        if(opt==1){
            printf("%d %d %d\n",ran(1,10),ran(1,10),ran(1,5));
        }
        else{
            int l1=ran(1,10),l2=ran(1,10);
            int r1=ran(l1,11),r2=ran(l2,11);
            printf("%d %d %d %d\n",l1,l2,r1,r2);
        }
    }
    cout<<3<<endl;
    return 0;
}