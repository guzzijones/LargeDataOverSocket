#include "protoTypeLength.h"
protoTypeLength::protoTypeLength(char f, char s){
   Fx=f;
   Sx=s;
}
protoTypeLength::protoTypeLength(char * inC){
   Fx=inC[0];
   Sx=inC[1];
}
void protoTypeLength::setFx(std::bitset<8> in){
   Fx=in;
}
void protoTypeLength::setSx(std::bitset<8> in ){
   Sx=in;
}



