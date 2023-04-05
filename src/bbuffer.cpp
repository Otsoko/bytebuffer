#include "bbuffer.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>

BBuffer::BBuffer(size_t size) {
    this->size = size;
    pos        = 0;
    buff       = (byte *) malloc(size * sizeof(byte));
    memset(buff, 0x00, size);
    bigEndian = false;
}

BBuffer::BBuffer(const char *hexstring) {
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

BBuffer::BBuffer(byte *bytes, size_t size) {
    this->size = size;
    buff       = (byte *) malloc(size * sizeof(byte));
    memcpy(buff, bytes, size);
}

BBuffer::~BBuffer() {
    size = 0;
    pos  = 0;
    free(buff);
}

size_t BBuffer::getSize() {
    return size;
}

void BBuffer::reset() {
    pos = 0;
}

byte *BBuffer::getBytes() {
    return buff;
}

void BBuffer::order(Order order) {
    if (order == BB_BIG_ENDIAN) {
        bigEndian = true;
    } else {
        bigEndian = false;
    }
}

byte BBuffer::get() {
    return buff[pos++];
}

byte BBuffer::getAt(int index) {
    return buff[index];
}

short BBuffer::getShort() {
    short res = 0;
    if (bigEndian) {
        res = getShortB();
    } else {
        res = getShortL();
    }

    std::cout << "res: " << res << std::endl;

    return res;
}

short BBuffer::getShortL() {
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 2;

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short BBuffer::getShortB() {
    byte b0 = buff[pos + 1];
    byte b1 = buff[pos];

    pos += 2;

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short BBuffer::getShortAt(int index) {
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

short BBuffer::getShortLAt(int index) {
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

short BBuffer::getShortBAt(int index) {
    byte b0 = buff[index + 1];
    byte b1 = buff[index];

    return ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int BBuffer::getInt() {
    int res = 0;
    if (bigEndian) {
        res = getIntB();
    } else {
        res = getIntL();
    }
    return res;
}

int BBuffer::getIntL() {
    byte b3 = buff[pos + 3];
    byte b2 = buff[pos + 2];
    byte b1 = buff[pos + 1];
    byte b0 = buff[pos];

    pos += 4;

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int BBuffer::getIntB() {
    byte b0 = buff[pos + 3];
    byte b1 = buff[pos + 2];
    byte b2 = buff[pos + 1];
    byte b3 = buff[pos];

    pos += 4;

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int BBuffer::getIntAt(int index) {
    int res = 0;
    if (bigEndian) {
        res = getIntBAt(index);
    } else {
        res = getIntLAt(index);
    }
    return res;
}

int BBuffer::getIntLAt(int index) {
    byte b3 = buff[index + 3];
    byte b2 = buff[index + 2];
    byte b1 = buff[index + 1];
    byte b0 = buff[index];

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

int BBuffer::getIntBAt(int index) {
    byte b0 = buff[index + 3];
    byte b1 = buff[index + 2];
    byte b2 = buff[index + 1];
    byte b3 = buff[index];

    return (b3 << 24) | ((b2 & 0xFF) << 16) | ((b1 & 0xFF) << 8) | (b0 & 0xFF);
}

float BBuffer::getFloat() {
    return intBitsToFloat(getInt());
}

float BBuffer::getFloatAt(int index) {
    return intBitsToFloat(getIntAt(index));
}

Long BBuffer::getLong() {
    Long res = 0LL;
    if (bigEndian) {
        res = getLongB();
    } else {
        res = getLongL();
    }
    return res;
}

Long BBuffer::getLongL() {
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

Long BBuffer::getLongB() {
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

Long BBuffer::getLongAt(int index) {
    Long res = 0LL;
    if (bigEndian) {
        res = getLongBAt(index);
    } else {
        res = getLongLAt(index);
    }
    return res;
}

Long BBuffer::getLongLAt(int index) {
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

Long BBuffer::getLongBAt(int index) {
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

double BBuffer::getDouble() {
    double res = 0.0;
    if (bigEndian) {
        res = getDoubleB();
    } else {
        res = getDoubleL();
    }
    return res;
}

double BBuffer::getDoubleL() {
    DoubleB valueB;

    for (int i = 0; i < 8; i++) {
        valueB.bytes[i] = buff[pos++];
    }

    return valueB.value;
}

double BBuffer::getDoubleB() {
    DoubleB valueB;

    for (int i = 7; i >= 0; i--) {
        valueB.bytes[i] = buff[pos++];
    }

    return valueB.value;
}

double BBuffer::getDoubleAt(int index) {
    double res = 0.0;
    if (bigEndian) {
        res = getDoubleBAt(index);
    } else {
        res = getDoubleLAt(index);
    }
    return res;
}

double BBuffer::getDoubleLAt(int index) {
    DoubleB valueB;

    for (int i = 0; i < 8; i++) {
        valueB.bytes[i] = buff[index++];
    }

    return valueB.value;
}

double BBuffer::getDoubleBAt(int index) {
    DoubleB valueB;

    for (int i = 7; i >= 0; i--) {
        valueB.bytes[i] = buff[index++];
    }

    return valueB.value;
}

char *BBuffer::getString(int length) {
    char *str = NULL;

    if (bigEndian) {
        str = getStringB(length);
    } else {
        str = getStringL(length);
    }

    return str;
}

char *BBuffer::getStringL(int length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        str[i] = buff[pos++];
    }

    return str;
}

char *BBuffer::getStringB(int length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        str[i] = buff[pos++];
    }

    return str;
}

char *BBuffer::getStringAt(int length, int index) {
    char *str = NULL;

    if (bigEndian) {
        str = getStringBAt(length, index);
    } else {
        str = getStringLAt(length, index);
    }

    return str;
}

char *BBuffer::getStringLAt(int length, int index) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        str[i] = buff[index++];
    }

    return str;
}

char *BBuffer::getStringBAt(int length, int index) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        str[i] = buff[index++];
    }

    return str;
}

void BBuffer::put(byte value) {
    buff[pos++] = value;
}

void BBuffer::putAt(byte value, int index) {
    buff[index] = value;
}

void BBuffer::putShort(short value) {
    if (bigEndian) {
        putShortB(value);
    } else {
        putShortL(value);
    }
}

void BBuffer::putShortL(short value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
}

void BBuffer::putShortB(short value) {
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void BBuffer::putShortAt(short value, int index) {
    if (bigEndian) {
        putShortBAt(value, index);
    } else {
        putShortLAt(value, index);
    }
}

void BBuffer::putShortLAt(short value, int index) {
    buff[index++] = value & 0xFF;
    buff[index]   = (value >> 8) & 0xFF;
}

void BBuffer::putShortBAt(short value, int index) {
    buff[index++] = (value >> 8) & 0xFF;
    buff[index]   = value & 0xFF;
}

void BBuffer::putInt(int value) {
    if (bigEndian) {
        putIntB(value);
    } else {
        putIntL(value);
    }
}

void BBuffer::putIntL(int value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
}

void BBuffer::putIntB(int value) {
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void BBuffer::putIntAt(int value, int index) {
    if (bigEndian) {
        putIntBAt(value, index);
    } else {
        putIntLAt(value, index);
    }
}

void BBuffer::putIntLAt(int value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index]   = (value >> 24) & 0xFF;
}

void BBuffer::putIntBAt(int value, int index) {
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index]   = value & 0xFF;
}

void BBuffer::putFloat(float value) {
    if (bigEndian) {
        putFloatB(value);
    } else {
        putFloatL(value);
    }
}

void BBuffer::putFloatL(float value) {
    FloatB valueB;
    valueB.value = value;

    buff[pos++] = valueB.bytes[0];
    buff[pos++] = valueB.bytes[1];
    buff[pos++] = valueB.bytes[2];
    buff[pos++] = valueB.bytes[3];
}

void BBuffer::putFloatB(float value) {
    FloatB valueB;
    valueB.value = value;

    buff[pos++] = valueB.bytes[3];
    buff[pos++] = valueB.bytes[2];
    buff[pos++] = valueB.bytes[1];
    buff[pos++] = valueB.bytes[0];
}

void BBuffer::putFloatAt(float value, int index) {
    if (bigEndian) {
        putFloatBAt(value, index);
    } else {
        putFloatLAt(value, index);
    }
}

void BBuffer::putFloatLAt(float value, int index) {
    FloatB valueB;
    valueB.value = value;

    buff[index++] = valueB.bytes[0];
    buff[index++] = valueB.bytes[1];
    buff[index++] = valueB.bytes[2];
    buff[index]   = valueB.bytes[3];
}

void BBuffer::putFloatBAt(float value, int index) {
    FloatB valueB;
    valueB.value = value;

    buff[index++] = valueB.bytes[3];
    buff[index++] = valueB.bytes[2];
    buff[index++] = valueB.bytes[1];
    buff[index]   = valueB.bytes[0];
}

void BBuffer::putLong(Long value) {
    if (bigEndian) {
        putLongB(value);
    } else {
        putLongL(value);
    }
}

void BBuffer::putLongL(Long value) {
    buff[pos++] = value & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 32) & 0xFF;
    buff[pos++] = (value >> 40) & 0xFF;
    buff[pos++] = (value >> 48) & 0xFF;
    buff[pos++] = (value >> 56) & 0xFF;
}

void BBuffer::putLongB(Long value) {
    buff[pos++] = (value >> 56) & 0xFF;
    buff[pos++] = (value >> 48) & 0xFF;
    buff[pos++] = (value >> 40) & 0xFF;
    buff[pos++] = (value >> 32) & 0xFF;
    buff[pos++] = (value >> 24) & 0xFF;
    buff[pos++] = (value >> 16) & 0xFF;
    buff[pos++] = (value >> 8) & 0xFF;
    buff[pos++] = value & 0xFF;
}

void BBuffer::putLongAt(Long value, int index) {
    if (bigEndian) {
        putLongBAt(value, index);
    } else {
        putLongLAt(value, index);
    }
}

void BBuffer::putLongLAt(Long value, int index) {
    buff[index++] = value & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 32) & 0xFF;
    buff[index++] = (value >> 40) & 0xFF;
    buff[index++] = (value >> 48) & 0xFF;
    buff[index]   = (value >> 56) & 0xFF;
}

void BBuffer::putLongBAt(Long value, int index) {
    buff[index++] = (value >> 56) & 0xFF;
    buff[index++] = (value >> 48) & 0xFF;
    buff[index++] = (value >> 40) & 0xFF;
    buff[index++] = (value >> 32) & 0xFF;
    buff[index++] = (value >> 24) & 0xFF;
    buff[index++] = (value >> 16) & 0xFF;
    buff[index++] = (value >> 8) & 0xFF;
    buff[index++] = value & 0xFF;
}

void BBuffer::putDouble(double value) {
    if (bigEndian) {
        putDoubleB(value);
    } else {
        putDoubleL(value);
    }
}

void BBuffer::putDoubleL(double value) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 0; i < 8; i++) {
        buff[pos++] = valueB.bytes[i];
    }
}

void BBuffer::putDoubleB(double value) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 7; i >= 0; i--) {
        buff[pos++] = valueB.bytes[i];
    }
}

void BBuffer::putDoubleAt(double value, int index) {
    if (bigEndian) {
        putDoubleBAt(value, index);
    } else {
        putDoubleLAt(value, index);
    }
}

void BBuffer::putDoubleLAt(double value, int index) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 0; i < 8; i++) {
        buff[index++] = valueB.bytes[i];
    }
}

void BBuffer::putDoubleBAt(double value, int index) {
    DoubleB valueB;
    valueB.value = value;

    for (int i = 7; i >= 0; i--) {
        buff[index++] = valueB.bytes[i];
    }
}

void BBuffer::putString(const char *value, int length) {
    if (bigEndian) {
        putStringB(value, length);
    } else {
        putStringL(value, length);
    }
}

void BBuffer::putStringL(const char *value, int length) {
    for (int i = 0; i < length; i++) {
        buff[pos++] = value[i];
    }
}

void BBuffer::putStringB(const char *value, int length) {
    for (int i = length - 1; i >= 0; i--) {
        buff[pos++] = value[i];
    }
}

void BBuffer::putStringAt(const char *value, int length, int index) {
    if (bigEndian) {
        putStringBAt(value, length, index);
    } else {
        putStringLAt(value, length, index);
    }
}

void BBuffer::putStringLAt(const char *value, int length, int index) {
    for (int i = 0; i < length; i++) {
        buff[index++] = value[i];
    }
}

void BBuffer::putStringBAt(const char *value, int length, int index) {
    for (int i = length - 1; i >= 0; i--) {
        buff[index++] = value[i];
    }
}

char *BBuffer::getHexString() {
    char *str        = (char *) malloc(2 * size * sizeof(char) + 1);
    char  hexArray[] = "0123456789ABCDEF";

    for (size_t i = 0; i < size; i++) {
        byte v         = buff[i] & 0xFF;
        str[i * 2]     = hexArray[v >> 4];
        str[i * 2 + 1] = hexArray[v & 0x0F];
    }
    str[size * 2] = '\0';

    return str;
}

void BBuffer::getHexString(char *str) {
    char hexArray[] = "0123456789ABCDEF";

    for (size_t i = 0; i < size; i++) {
        byte v         = buff[i] & 0xFF;
        str[i * 2]     = hexArray[v >> 4];
        str[i * 2 + 1] = hexArray[v & 0x0F];
    }
    str[size * 2] = '\0';
}

BBuffer BBuffer::clone() {
    BBuffer cloned(size);

    for (size_t i = 0; i < size; i++) {
        cloned.putAt(buff[i], i);
    }

    cloned.pos       = pos;
    cloned.bigEndian = bigEndian;

    return cloned;
}

float BBuffer::intBitsToFloat(int value) {
    FloatB valueB;

    valueB.bytes[0] = value & 0xFF;
    valueB.bytes[1] = (value >> 8) & 0xFF;
    valueB.bytes[2] = (value >> 16) & 0xFF;
    valueB.bytes[3] = (value >> 24) & 0xFF;

    return valueB.value;
}

float BBuffer::intBitsToFloatPow(int value) {
    int s = (value >> 31) == 0 ? 1 : -1;
    int e = (value >> 23) & 0xFF;
    int m =
        (e == 0) ? ((value & 0x7FFFFF) << 1) : ((value & 0x7FFFFF) | 0x800000);

    return s * m * pow(2, e - 150);
}

bool BBuffer::isArchBigEndian(void) {
    union {
        int  i;
        char c[4];
    } bigint = {0x01020304};

    return bigint.c[0] == 1;
}