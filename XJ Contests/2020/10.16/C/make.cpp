#include<bits/stdc++.h>
using namespace std;
const int maxn=(int)1e9;

int main(){
    srand(time(0));
    int n=5000,q=5000;
    cout<<n<<" "<<q<<endl;
    for(int i=1;i<=n;i++){
        printf("%d ",rand()%10+1);
    }
    puts("");
    for(int i=1;i<=q;i++){
        int r=rand()%n+1;
        int l=rand()%r+1;
        printf("%d %d\n",l,r);
    }
}