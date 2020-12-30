/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=500005;
const int M=1005;
struct node{
    int opt,i,j,k;
};
vector<node> ans;
void add(int i,int j,int k){ans.push_back({1,i,j,k});}//a[k]=a[i]+a[j]
void com(int i,int j,int k){ans.push_back({2,i,j,k});}//a[k]=a[i]<a[j]
const int One=1e4,Two=2e4,Inf=3e4,Zero=4e4,Tmp=5e4,B=1e3;
int Base[31];
void init(){
    com(3,0,One);
    add(One,One,Two);
    add(One,One,Inf);
    for(int i=2;i<=60;i++) add(Inf,Inf,Inf);
    for(int i=0;i<=30;i++) Base[i]=i+B;
    add(One,Zero,Base[0]);
    for(int i=1;i<=30;i++) add(Base[i-1],Base[i-1],Base[i]);
}
void mul(int a,int b,int c){//a[c]=a[b]*a[a]
    add(a,b,Tmp);
    com(Tmp,Two,Tmp);
    com(Tmp,One,Tmp);
    add(c,Tmp,c);
}
void make_2pow(int pos,int x){
    while(x--) add(pos,pos,pos);
}
void split(int *a,int BB,int pos){
    for(int i=0;i<=30;i++) a[i]=BB+i;
    add(Zero,Zero,Tmp);
    for(int i=30;i>=0;i--){
        add(Tmp,Base[i],Tmp+1);
        add(pos,One,Tmp+2);
        com(Tmp+1,Tmp+2,a[i]);
        add(a[i],Zero,Tmp+1);
        make_2pow(Tmp+1,i);
        add(Tmp,Tmp+1,Tmp);
    }
}

int a[31],b[31];
int c[N];
void Slow_FFT(){
    for(int i=0;i<=60;i++) c[i]=300+i;
    for(int i=0;i<=30;i++){
        for(int j=0;j<=30;j++){
            mul(a[i],b[j],c[i+j]);
        }
    }
    for(int i=0;i<=60;i++){
        make_2pow(c[i],i);
        add(2,c[i],2);
    }
}

int main()
{
    init();
    split(a,100,0); split(b,200,1);
    Slow_FFT();
    printf("%d\n",sz(ans));
    for(auto &to : ans){
        if(to.opt==1){
            printf("+ %d %d %d\n",to.i,to.j,to.k);
        }
        else{
            printf("< %d %d %d\n",to.i,to.j,to.k);
        }
    }
    return 0;
}