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
int in[500005];
void make_tree(int n){
    for(int i=2;i<=n;i++){
        int fa=ran(1,i-1);
        while(in[fa]==2) fa=ran(1,i-1);
        printf("%d %d\n",fa,i); in[fa]++;
    }
}
void make_tree2(int n){
    for(int i=1;i<=n;i++){
        int ls=i*2,rs=i*2+1;
        if(ls<=n) printf("%d %d\n",i,ls);
        if(rs<=n) printf("%d %d\n",i,rs);       
    }   
}

void make_tree3(int n){
    puts("1 2"); puts("1 3");
    for(int i=2;i<=n;i+=2){
        int ls=i+2,rs=i+3;
        if(ls<=n) printf("%d %d\n",i,ls);
        if(rs<=n) printf("%d %d\n",i,rs);      
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
    int n=1000,x=0;
    cout<<n<<" "<<x<<endl;
    make_tree(n); 
    return 0;
}