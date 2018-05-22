#include <iostream>
#include <cstddef>
#include "bytebuffer.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Funcionando" << endl;

  ByteBuffer bytebuffer(7);
  cout << "Size: " << bytebuffer.getSize() << endl;
  
  bytebuffer.put(64);
  bytebuffer.reset();
  byte b = bytebuffer.get();
  cout << "byte leído: " << (int)b << endl;
  
  return 0;
}
