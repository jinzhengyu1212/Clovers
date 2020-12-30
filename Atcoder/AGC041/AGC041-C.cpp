#include<bits/stdc++.h>
using namespace std;
const int N=1005;
char a[N][N];
void print3(int x,int y){
    a[x][y]=a[x][y+1]='y';
    a[x+1][y+2]=a[x+2][y+2]='x';
}
void print4(int x,int y){
    a[x][y]=a[x][y+1]=a[x+2][y+2]=a[x+2][y+3]='a';
    a[x+1][y]=a[x+1][y+1]=a[x+3][y+2]=a[x+3][y+3]='b';
    a[x+2][y]=a[x+3][y]=a[x][y+2]=a[x+1][y+2]='c';
    a[x][y+3]=a[x+1][y+3]=a[x+2][y+1]=a[x+3][y+1]='d';
}
void print5(int x,int y){
    a[x][y]=a[x][y+1]=a[x][y+4]=a[x+1][y+4]='a';
    a[x+4][y+4]=a[x+4][y+3]=a[x+4][y]=a[x+3][y]='a';
    a[x][y+2]=a[x][y+3]=a[x+2][y+4]=a[x+3][y+4]='b';
    a[x+1][y]=a[x+2][y]=a[x+4][y+1]=a[x+4][y+2]='b';
    print3(x+1,y+1);
}
void print7(int x,int y){
    a[x][y]=a[x][y+1]=a[x][y+4]=a[x][y+5]='a';
    a[x+1][y+6]=a[x+2][y+6]=a[x+5][y+6]=a[x+6][y+6]='a';
    a[x][y+2]=a[x][y+3]=a[x+3][y+6]=a[x+4][y+6]='b';
    print3(x+1,y); print3(x+1,y+3);
    print3(x+4,y); print3(x+4,y+3);
}

int main(){
    int n; scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) a[i][j]='.';
    if(n==2){
        puts("-1");
        return 0;
    }
    if(n==3){
        print3(1,1);
    }
    else if(n==6){
        print3(1,1);
        print3(4,4);
    }   
    else if(n==7){
        print7(1,1);
    }
    else if(n==11){
        print7(1,1);
        print4(8,8);
    }
    else{
        int t5=n%4;
        int x=1,y=1;
        while(t5--){
            print5(x,y);
            x+=5; y+=5;
        }
        int t4=(n-x+1)/4;
        while(t4--){
            print4(x,y);
            x+=4; y+=4;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) printf("%c",a[i][j]);
        puts("");
    }
    return 0;
}