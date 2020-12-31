    for(int i=1;i<=k;i++){
        int x,y; scanf("%d%d",&x,&y);
        mp[x][y]='X';
        printf("%d\n",calc());
    }