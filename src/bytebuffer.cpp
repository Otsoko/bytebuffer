#include "bytebuffer.h"
#include <stdlib.h>
#include <iostream>
//#include <cstdint>
#include <string>

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

byte ByteBuffer::getAt(int index){
	return buff[index];
}

void ByteBuffer::put(byte value){
	buff[pos++] = value;
}

short ByteBuffer::getShort(){
	short s = *(short*)(buff+pos);
	pos += sizeof(short);
	return s;
}

void ByteBuffer::putShort(short value){
	*(short*)(buff+pos) = value;
}