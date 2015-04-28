#include "ASocket.h"

ASocket::ASocket(int inPort,int inMaxListenters){
 listenfd = socket(AF_INET,SOCK_STREAM,0);   
 maxListeners=inMaxListenters;
 port=inPort;
 if(listenfd < 0)
   throw std::runtime_error("SocketFailed to connect");
 //clear out serv_addr space
 serv_addr = new struct sockaddr_in;
 serv_addr->sin_family=AF_INET;
 serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
 serv_addr->sin_port=htons(port);
 
 std::cout << "next step is to bind" << std::endl;
 //serv_addr needs to be cast from sockaddr_in to sockaddr pointer
 bind(listenfd,(struct sockaddr*)(serv_addr),sizeof(*serv_addr));

}
void ASocket::listenSocket(){

 if(listen(listenfd,maxListeners)==-1){
   throw std::runtime_error("failed to listen");
 }
 printf("Listening on: %i", port );
//event loop 
// signal (SIGINT, handler);
signal(SIGCHLD,SIG_IGN);
 while(1){
   int newSockFd;
   newSockFd = accept(listenfd,(struct sockaddr*)NULL,NULL);
   if(newSockFd<0)
      std::cerr << "Error on Accept" << std::endl;
   int pid = fork();
   if(pid <0)
      std::cerr << "Error on Fork" << std::endl;
   if(pid ==0){//if pid = zero that means it is the child.
      close(listenfd);//close the parent file descriptor, we do not need it and then process will wait again.
      //create an object here to do stuff with the socket
      DoStuff(newSockFd);
      exit(0);//exit child process
    }
    else
      close(newSockFd);//there was a problem
   }//end of while loop
   close(listenfd);
   //never happens;
}

bool DoWrite(const int & sock,void * data,uint32_t size){
  uint32_t bytesWrite=0;
  while(bytesWrite!=size){
      uint32_t WriteThisTime;
      do{
      WriteThisTime=send(sock,data+bytesWrite,size-bytesWrite,0); // Receive the message length
      }while((WriteThisTime == -1) && (errno == EINTR));
      if(WriteThisTime<0){
      std::cout << "Write failure" << std::endl;
      return false;
      }
      bytesWrite+=WriteThisTime;
   }  
   return true;
}

bool ASocket::DoRead(const int & sock,void * data,uint32_t size){
  uint32_t bytesRead=0;
  while(bytesRead!=size){
      uint32_t readThisTime;
      do{
      readThisTime=recv(sock,data+bytesRead,size-bytesRead,0); // Receive the message length
      }while((readThisTime == -1) && (errno == EINTR));
      if(readThisTime<0){
      std::cout << "read failure" << std::endl;
      return false;
      }
      bytesRead+=readThisTime;
   }  
   std::cout << "size: " << size << std::endl;
   std::cout << "bytes read: " << bytesRead << std::endl;
   return true;
}

void ASocket::DoStuff(int sock){
   std::cout << "doing stuff" << std::endl;
   int n;
   uint32_t dataLength;
   int result;
   DoRead(sock,&dataLength,sizeof(uint32_t));
   dataLength = ntohl(dataLength ); // Ensure host system byte order on the int;from the network will be network byte order

   std::cout << "data length: " << dataLength << std::endl;
   //allocate a buffer of the size being sent +1
   char rcvBuf[dataLength+1];    // Allocate a receive buffer
   
   DoRead(sock,rcvBuf,dataLength); // Receive the string data
   //set the datalength postiion to null
   //ie if length is 3 we created a 4 element char, position 0,1,2,3 , 3 is set to null;
   rcvBuf[dataLength]='\0';
   std::string receivedString;                        // assign buffered data to a 
//   rcvBuf[dataLength+1]='\0';
   std::cout << "string: " << rcvBuf<< std::endl;
   std::cout << "data length: " << dataLength << std::endl;
 
}

ASocket::~ASocket(){
   delete serv_addr;

}


