#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <cstddef>

typedef unsigned char byte;

class ByteBuffer {

  byte *buff;
  std::size_t size;
  int pos;

public:
  ByteBuffer(std::size_t size);
  ~ByteBuffer();
  std::size_t getSize();
  void reset();
  
  byte get();
  
  void put(byte value);
};

#endif
