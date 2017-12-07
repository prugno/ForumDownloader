#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int system(const char *command);

int fd; /* File descriptor for the port */
FILE *data;
FILE *fp;
FILE *stream;
void removeAll(char * str, char * toRemove);

int main(int argc, char *argv[]) {
    
    char buf[10000];
    char *sup;
    char res[10000];
    char res1[10000];
    char res6[10000];
    char res7[10000];

    int n=0;
    int page=0;
    for(page=1;page<67;page++){
    sprintf(res6,"curl -g --location \"http://www.phica.net/forums/showthread.php?1926720-Ragazze-di-BARI-(e-Puglia)/page%d\" > /Users/uea/Documents/xcode/ForumDownloader/ForumDownloader/bari/ForumPage.html",page);
        system(res6);
        
    printf("DOWNLOAD COMPLETE\n");

        fp=fopen("/Users/uea/Documents/xcode/ForumDownloader/ForumDownloader/bari/ForumPage.html","r");
    data=fopen("/Users/uea/Documents/xcode/ForumDownloader/ForumDownloader/bari/support.txt","w");
    int i=0;

        if (fp) {       // File is ok
        while (!feof(fp)){  //Read file
            if (fgets(buf, 10000, fp) != NULL)  {
                sup=strstr(buf,"attachmentid=");           //Match attachmentid= token
                if(sup != NULL){    //If there' s a match
                    if(sscanf(sup,"%s %s",res,res1)>0){ //Memorize the remaining string
                      printf("------------Page %d, N.%d, %s %s\n",page,n,res,res1);
                       // for(i=0;i<48;i++) printf("%c",i,res1[i]);
                        sprintf(res7,"curl \"http://www.phica.net/forums/attachment.php?%s > /Users/uea/Documents/xcode/ForumDownloader/ForumDownloader/bari/Page%d_file%d.jpg",res,page,n);
                      //  printf("RES7 %s\n",res7);   //Use the string

                       // fprintf(data,"http://www.phica.net/forums/attachment.php?%s\n",res);   //Extract ASCII URL
                        system(res7);   //Download images.
                        n++;

                        }
                }
            }
        }
    }
        fclose(fp);
        fclose(data);
    }
}


