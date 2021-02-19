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
char s[N];
int main()
{
    srand(time(NULL));
    int n=2,m=10,len=(ran(5,500))*2+1;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++) printf("%d ",ran(1,200));
        puts("");
    }
    for(int i=1;i<=len/2;i++) a[i]=i;
    random_shuffle(a+1,a+len/2+1);
    for(int i=1;i<=len;i++){
        if(i&1) s[i]='0'+ran(0,9);
        else{
            int x=ran(1,2);
            if(x==1) s[i]='<'; else s[i]='>';
        }
    }
    for(int i=1;i<=5;i++){
        s[a[i]*2]='?';
    }
    for(int i=1;i<=len;i++) printf("%c",s[i]); puts("");
    return 0;
}