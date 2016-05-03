#include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/socket.h>
 #include <sys/un.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>



 static void displayError(const char *on_what)
 {
    perror(on_what); 
    exit(1);         
 }


    char * sock_addr(int s,char *buf,size_t bufsiz) {
    int z;         /* Status return code */
    struct sockaddr_in adr_inet;/* AF_INET */
    int len_inet;  /* length */

    len_inet = sizeof adr_inet;
    z = getsockname(s, (struct sockaddr *)&adr_inet, &len_inet);
    if ( z == -1 ) 
    {
       return NULL; /* Failed */
    }

    snprintf(buf,bufsiz, "%s:%u",
    inet_ntoa(adr_inet.sin_addr),
    (unsigned)ntohs(adr_inet.sin_port));
    return buf;
 }

 int  main(int argc,char **argv,char **envp) 
{
    int z; /* Status return code */
    int sck_inet; /* Socket */
    struct sockaddr_in adr_inet;/* AF_INET */
    int len_inet; /* length */
    char buf[64]; /* Work buffer */

    sck_inet = socket(AF_INET,SOCK_STREAM,0);
    if ( sck_inet == -1 ) {
       displayError("socket()");
    }

    memset(&adr_inet,0,sizeof adr_inet);
    adr_inet.sin_family = AF_INET;
    adr_inet.sin_port = htons(9000);
    inet_aton ("127.0.0.24",&adr_inet.sin_addr);
    len_inet = sizeof adr_inet;

    z = bind(sck_inet,
    (struct sockaddr *)&adr_inet,
    len_inet);
    if ( z == -1 ) {
       displayError("bind()");
    }


    if ( !sock_addr(sck_inet,buf,sizeof buf))
   {
       displayError("sock_addr()");
    }

    printf("Address is'%s'\n" ,buf);
    close(sck_inet);
    return 0;
 }