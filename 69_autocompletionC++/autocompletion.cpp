/*
	http://cc.byexamples.com/2008/06/13/gnu-readline-how-to-keep-a-history-list-of-entered-command-lines/
	http://cc.byexamples.com/2008/06/16/gnu-readline-implement-custom-auto-complete/
*/
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
 
static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);
 
char* cmd [] ={ "hello", "world", "hell" ,"word", "quit", " " };
 
int main()
{
	for ( int i = 0; i < 6; i++ )
		printf( "commands[%i]: %s\n", i, cmd[ i ] );
    char *buf;
 
    rl_attempted_completion_function = my_completion;
 
    while((buf = readline("\n> "))!=NULL) {
        //enable auto-complete
        rl_bind_key('\t',rl_complete);
 
        printf("cmd [%s]\n",buf);
        if (strcmp(buf,"quit")==0)
            break;
        if (buf[0]!=0)
            add_history(buf);
    }
 
    free(buf);
 
    return 0;
}
 
 
static char** my_completion( const char * text , int start,  int end)
{
    char **matches;
 
    matches = (char **)NULL;
 
    if (start == 0)
        matches = rl_completion_matches ((char*)text, &my_generator);
    else
        rl_bind_key('\t',rl_abort);
 
    return (matches);
 
}
 
char* my_generator(const char* text, int state)
{
    static int list_index, len;
    char *name;
 
    if (!state) {
        list_index = 0;
        len = strlen (text);
    }
   
    while (name = cmd[list_index]) {
        list_index++;
 
        if (strncmp (name, text, len) == 0)
            return (dupstr(name));
    }
 
    /* If no names matched, then return NULL. */
    return ((char *)NULL);
 
}
 
char * dupstr (char* s) {
  char *r;
 
  r = (char*) xmalloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}
 
void * xmalloc (int size)
{
    void *buf;
 
    buf = malloc (size);
    if (!buf) {
        fprintf (stderr, "Error: Out of memory. Exiting.'n");
        exit (1);
    }
 
    return buf;
}

