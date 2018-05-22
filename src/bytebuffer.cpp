#include "bytebuffer.h"
#include <stdlib.h>
#include <iostream>

ByteBuffer::ByteBuffer(std::size_t size){
  this->size = size;
  pos = 0;
  buff = (byte*) malloc(size * sizeof(byte));
}

ByteBuffer::~ByteBuffer(){
	std::cout << "Liberando" << std::endl;
	free(buff);
}

std::size_t ByteBuffer::getSize(){
  return size;
}

void ByteBuffer::reset(){
	pos = 0;
}

byte ByteBuffer::get(){
	return buff[pos++];
}

void ByteBuffer::put(byte value){
	buff[pos++] = value;
}