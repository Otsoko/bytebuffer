#include "bytebuffer.h"
#include <cstddef>
#include <iostream>
#include <stdlib.h>

void        printBB(ByteBuffer *byteBuffer);
ByteBuffer *test(ByteBuffer *b);

void printHex(ByteBuffer *buffer) {
    char *hex = buffer->getHexString();
    printf("%s\n", hex);
    free(hex);
}

int main(int argc, char const *argv[]) {

    // Creamos el ByteBuffer con un tamaño de 9 bytes
    ByteBuffer bytebuffer(37);

    // Comprobamos que el tamaño es el que le hemos dado
    std::cout << "Tamaño del buffer: " << bytebuffer.getSize() << " bytes" << std::endl;

    bytebuffer.order(BB_LITTLE_ENDIAN);

    // Insertamos un byte
    bytebuffer.put(64);
    // Insertamos un byte
    bytebuffer.put(33);
    // Insertamos un byte
    bytebuffer.put(17);
    // Insertamos un short
    bytebuffer.putShort(345);
    // Insertamos un int
    bytebuffer.putInt(123456);
    // Insertamos un float
    bytebuffer.putFloat(82.56f);
    // Insertamos un long
    bytebuffer.putLong(12345678ULL);
    // Insertamos un double
    bytebuffer.putDouble(125.12563);
    // Insertamos una cadena
    bytebuffer.putString("Kaixop", 6);

    printBB(&bytebuffer);

    // Volvemos al principio del buffer para empezar a leer
    bytebuffer.reset();

    // Leemos un byte
    byte b1 = bytebuffer.get();
    // Leemos un byte
    byte b2 = bytebuffer.get();
    // Leemos un byte
    byte b3 = bytebuffer.get();
    // Leemos un short
    short s = bytebuffer.getShort();
    // Leemos un int
    int in = bytebuffer.getInt();
    // Leemos un float
    float f = bytebuffer.getFloat();
    // Leemos un long
    Long l = bytebuffer.getLong();
    // Leemos un double
    double d = bytebuffer.getDouble();
    // Leemos una cadena
    char *str = bytebuffer.getString(6);

    std::cout << std::fixed << "Valores leídos: " << (int) b1 << ", " << (int) b2 << ", "
              << (int) b3 << ", " << (int) s << ", " << (int) in << ", " << (float) f
              << ", " << (Long) l << ", " << (double) d << ", " << str << std::endl;

    free(str);

    // Insertamos un byte en la posición 2
    bytebuffer.putAt(44, 2);

    // Mostramos el contenido del ByteBuffer
    printBB(&bytebuffer);

    // Insertamos un short en la posición 2
    bytebuffer.putShortAt(55, 2);
    // Leemos un short en la posición 2
    std::cout << (int) bytebuffer.getShortAt(2) << std::endl;
    // Leemos un int en la posición 5
    std::cout << (int) bytebuffer.getIntAt(5) << std::endl;
    // Insertamos un int en la posición 2
    bytebuffer.putIntAt(78945, 2);
    // Leemos un int en la posición 2
    std::cout << (int) bytebuffer.getIntAt(2) << std::endl;
    // Insertamos un float en la posición 2
    bytebuffer.putFloatAt(123.45f, 2);
    // Leemos un float en la posición 2
    std::cout << (float) bytebuffer.getFloatAt(2) << std::endl;
    // Insertamos un long en la posición 2
    bytebuffer.putLongAt(789456123LL, 2);
    // Leemos un long en la posición 2
    std::cout << (Long) bytebuffer.getLongAt(2) << std::endl;
    // Insertamos un double en la posición 2
    bytebuffer.putDoubleAt(45678.456123, 2);
    // Leemos un double en la posición 2
    std::cout << std::fixed << bytebuffer.getDoubleAt(2) << std::endl;
    // Insertamos una cadena en la posición 2
    bytebuffer.putStringAt("Mundukorik politena", 19, 2);
    // Leemos una cadena en la posición 2
    str = bytebuffer.getStringAt(19, 2);
    std::cout << str << std::endl;
    free(str);

    byte *bytes = bytebuffer.getBytes();
    for (size_t i = 0; i < bytebuffer.getSize(); i++) {
        std::cout << (int) bytes[i] << " ";
    }
    std::cout << std::endl;

    char *hex1 = bytebuffer.getHexString();
    char  hex2[bytebuffer.getSize() * 2 + 1];

    bytebuffer.getHexString(hex2);

    std::cout << "HexString 1: " << hex1 << std::endl;
    std::cout << "HexString 2: " << hex2 << std::endl;

    // Liberar el devuelto
    free(hex1);

    // Creamos una copia del ByteBuffer
    ByteBuffer cloned = bytebuffer.clone();

    // Mostramos el contenido del ByteBuffer copiado
    printBB(&bytebuffer);
    printBB(&cloned);

    bytebuffer.putShort(123);
    cloned.putShort(123);

    printBB(&bytebuffer);
    printBB(&cloned);

    std::cout << std::endl
              << "s(int): " << sizeof(int) << ", s(long): " << sizeof(long)
              << ", s(long long): " << sizeof(long long)
              << ", s(float): " << sizeof(float) << ", s(double): " << sizeof(double)
              << ", s(u_int64_t): " << sizeof(uint64_t) << std::endl;

    ByteBuffer *r = NULL;
    r             = test(r);
    printBB(r);

    ByteBuffer bbstr("A3B2F1");
    printBB(&bbstr);

    return 0;
}

void printBB(ByteBuffer *byteBuffer) {
    // Mostramos el contenido del ByteBuffer
    for (size_t i = 0; i < byteBuffer->getSize(); i++) {
        std::cout << (int) byteBuffer->getAt(i) << " ";
    }
    std::cout << std::endl;
}

ByteBuffer *test(ByteBuffer *b) {
    b = new ByteBuffer(1);
    b->put(64);
    return b;
}