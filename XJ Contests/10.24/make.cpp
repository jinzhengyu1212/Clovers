#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(0));
    int n=1000000;
    for(int i=1;i<=n;i++){
        printf("%c",rand()%26+'a');
    }
    return 0;
}