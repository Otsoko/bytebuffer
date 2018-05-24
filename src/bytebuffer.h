#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <cstddef>

typedef unsigned char byte;

class ByteBuffer {

    byte *      buff;
    std::size_t size;
    int         pos;

public:
    ByteBuffer(std::size_t size);

    ~ByteBuffer();

    std::size_t getSize();

    void reset();

    byte *getBytes();

    byte get();

    byte getAt(int index);

    short getShort();

    short getShortAt(int index);

    int getInt();

    int getIntAt(int index);

    void put(byte value);

    void putAt(byte value, int index);

    void putShort(short value);

    void putShortAt(short value, int index);

    void putInt(int value);

    void putIntAt(int value, int index);

    char *getHexString();

    void getHexString(char *str);
};

#endif