#include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <assert.h>
 

  static void
  displayError(const char *on_what) {
	  if ( errno != 0 ) {
		  fputs(strerror(errno),stderr);
		  fputs(": ",stderr);
	  }
	  fputs(on_what,stderr);
	  fputc('\n',stderr);
	  exit(1);
  }
 
  int main(int argc,char **argv) {
	  int z;
	  int s = -1;      
	  int sndbuf=0;     
	  int rcvbuf=0;     
	  socklen_t optlen; 
	 

	  s = socket(PF_INET,SOCK_STREAM,0);
	  if ( s == -1 ) {
		displayError("socket(2)");
	  }
	 
	 /*
	  * Get socket option SO_SNDBUF:
	  */
	  optlen = sizeof sndbuf;
	  z = getsockopt(s,
	                 SOL_SOCKET,
					 SO_SNDBUF,
	                 &sndbuf,&optlen);
	  if ( z ) {
		displayError("getsockopt(s,SOL_SOCKET," 
      	             "SO_SNDBUF)");
	  }
	 
	  assert(optlen == sizeof sndbuf);
	 

	  optlen = sizeof rcvbuf;
	  z = getsockopt(s,
	                 SOL_SOCKET,
					 SO_RCVBUF,
	                 &rcvbuf,&optlen);
	  if ( z ) {
		displayError("getsockopt(s,SOL_SOCKET,"
		             "SO_RCVBUF)");
	  }
	 
	  assert(optlen == sizeof rcvbuf);
	 

	  printf( "Socket s : %d\n",s);
	  printf( "Send buf: %d bytes\n", sndbuf);
	  printf( "Recv buf: %d bytes\n", rcvbuf);
	 
	  close(s);
	  return 0;
  }