#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <cstddef>
//#include <cstdint>
#include <string>

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
  byte getAt(int index);
  short getShort();
  short getShortAt(int index);
  
  void put(byte value);
  void putAt(byte value, int index);
  void putShort(short value);
  void putShortAt(short value, int index);
  
};

#endif
