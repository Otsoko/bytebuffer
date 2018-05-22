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

void ByteBuffer::putAt(byte value, int index){
	buff[index] = value;
}

short ByteBuffer::getShort(){
	short s = *(short*)(buff+pos);
	pos += sizeof(short);
	return s;
}

short ByteBuffer::getShortAt(int index){
	short s = *(short*)(buff+index);
	pos += sizeof(short);
	return s;
}

void ByteBuffer::putShort(short value){
	*(short*)(buff+pos) = value;
	pos += sizeof(short);
}

void ByteBuffer::putShortAt(short value, int index){
	*(short*)(buff+index) = value;
}

int ByteBuffer::getInt(){
	int i = *(int*)(buff+pos);
	pos += sizeof(int);
	return i;
}

int ByteBuffer::getIntAt(int index){
	int i = *(int*)(buff+index);
	return i;
}

void ByteBuffer::putInt(int value){
	*(int*)(buff+pos) = value;
	pos += sizeof(int);
}

void ByteBuffer::putIntAt(int value, int index){
	*(int*)(buff+index) = value;
}