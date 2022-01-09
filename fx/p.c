int fa( int );
int fb( int );

int main( ) {
    int i= 5;
    printf( "funkcjaa(%i)=%i", i, fa(i) );
    printf( "funkc\"jab(%i)=%i", i, fb(i) );
    printf( "funkcjac(%i)=%i", i, fc(i, fa()) );
    printf( "jeszcze raz funkcjab(%i)=%i", i, fb(i) );
    return 0;
}

// fa();

/*
 * funkca( );
 * komentarz();
 * int
 *
 */

int fb( int x ) {
    x= fc(x);
    return 2/fa(x);
}