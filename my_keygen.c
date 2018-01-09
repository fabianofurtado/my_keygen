/***********************************************************************
* FILENAME :        my_keygen.c
*
* DESCRIPTION :
*       Generic keygen application based on sum of ASCII values
*
* AUTHOR :    Fabiano Furtado        START DATE :    2018-01-08
* 
* COMPILING : gcc my_keygen.c -o my_keygen -Wall
*
* CHANGES :
*
* REF NO  VERSION DATE    WHO     DETAIL
*
*
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define key_size   10  // size of the key in characters
#define key_sum   914  // arbitrary number: sum of ASCII characters for key validation

unsigned short sum_ascii(unsigned char skey[]) {
   unsigned short sum = 0;
   
   for (unsigned char i=0; i < key_size; i++ )
      sum += skey[i];
   return sum;
}

int main( int argc, char *argv[] ) {
   const unsigned char valid_chars[73] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-_@$%^*#?!";
   unsigned char vd, ks, valid_keys, key[key_size+1];
   bool valid_key = false;

   key[key_size] = '\0';

   if (argc != 2) {
        printf("Error! Argument not found!\n\n  Usage: %s <number of keys to gen>\n\n", argv[0]);
        exit(1);
   }

   valid_keys = atoi( argv[1] );
   
   printf("Wait... generating %d valid keys with %d digits and sum %d:\n", valid_keys, key_size, key_sum);

   srand((unsigned int) time(NULL) + getpid());

   for (vd=0; vd < valid_keys; vd++) {
      valid_key = false;
      while (!valid_key) {
         for (ks=0; ks < key_size; ks++)
            key[ks] = valid_chars[rand() % sizeof(valid_chars)];
         if ( sum_ascii(key) == key_sum ) {
            valid_key = true;
            printf("  * Valid key %03d: %s\n", vd+1, key);
         }
      }
   }
   printf("\nDone!\n\n");
   return 0;
}
