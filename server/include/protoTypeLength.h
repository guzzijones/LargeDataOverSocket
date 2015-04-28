#ifndef PROTOTYPELENGTH_H
#define PROTOTYPELENGTH_H
#include <bitset>
class protoTypeLength{
private:


protected:
   std::bitset<16> Fx;// number of bytes
 
public:
   protoTypeLength(char f, char s);
   protoTypeLength(char *);

   void setFx(std::bitset<8>);
   void setSx(std::bitset<8>);

   std::bitset<8> getFx();
   std::bitset<8> getrSx();

};
#endif
