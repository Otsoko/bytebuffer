#include "bytebuffer.h"
#include <iostream>
#include <stdlib.h>

ByteBuffer::ByteBuffer(size_t size) {
    this->size = size;
    pos        = 0;
    buff       = (byte *) malloc(size * sizeof(byte));
}

ByteBuffer::~ByteBuffer() {
    free(buff);
}

size_t ByteBuffer::getSize() {
    return size;
}

void ByteBuffer::reset() {
    pos = 0;
}

byte *ByteBuffer::getBytes() {
    return buff;
}

byte ByteBuffer::get() {
    return buff[pos++];
}

byte ByteBuffer::getAt(int index) {
    return buff[index];
}

void ByteBuffer::put(byte value) {
    buff[pos++] = value;
}

void ByteBuffer::putAt(byte value, int index) {
    buff[index] = value;
}

short ByteBuffer::getShort() {
    short s = *(short *) (buff + pos);
    pos += sizeof(short);
    return s;
}

short ByteBuffer::getShortAt(int index) {
    short s = *(short *) (buff + index);
    return s;
}

void ByteBuffer::putShort(short value) {
    *(short *) (buff + pos) = value;
    pos += sizeof(short);
}

void ByteBuffer::putShortAt(short value, int index) {
    *(short *) (buff + index) = value;
}

int ByteBuffer::getInt() {
    int i = *(int *) (buff + pos);
    pos += sizeof(int);
    return i;
}

int ByteBuffer::getIntAt(int index) {
    int i = *(int *) (buff + index);
    return i;
}

float ByteBuffer::getFloat() {
    float f = *(float *) (buff + pos);
    pos += sizeof(float);
    return f;
}

float ByteBuffer::getFloatAt(int index) {
    float f = *(float *) (buff + index);
    return f;
}

void ByteBuffer::putInt(int value) {
    *(int *) (buff + pos) = value;
    pos += sizeof(int);
}

void ByteBuffer::putIntAt(int value, int index) {
    *(int *) (buff + index) = value;
}

void ByteBuffer::putFloat(float value) {
    *(float *) (buff + pos) = value;
    pos += sizeof(float);
}

void ByteBuffer::putFloatAt(float value, int index) {
    *(float *) (buff + index) = value;
}

char *ByteBuffer::getHexString() {
    char *str        = (char *) malloc(2 * size * sizeof(char));
    char  hexArray[] = "0123456789ABCDEF";

    for (size_t i = 0; i < size; i++) {
        byte v         = buff[i] & 0xFF;
        str[i * 2]     = hexArray[v >> 4];
        str[i * 2 + 1] = hexArray[v & 0x0F];
    }

    return str;
}

void ByteBuffer::getHexString(char *str) {
    char hexArray[] = "0123456789ABCDEF";

    for (size_t i = 0; i < size; i++) {
        byte v         = buff[i] & 0xFF;
        str[i * 2]     = hexArray[v >> 4];
        str[i * 2 + 1] = hexArray[v & 0x0F];
    }
    str[size * 2] = '\0';
}

ByteBuffer ByteBuffer::clone() {
    ByteBuffer cloned(size);

    for (size_t i = 0; i < size; i++) {
        cloned.putAt(buff[i], i);
    }

    return cloned;
}