
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}




//////////////////
void ncp( char *filetarget,  char *  filesource )
{
  // fread
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  //if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "wb");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) {
                freader = 0 ; 
            }
            n = fread(  buffer, sizeof(char), 1 , fp);
            m = fwrite( buffer, sizeof(char), 1,  fp2);
        }
        fclose(fp2);
        fclose(fp);
      }
}







char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}



//////////////////////////////
 void nrun_createdat( char *thefile )
 {
       char targetfile[PATH_MAX];
       strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
       strncat( targetfile , ".dat" , PATH_MAX - strlen( targetfile ) -1 );
       ncp( targetfile, thefile );
 }





//////////////////////////////
 void nrun_cmd( char *thefile )
 {
       char targetfile[PATH_MAX];
       char cmdi[PATH_MAX];

       strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
       strncat( targetfile , ".dat" , PATH_MAX - strlen( targetfile ) -1 );
       strncpy( cmdi , " pdflatex  " , PATH_MAX );
       strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );

       strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
       strncat( targetfile , ".pdf" , PATH_MAX - strlen( targetfile ) -1 );
       strncpy( cmdi , " mupdf  " , PATH_MAX );
       strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
 }






int main( int argc, char *argv[])
{
    int i ; 
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
	      if ( fexist( argv[ i ] ) == 1 )
              {
                nrun_createdat( argv[ i ] );
                nrun_cmd( argv[ i ] );
              }
          }
    }
    return 0;
}


