void Read( int &x ) {
    char ch;
    x = 0;
    ch = getchar();
    while( !(ch >= '0' && ch <= '9') ) ch = getchar();
    while( ch >= '0' && ch <= '9' ) {
        x = x * 10 + ch - '0' ;
        ch = getchar();
    }
}
