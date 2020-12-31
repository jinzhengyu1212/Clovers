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
    int n=50000,m=50000,Q=100000;
    cout<<0<<endl;
    cout<<n<<" "<<m<<" "<<Q<<endl;
    for(int i=1;i<=Q;i++){
        int opt=ran(1,3);
        if(opt==1){
            printf("I ");
            int l=ran(1,n),r=ran(1,n),y=ran(1,n),p=ran(1,(int)1e6),q=ran(1,(int)1e6);
            while(vis[y]) y=ran(1,n);
            vis[y]=1;
            if(l>r) swap(l,r);
            printf("%d %d %d %d %d\n",l,r,y,p,q);
        }
        else if(opt==2){
            printf("D ");
            int y=ran(1,n);
            printf("%d\n",y);
        }
        else{
            printf("Q ");
            int x=ran(1,n),l=ran(1,n),r=ran(1,n);
            if(l>r) swap(l,r);
            printf("%d %d %d\n",x,l,r);
        }
    }
    return 0;
}