#include "bytebuffer.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>

ByteBuffer::ByteBuffer(size_t size) {
    this->size = size;
    pos        = 0;
    buff       = (byte *) malloc(size * sizeof(byte));
    bigEndian  = false;
}

ByteBuffer::ByteBuffer(const char *hexstring) {
    size      = strlen(hexstring) / 2;
    pos       = 0;
    buff      = (byte *) malloc(size * sizeof(byte));
    bigEndian = false;

    for (size_t i = 0; i < size * 2; i += 2) {
        int  c = 0;
        char cb[3];
        cb[0] = *(hexstring + i);
        cb[1] = hexstring[i + 1];
        cb[2] = '\0';
        sscanf(cb, "%x", &c);
        buff[i / 2] = c;
    }
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

void ByteBuffer::order(Order order) {
    if (order == BB_BIG_ENDIAN) {
        bigEndian = true;
    } else {
        bigEndian = false;
    }
}

byte ByteBuffer::get() {
    return buff[pos++];
}

byte ByteBuffer::getAt(int index) {
    return buff[index];
}

short ByteBuffer::getShort() {
    short res = 0;
    if (bigEndian) {
        res = getShortB();
    } else {
        res = getShortL();
    }

    std::cout << "res: " << res << std::endl;

    return res;
}

short ByteBuffer::getShortL() {
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 2;

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short ByteBuffer::getShortB() {
    byte b0 = buff[pos + 1];
    byte b1 = buff[pos];

    pos += 2;

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short ByteBuffer::getShortAt(int index) {
    short res = 0;
    if (bigEndian) {
        res = getShortBAt(index);
    } else {
        res = getShortLAt(index);
    }

    std::cout << "res: " << res << std::endl;

    std::cout << "Machine is big endian: " << isArchBigEndian() << std::endl;

    return res;
}

short ByteBuffer::getShortLAt(int index) {
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short ByteBuffer::getShortBAt(int index) {
    byte b0 = buff[index + 1];
    byte b1 = buff[index];

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getInt() {
    int res = 0;
    if (bigEndian) {
        res = getIntB();
    } else {
        res = getIntL();
    }
    return res;
}

int ByteBuffer::getIntL() {
    byte b3 = buff[pos + 3];
    byte b2 = buff[pos + 2];
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 4;

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getIntB() {
    byte b0 = buff[pos + 3];
    byte b1 = buff[pos + 2];
    byte b2 = buff[pos + 1];
    byte b3 = buff[pos];

    pos += 4;

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getIntAt(int index) {
    int res = 0;
    if (bigEndian) {
        res = getIntBAt(index);
    } else {
        res = getIntLAt(index);
    }
    return res;
}

int ByteBuffer::getIntLAt(int index) {
    byte b3 = buff[index + 3];
    byte b2 = buff[index + 2];
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int ByteBuffer::getIntBAt(int index) {
    byte b0 = buff[index + 3];
    byte b1 = buff[index + 2];
    byte b2 = buff[index + 1];
    byte b3 = buff[index];

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

float ByteBuffer::getFloat() {
    return intBitsToFloat(getInt());
}

float ByteBuffer::getFloatAt(int index) {
    return intBitsToFloat(getIntAt(index));
}

Long ByteBuffer::getLong() {
    Long res = 0LL;
    if (bigEndian) {
        res = getLongB();
    } else {
        res = getLongL();
    }
    return res;
}

Long ByteBuffer::getLongL() {
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

Long ByteBuffer::getLongB() {
    byte b0 = buff[pos + 7];
    byte b1 = buff[pos + 6];
    byte b2 = buff[pos + 5];
    byte b3 = buff[pos + 4];
    byte b4 = buff[pos + 3];
    byte b5 = buff[pos + 2];
    byte b6 = buff[pos + 1];
    byte b7 = buff[pos];

    pos += 8;

    Long ll = (((Long) b7 & 0xFF) << 56) | (((Long) b6 & 0xFF) << 48) |
              (((Long) b5 & 0xFF) << 40) | (((Long) b4 & 0xFF) << 32) |
              (((Long) b3 & 0xFF) << 24) | (((Long) b2 & 0xFF) << 16) |
              (((Long) b1 & 0xFF) << 8) | ((Long) b0 & 0xFF);

    return ll;
}

Long ByteBuffer::getLongAt(int index) {
    Long res = 0LL;
    if (bigEndian) {
        res = getLongBAt(index);
    } else {
        res = getLongLAt(index);
    }
    return res;
}

Long ByteBuffer::getLongLAt(int index) {
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

Long ByteBuffer::getLongBAt(int index) {
    byte b0 = buff[index + 7];
    byte b1 = buff[index + 6];
    byte b2 = buff[index + 5];
    byte b3 = buff[index + 4];
    byte b4 = buff[index + 3];
    byte b5 = buff[index + 2];
    byte b6 = buff[index + 1];
    byte b7 = buff[index];

    Long ll = (((Long) b7 & 0xFF) << 56) | (((Long) b6 & 0xFF) << 48) |
              (((Long) b5 & 0xFF) << 40) | (((Long) b4 & 0xFF) << 32) |
              (((Long) b3 & 0xFF) << 24) | (((Long) b2 & 0xFF) << 16) |
              (((Long) b1 & 0xFF) << 8) | ((Long) b0 & 0xFF);

    return ll;
}

double ByteBuffer::getDouble() {
    double res = 0.0;
    if (bigEndian) {
        res = getDoubleB();
    } else {
        res = getDoubleL();
    }
    return res;
}

double ByteBuffer::getDoubleL() {
    DoubleB valueB;

    for (int i = 0; i < 8; i++) {
        valueB.bytes[i] = buff[pos++];
    }

    return valueB.value;
}

double ByteBuffer::getDoubleB() {
    DoubleB valueB;

    for (int i = 7; i >= 0; i--) {
        valueB.bytes[i] = buff[pos++];
    }

    return valueB.value;
}

double ByteBuffer::getDoubleAt(int index) {
    double res = 0.0;
    if (bigEndian) {
        res = getDoubleBAt(index);
    } else {
        res = getDoubleLAt(index);
    }
    return res;
}

double ByteBuffer::getDoubleLAt(int index) {
    DoubleB valueB;

    for (int i = 0; i < 8; i++) {
        valueB.bytes[i] = buff[index++];
    }

    return valueB.value;
}

double ByteBuffer::getDoubleBAt(int index) {
    DoubleB valueB;

    for (int i = 7; i >= 0; i--) {
        valueB.bytes[i] = buff[index++];
    }

    return valueB.value;
}

char *ByteBuffer::getString(int length) {
    char *str = NULL;

    if (bigEndian) {
        str = getStringB(length);
    } else {
        str = getStringL(length);
    }

    return str;
}

char *ByteBuffer::getStringL(int length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        str[i] = buff[pos++];
    }

    return str;
}

char *ByteBuffer::getStringB(int length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        str[i] = buff[pos++];
    }

    return str;
}

char *ByteBuffer::getStringAt(int length, int index) {
    char *str = NULL;

    if (bigEndian) {
        str = getStringBAt(length, index);
    } else {
        str = getStringLAt(length, index);
    }

    return str;
}

char *ByteBuffer::getStringLAt(int length, int index) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        str[i] = buff[index++];
    }

    return str;
}

char *ByteBuffer::getStringBAt(int length, int index) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        str[i] = buff[index++];
    }

    return str;
}

void ByteBuffer::put(byte value) {
    buff[pos++] = value;
}

void ByteBuffer::putAt(byte value, int index) {
    buff[index] = value;
}

void ByteBuffer::putShort(short value) {
    if (bigEndian) {
        putShortB(value);
    } else {
        putShortL(value);
    }
}

void ByteBuffer::putShortL(short value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
}

void ByteBuffer::putShortB(short value) {
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void ByteBuffer::putShortAt(short value, int index) {
    if (bigEndian) {
        putShortBAt(value, index);
    } else {
        putShortLAt(value, index);
    }
}

void ByteBuffer::putShortLAt(short value, int index) {
    buff[index++] = value & 0xFF;
    buff[index]   = (value >> 8) & 0xFF;
}

void ByteBuffer::putShortBAt(short value, int index) {
    buff[index++] = (value >> 8) & 0xFF;
    buff[index]   = value & 0xFF;
}

void ByteBuffer::putInt(int value) {
    if (bigEndian) {
        putIntB(value);
    } else {
        putIntL(value);
    }
}

void ByteBuffer::putIntL(int value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
}

void ByteBuffer::putIntB(int value) {
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void ByteBuffer::putIntAt(int value, int index) {
    if (bigEndian) {
        putIntBAt(value, index);
    } else {
        putIntLAt(value, index);
    }
}

void ByteBuffer::putIntLAt(int value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index]   = (value >> 24) & 0xFF;
}

void ByteBuffer::putIntBAt(int value, int index) {
    buff[index]   = (value >> 24) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = value & 0xFF;
}

void ByteBuffer::putFloat(float value) {
    if (bigEndian) {
        putFloatB(value);
    } else {
        putFloatL(value);
    }
}

void ByteBuffer::putFloatL(float value) {
    FloatB valueB;
    valueB.value = value;

    buff[pos++] = valueB.bytes[0];
    buff[pos++] = valueB.bytes[1];
    buff[pos++] = valueB.bytes[2];
    buff[pos++] = valueB.bytes[3];
}

void ByteBuffer::putFloatB(float value) {
    FloatB valueB;
    valueB.value = value;

    buff[pos++] = valueB.bytes[3];
    buff[pos++] = valueB.bytes[2];
    buff[pos++] = valueB.bytes[1];
    buff[pos++] = valueB.bytes[0];
}

void ByteBuffer::putFloatAt(float value, int index) {
    if (bigEndian) {
        putFloatBAt(value, index);
    } else {
        putFloatLAt(value, index);
    }
}

void ByteBuffer::putFloatLAt(float value, int index) {
    FloatB valueB;
    valueB.value = value;

    buff[index++] = valueB.bytes[0];
    buff[index++] = valueB.bytes[1];
    buff[index++] = valueB.bytes[2];
    buff[index]   = valueB.bytes[3];
}

void ByteBuffer::putFloatBAt(float value, int index) {
    FloatB valueB;
    valueB.value = value;

    buff[index++] = valueB.bytes[3];
    buff[index++] = valueB.bytes[2];
    buff[index++] = valueB.bytes[1];
    buff[index]   = valueB.bytes[0];
}

void ByteBuffer::putLong(Long value) {
    if (bigEndian) {
        putLongB(value);
    } else {
        putLongL(value);
    }
}

void ByteBuffer::putLongL(Long value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 32) & 0xFF;
    buff[pos++] = (value >> 40) & 0xFF;
    buff[pos++] = (value >> 48) & 0xFF;
    buff[pos++] = (value >> 56) & 0xFF;
}

void ByteBuffer::putLongB(Long value) {
    buff[pos++] = (value >> 56) & 0xFF;
    buff[pos++] = (value >> 48) & 0xFF;
    buff[pos++] = (value >> 40) & 0xFF;
    buff[pos++] = (value >> 32) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void ByteBuffer::putLongAt(Long value, int index) {
    if (bigEndian) {
        putLongBAt(value, index);
    } else {
        putLongLAt(value, index);
    }
}

void ByteBuffer::putLongLAt(Long value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 32) & 0xFF;
    buff[index++] = (value >> 40) & 0xFF;
    buff[index++] = (value >> 48) & 0xFF;
    buff[index]   = (value >> 56) & 0xFF;
}

void ByteBuffer::putLongBAt(Long value, int index) {
    buff[index++] = (value >> 56) & 0xFF;
    buff[index++] = (value >> 48) & 0xFF;
    buff[index++] = (value >> 40) & 0xFF;
    buff[index++] = (value >> 32) & 0xFF;
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = value & 0xFF;
}

void ByteBuffer::putDouble(double value) {
    if (bigEndian) {
        putDoubleB(value);
    } else {
        putDoubleL(value);
    }
}

void ByteBuffer::putDoubleL(double value) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 0; i < 8; i++) {
        buff[pos++] = valueB.bytes[i];
    }
}

void ByteBuffer::putDoubleB(double value) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 7; i >= 0; i--) {
        buff[pos++] = valueB.bytes[i];
    }
}

void ByteBuffer::putDoubleAt(double value, int index) {
    if (bigEndian) {
        putDoubleBAt(value, index);
    } else {
        putDoubleLAt(value, index);
    }
}

void ByteBuffer::putDoubleLAt(double value, int index) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 0; i < 8; i++) {
        buff[index++] = valueB.bytes[i];
    }
}

void ByteBuffer::putDoubleBAt(double value, int index) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 7; i >= 0; i--) {
        buff[index++] = valueB.bytes[i];
    }
}

void ByteBuffer::putString(const char *value, int length) {
    if (bigEndian) {
        putStringB(value, length);
    } else {
        putStringL(value, length);
    }
}

void ByteBuffer::putStringL(const char *value, int length) {
    for (int i = 0; i < length; i++) {
        buff[pos++] = value[i];
    }
}

void ByteBuffer::putStringB(const char *value, int length) {
    for (int i = length - 1; i >= 0; i--) {
        buff[pos++] = value[i];
    }
}

void ByteBuffer::putStringAt(const char *value, int length, int index) {
    if (bigEndian) {
        putStringBAt(value, length, index);
    } else {
        putStringLAt(value, length, index);
    }
}

void ByteBuffer::putStringLAt(const char *value, int length, int index) {
    for (int i = 0; i < length; i++) {
        buff[index++] = value[i];
    }
}

void ByteBuffer::putStringBAt(const char *value, int length, int index) {
    for (int i = length - 1; i >= 0; i--) {
        buff[index++] = value[i];
    }
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

bool ByteBuffer::isArchBigEndian(void) {
    union {
        int  i;
        char c[4];
    } bigint = {0x01020304};

    return bigint.c[0] == 1;
}