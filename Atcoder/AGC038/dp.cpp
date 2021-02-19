#include<bits/stdc++.h>
using namespace std;
int main()
{
    for(int i=1;;i++)
    {
        printf("The result of No.%d Case is:",i);
        system("./make > data.in");
        system("./me < data.in > me.out");
        system("./std < data.in > std.out");
        if(system("diff me.out std.out -b"))
        {
            puts("Wrong Answer!");
            return 0;
        }
        puts("Accepted!");
        //system("sleep 0.4");
    }
}