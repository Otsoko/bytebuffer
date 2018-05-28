#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <cstddef>

typedef unsigned char byte;
typedef long long     Long;

typedef union {
    float value;
    byte  bytes[4];
} FloatB;

typedef union {
    double value;
    byte   bytes[8];
} DoubleB;

class ByteBuffer {

    byte * buff;
    size_t size;
    int    pos;

public:
    ByteBuffer(size_t size);
    ~ByteBuffer();

    size_t getSize();
    void   reset();
    byte * getBytes();

    byte   get();
    byte   getAt(int index);
    short  getShort();
    short  getShortAt(int index);
    int    getInt();
    int    getIntAt(int index);
    float  getFloat();
    float  getFloatAt(int index);
    Long   getLong();
    Long   getLongAt(int index);
    double getDouble();
    double getDoubleAt(int index);
    char * getString(int length);
    char * getStringAt(int length, int index);

    void   put(byte value);
    void   putAt(byte value, int index);
    void   putShort(short value);
    void   putShortAt(short value, int index);
    void   putInt(int value);
    void   putIntAt(int value, int index);
    void   putFloat(float value);
    void   putFloatAt(float value, int index);
    void   putLong(Long value);
    void   putLongAt(Long value, int index);
    void   putDouble(double value);
    void   putDoubleAt(double value, int index);
    void   putString(const char *value, int length);
    void   putStringAt(const char *value, int length, int index);

    char *getHexString();
    void  getHexString(char *str);

    ByteBuffer clone();

private:
    float intBitsToFloat(int value);
    float intBitsToFloatPow(int value);
};

#endif