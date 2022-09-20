/*******************************************************************************
* FILENAME: my_keygen.c                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Generic keygen application based on sum of ASCII values                *
*                                                                              *
* AUTHOR: Fabiano Furtado        START DATE: 2018-01-08                        *
*                                                                              *
* COMPILING: ./make                                                            *
*                                                                              *
* CHANGES:                                                                     *
*                                                                              *
* REVNO:  VERSION DATE:  WHO:              DETAIL:                             *
*  1     2022-09-20    Fabiano Furtado  Fixed minor bugs/add flex key size     *
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define key_sum  914  // arbitrary number: sum of ASCII characters for
                      // key validation

static unsigned short
sum_ascii( const unsigned char skey[], const unsigned char key_size )
{
   unsigned short sum = 0;
   
   for (unsigned char i=0; i < key_size; i++ )
      sum += skey[i];
   return sum;
}

int
main( int argc, char *argv[] )
{
  const unsigned char valid_chars[] = "abcdefghijklmnopqrstuvwxyz"
                                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                      "0123456789.,-_@$%^*#?!<>=+"
                                      ";:|/\\[]{}()~'\"";
  unsigned char vd, ks, valid_keys, key_size;
  bool valid_key;

  if ( argc != 3 ) {
    fprintf( stderr,
             "Error! Argument not found!\n\n  Usage: %s <key size> "
             "<number of keys to gen>\n\n", argv[0] );
    return EXIT_FAILURE;
  }

  key_size = atoi( argv[1] );
  valid_keys = atoi( argv[2] );

  if ( key_size < 10 ) {
    fprintf( stderr, "Error! Cannot generate a key shorter than "
                     "10 characters!\n" );
    return EXIT_FAILURE;
  }

  if ( valid_keys == 0 ) {
    fprintf( stderr, "Error! Number of valid key cannot be 0!\n" ); 
    return EXIT_FAILURE;
  }

  unsigned char key[ key_size+1 ];
  key[key_size] = '\0';

  fprintf( stdout,
           "Wait... generating %d valid keys with %d digits and sum %d:\n",
          valid_keys, key_size, key_sum);

  srand( (unsigned int)time(NULL) + (unsigned int)getpid() );

  for ( vd=0; vd < valid_keys; vd++ ) {
    valid_key = false;
    while ( valid_key == false ) {
      for ( ks=0; ks < key_size; ks++ ) {
         key[ks] = valid_chars[ ( rand() + (int)vd + (int)ks ) %
                                (int)(sizeof( valid_chars )-1) ];
      }
      if ( sum_ascii( key, key_size ) == key_sum ) {
        valid_key = true;
        fprintf( stdout, "%s\n", key );
      }
    }
  }
  fprintf( stdout, "\nDone!\n\n" );
  return EXIT_SUCCESS;
}