#include <iostream>
#include <cstddef>
#include "bytebuffer.h"

using namespace std;

int main(int argc, char const *argv[]) {
	
  ByteBuffer bytebuffer(9);
  cout << "Size: " << bytebuffer.getSize() << endl;
  
  bytebuffer.put(64);
  bytebuffer.put(33);
  bytebuffer.put(17);
  bytebuffer.putShort(345);
  bytebuffer.putInt(123456);
  
  bytebuffer.reset();
  
  byte b = bytebuffer.get();
  byte c = bytebuffer.get();
  byte d = bytebuffer.get();
  short s = bytebuffer.getShort();
  int in = bytebuffer.getInt();
  
  cout << "bytes leídos: " << (int)in << ", " << (short)s << endl;
  
  bytebuffer.putAt(44, 2);
  
  for(int i=0; i < bytebuffer.getSize(); i++){
	  cout << i << " " << (int)bytebuffer.getAt(i) << endl;
  }
  
  bytebuffer.putShortAt(55, 2);
  cout << (int)bytebuffer.getShortAt(2) << endl;
  cout << (int)bytebuffer.getIntAt(5) << endl;
  
  bytebuffer.putIntAt(78945, 2);
  cout << (int)bytebuffer.getIntAt(2) << endl;
  
  return 0;
}
