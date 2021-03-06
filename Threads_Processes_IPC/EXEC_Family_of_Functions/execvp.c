/*              execvp.c
 
execvp(file,args): Process which calls this API stops itself and get replaced by file=EXE.
*/

#ifdef PROG1
//PROG1
# include <unistd.h>
void main(){
    printf ("I am prog1");
}
# gcc prog1.c -o PROG1
#endif

#ifdef PROG2
//PROG2
# include <unistd.h>
void main(){
    char *args[]={"./PROG1",NULL};
    execvp(args[0],args);
    printf("\nProg2 Last line");    <- This line not executed bcoz as soon as the execvp() function is called, this program is replaced by PROG1
}
# gcc prog2.c -o PROG2
#endif

# ./PROG2
    I am prog1
