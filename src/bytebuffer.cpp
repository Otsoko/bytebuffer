#include "bytebuffer.h"
#include <cmath>
#include <stdlib.h>

ByteBuffer::ByteBuffer(size_t size) {
    this->size = size;
    pos        = 0;
    buff       = (byte *) malloc(size * sizeof(byte));
}

ByteBuffer::~ByteBuffer() {
    size = 0;
    pos  = 0;
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

short ByteBuffer::getShort() {
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 2;

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short ByteBuffer::getShortAt(int index) {
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getInt() {
    byte b3 = buff[pos + 3];
    byte b2 = buff[pos + 2];
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 4;

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getIntAt(int index) {
    byte b3 = buff[index + 3];
    byte b2 = buff[index + 2];
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

float ByteBuffer::getFloat() {
    return intBitsToFloat(getInt());
}

float ByteBuffer::getFloatAt(int index) {
    return intBitsToFloat(getIntAt(index));
}

Long ByteBuffer::getLong() {
    byte b7 = buff[pos + 7];
    byte b6 = buff[pos + 6];
    byte b5 = buff[pos + 5];
    byte b4 = buff[pos + 4];
    byte b3 = buff[pos + 3];
    byte b2 = buff[pos + 2];
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 8;

    Long ll = (((Long) b7 & 0xFF) << 56) | (((Long) b6 & 0xFF) << 48) |
              (((Long) b5 & 0xFF) << 40) | (((Long) b4 & 0xFF) << 32) |
              (((Long) b3 & 0xFF) << 24) | (((Long) b2 & 0xFF) << 16) |
              (((Long) b1 & 0xFF) << 8) | ((Long) b0 & 0xFF);

    return ll;
}

Long ByteBuffer::getLongAt(int index) {
    byte b7 = buff[index + 7];
    byte b6 = buff[index + 6];
    byte b5 = buff[index + 5];
    byte b4 = buff[index + 4];
    byte b3 = buff[index + 3];
    byte b2 = buff[index + 2];
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    Long ll = (((Long) b7 & 0xFF) << 56) | (((Long) b6 & 0xFF) << 48) |
              (((Long) b5 & 0xFF) << 40) | (((Long) b4 & 0xFF) << 32) |
              (((Long) b3 & 0xFF) << 24) | (((Long) b2 & 0xFF) << 16) |
              (((Long) b1 & 0xFF) << 8) | ((Long) b0 & 0xFF);

    return ll;
}

void ByteBuffer::put(byte value) {
    buff[pos++] = value;
}

void ByteBuffer::putAt(byte value, int index) {
    buff[index] = value;
}

void ByteBuffer::putShort(short value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
}

void ByteBuffer::putShortAt(short value, int index) {
    buff[index++] = value & 0xFF;
    buff[index]   = (value >> 8) & 0xFF;
}

void ByteBuffer::putInt(int value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
}

void ByteBuffer::putIntAt(int value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index]   = (value >> 24) & 0xFF;
}

void ByteBuffer::putFloat(float value) {
    FloatB valueB;
    valueB.value = value;

    buff[pos++] = valueB.bytes[0];
    buff[pos++] = valueB.bytes[1];
    buff[pos++] = valueB.bytes[2];
    buff[pos++] = valueB.bytes[3];
}

void ByteBuffer::putFloatAt(float value, int index) {
    FloatB valueB;
    valueB.value = value;

    buff[index++] = valueB.bytes[0];
    buff[index++] = valueB.bytes[1];
    buff[index++] = valueB.bytes[2];
    buff[index]   = valueB.bytes[3];
}

void ByteBuffer::putLong(Long value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 32) & 0xFF;
    buff[pos++] = (value >> 40) & 0xFF;
    buff[pos++] = (value >> 48) & 0xFF;
    buff[pos++] = (value >> 56) & 0xFF;
}

void ByteBuffer::putLongAt(Long value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 32) & 0xFF;
    buff[index++] = (value >> 40) & 0xFF;
    buff[index++] = (value >> 48) & 0xFF;
    buff[index]   = (value >> 56) & 0xFF;
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

float ByteBuffer::intBitsToFloat(int value) {
    FloatB valueB;

    valueB.bytes[0] = value & 0xFF;
    valueB.bytes[1] = (value >> 8) & 0xFF;
    valueB.bytes[2] = (value >> 16) & 0xFF;
    valueB.bytes[3] = (value >> 24) & 0xFF;

    return valueB.value;
}

float ByteBuffer::intBitsToFloatPow(int value) {
    int s = (value >> 31) == 0 ? 1 : -1;
    int e = (value >> 23) & 0xFF;
    int m =
        (e == 0) ? ((value & 0x7FFFFF) << 1) : ((value & 0x7FFFFF) | 0x800000);

    return s * m * pow(2, e - 150);
}