#ifndef _BBUFFER_H_
#define _BBUFFER_H_

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

typedef enum { BB_LITTLE_ENDIAN, BB_BIG_ENDIAN } Order;

class BBuffer {

    byte * buff;
    size_t size;
    int    pos;
    bool   bigEndian;

public:
    BBuffer(size_t size);
    BBuffer(const char *hexstring);
    BBuffer(byte *bytes, size_t length);
    ~BBuffer();

    size_t getSize();
    void   reset();
    byte * getBytes();
    void   order(Order order);

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
    char * getHexString();
    void   getHexString(char *str);

    BBuffer clone();

private:
    float  intBitsToFloat(int value);
    float  intBitsToFloatPow(int value);
    bool   isArchBigEndian(void);

    short  getShortL();
    short  getShortB();
    short  getShortLAt(int index);
    short  getShortBAt(int index);
    void   putShortL(short value);
    void   putShortB(short value);
    void   putShortLAt(short value, int index);
    void   putShortBAt(short value, int index);

    int    getIntL();
    int    getIntB();
    int    getIntLAt(int index);
    int    getIntBAt(int index);
    void   putIntL(int value);
    void   putIntB(int value);
    void   putIntLAt(int value, int index);
    void   putIntBAt(int value, int index);

    void   putFloatL(float value);
    void   putFloatB(float value);
    void   putFloatLAt(float value, int index);
    void   putFloatBAt(float value, int index);

    Long   getLongL();
    Long   getLongB();
    Long   getLongLAt(int index);
    Long   getLongBAt(int index);
    void   putLongL(Long value);
    void   putLongB(Long value);
    void   putLongLAt(Long value, int index);
    void   putLongBAt(Long value, int index);

    double getDoubleL();
    double getDoubleB();
    double getDoubleLAt(int index);
    double getDoubleBAt(int index);
    void   putDoubleL(double value);
    void   putDoubleB(double value);
    void   putDoubleLAt(double value, int index);
    void   putDoubleBAt(double value, int index);
    
    char * getStringL(int length);
    char * getStringB(int length);
    char * getStringLAt(int length, int index);
    char * getStringBAt(int length, int index);
    void   putStringL(const char *value, int length);
    void   putStringB(const char *value, int length);
    void   putStringLAt(const char *value, int length, int index);
    void   putStringBAt(const char *value, int length, int index);
};

#endif