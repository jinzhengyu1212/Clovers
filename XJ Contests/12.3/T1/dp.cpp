#include<bits/stdc++.h>
using namespace std;
int main(){
    int i;
    for(i=0;;i++){
        printf("The Result of No.%d TestCase is:",i);
        system("./make > data.in");
        system("./me < data.in > me.out");
        system("./std < data.in > std.out");
        if(system("diff me.out std.out -b")){
            puts("Wrong Answer!");
            //return 0;
        }
        puts("Accepted!");
        system("sleep 0.8");
    }
    return 0;
}