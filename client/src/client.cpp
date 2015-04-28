extern "C"{
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
}
#include <string>
#include <iostream>
// various bits for floating point types--
// varies for different architectures
typedef float float32_t;
typedef double float64_t;

/*
** packi16() -- store a 16-bit int into a char buffer (like htons())
*/ 
void packi16(unsigned char *buf, unsigned int i)
{
    *buf++ = i>>8; *buf++ = i;
}

/*
** packi32() -- store a 32-bit int into a char buffer (like htonl())
*/ 
void packi32(unsigned char *buf, unsigned long i)
{
    *buf++ = i>>24; *buf++ = i>>16;
    *buf++ = i>>8;  *buf++ = i;
}

bool DoRead(const int & sock,void * data,uint32_t size){
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
   return true;
}


bool DoWrite(const int & sock,void * data,uint32_t size){
  uint32_t bytesWrite=0;
//  std::cout << "size: " << size << st::endl;
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
   std::cout << "bytes Write: " << bytesWrite << std::endl;
   return true;
}


int main(void)
{
   int sockfd = 0,n = 0;
   unsigned  char sendBuff[2];
   struct sockaddr_in serv_addr;
   int i = 200;
   packi16(sendBuff,i); 

                                                          // data 
  // strcat(total,(char*)sendBuffFloat);
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(3000);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }
/* 
  n = write(sockfd, sendBuff, sizeof(sendBuff));
  while(n!=strlen((char*)sendBuff)&&n!=-1 ){
     n = write(sockfd, sendBuff, sizeof(sendBuff));
  }
  if(n<0){
      printf("Error Sending Data\n");
  }
*/ 
std::string dataToSend = "Hello World!";
//for(int i=0; i < 100000;i++){
 //  dataToSend=dataToSend + "a";
//}
std::cout << "datatosend: " << dataToSend << std::endl;
std::cout << "size: " << dataToSend.length() << std::endl;
uint32_t dataLength = htonl(dataToSend.size()); // Ensure network byte order 
bool ok;
ok=DoWrite(sockfd,&dataLength,sizeof(uint32_t));

ok=DoWrite(sockfd,&(dataToSend[0]),dataToSend.size());
std::cout << "Send ok: "<< ok << std::endl;

//int num=send(sockfd,&dataLength ,sizeof(uint32_t) ,MSG_CONFIRM); // Send the data length
//int numSent=send(sockfd,dataToSend.c_str(),dataToSend.size(),MSG_CONFIRM); // Send the string 
//std::cout << "actual sent: " << numSent;
 

  return 0;
}
