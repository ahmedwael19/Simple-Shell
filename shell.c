#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#define MAX_LINE 80
#include <string.h>
#include <ctype.h>


int main()
{
    pid_t pid;
    char *args_local[MAX_LINE/2 +1];
    char *args_global[MAX_LINE/2 +1];
    int should_run =1;
    char user_input[MAX_LINE]; //this is where the user write the command
    char *token=NULL;
    int global_counter=0;
    while(should_run)
    {
        int flag=0; //so We can have the parent running in the background
        int flag2=0; // for history

        printf("Ahmed@OS:~$ ");
        fflush(stdout);

        // USER INPUT //
        scanf("%[^\n]%*c", user_input);
        int local_counter=0;  //this is a local counter for the input to be breaked.
        global_counter=global_counter+local_counter;

        token = strtok(user_input, " ");

        if(strcmp(token,"history")==0 || strcmp(token,"history!!")==0 )
        {
                        //HISTORY//
            flag2=1;
            if(strcmp(token,"history")==0)
            {
                int history_counter=global_counter;
                if(global_counter==0) //error handling for empty history
                {
                    printf("Error : No commands in history");
                }
                if(global_counter>9)
                {
                    for(int n=global_counter-1;n>global_counter-11;n--)
                    {
                        printf("%d   %s\n",history_counter,args_global[n]);
                        history_counter--;
                    }
                }
                else if(global_counter<=9)
                {
                    for(int j=0;j<=global_counter-1;j++)
                    {
                        printf("%d   %s\n",history_counter,args_global[j]);
                        history_counter--;
                    }
                }
            }
            else if(strcmp(token,"history!!")==0)
            {
                printf("%s\n",args_global[global_counter-1]);
            }
            else if(strcmp(token,"history!")==0)
            {
                printf("test");
            }

        }
        //TO EXTRACT An Integer From a string -if any- and use it in History
        char *p=token;
        while(*p)
        {
            if(isdigit(*p))
            {
                flag2=1;
                long history_number=strtol(p,&p,10);
                if(history_number<=global_counter)
                {
                    printf("%s\n",args_global[history_number-1]);
                }
                else if(history_number > global_counter)
                {
                    printf("No such command in history\n");
                }
            }
            else
            {
                p++;
            }
        }


        while(token!=NULL && flag2==0)
        {
            if(strcmp(token,"&")==0){
                printf("test");
                flag=1;
                local_counter++;
                global_counter++; //so we can use it when invoking History
                token=NULL;
            }
            else
            {
                args_local[local_counter]= strdup(token);
                args_global[global_counter]=args_local[local_counter];
                token = strtok(NULL, " ");
                local_counter++;
                global_counter++; //so we can use it when invoking History
            }
        }
        args_local[local_counter]=NULL; //so that pid can work
        args_global[global_counter]=NULL; //so that pid can work

                        //FORK//

        pid=fork();
        if (pid<0 && flag2==0)
        {
            fprintf(stderr,"ForkFailed");
            return 1;
        }
        else if (pid==0 && flag2==0)
        {
           execvp(args_local[0],args_local);
        }
        else
        {
            if(flag==0 )
            {

            wait(NULL);
            }

        }
    }

    return 0;
}
