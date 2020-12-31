#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int M=2500;
int n,a[N][N];
int dx[]={1,0,0,-1};
int dy[]={0,1,-1,0};
//R U D L big->small
struct node{int x,y,z;};
vector<node> ans;
void p(int x,int y,int z){ans.push_back({x,y,z});}
void print(int x,int y,int num){
    if(num<=0) return;
    for(int i=3;i>=0;i--){
        int xx=x+dx[i],yy=y+dy[i];
        if(a[xx+M][yy+M]!=num-i-1) print(xx,yy,num-i-1);
    }
    p(x,y,num); a[x+M][y+M]=num;
}

int main(){
    scanf("%d",&n);
    print(0,0,n);
    for(int i=0;i<(int)ans.size();i++) 
        printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].z);
    return 0;
}