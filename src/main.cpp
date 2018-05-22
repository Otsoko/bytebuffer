#include <iostream>
#include <cstddef>
#include "bytebuffer.h"

using namespace std;

int main(int argc, char const *argv[]) {
	
  ByteBuffer bytebuffer(5);
  cout << "Size: " << bytebuffer.getSize() << endl;
  
  bytebuffer.put(64);
  bytebuffer.put(33);
  bytebuffer.put(17);
  bytebuffer.putShort(345);
  
  bytebuffer.reset();
  
  byte b = bytebuffer.get();
  byte c = bytebuffer.get();
  byte d = bytebuffer.get();
  short s = bytebuffer.getShort();
  
  cout << "bytes leídos: " << (int)d << ", " << (short)s << endl;
  
  for(int i=0; i < bytebuffer.getSize(); i++){
	  cout << i << " " << (int)bytebuffer.getAt(i) << endl;
  }
  
  return 0;
}
