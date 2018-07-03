#include "bytebuffer.h"
#include <cstddef>
#include <iostream>
#include <stdlib.h>

using namespace std;

void        printBB(ByteBuffer *byteBuffer);
ByteBuffer *test(ByteBuffer *b);

int main(int argc, char const *argv[]) {

    // Creamos el ByteBuffer con un tamaño de 9 bytes
    ByteBuffer bytebuffer(35);

    // Comprobamos que el tamaño es el que le hemos dado
    cout << "Tamaño del buffer: " << bytebuffer.getSize() << " bytes" << endl;

    bytebuffer.order(BB_BIG_ENDIAN);

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

    cout << fixed << "Valores leídos: " << (int) b1 << ", " << (int) b2 << ", "
         << (int) b3 << ", " << (int) s << ", " << (int) in << ", " << (float) f
         << ", " << (Long) l << ", " << (double) d << ", " << str << endl;

    free(str);

    // Insertamos un byte en la posición 2
    bytebuffer.putAt(44, 2);

    // Mostramos el contenido del ByteBuffer
    printBB(&bytebuffer);

    // Insertamos un short en la posición 2
    bytebuffer.putShortAt(55, 2);
    // Leemos un short en la posición 2
    cout << (int) bytebuffer.getShortAt(2) << endl;
    // Leemos un int en la posición 5
    cout << (int) bytebuffer.getIntAt(5) << endl;
    // Insertamos un int en la posición 2
    bytebuffer.putIntAt(78945, 2);
    // Leemos un int en la posición 2
    cout << (int) bytebuffer.getIntAt(2) << endl;
    // Insertamos un float en la posición 2
    bytebuffer.putFloatAt(123.45f, 2);
    // Leemos un float en la posición 2
    cout << (float) bytebuffer.getFloatAt(2) << endl;
    // Insertamos un long en la posición 2
    bytebuffer.putLongAt(789456123LL, 2);
    // Leemos un long en la posición 2
    cout << (Long) bytebuffer.getLongAt(2) << endl;
    // Insertamos un double en la posición 2
    bytebuffer.putDoubleAt(45678.456123, 2);
    // Leemos un double en la posición 2
    cout << fixed << bytebuffer.getDoubleAt(2) << endl;
    // Insertamos una cadena en la posición 2
    bytebuffer.putStringAt("Mundukorik politena", 19, 2);
    // Leemos una cadena en la posición 2
    str = bytebuffer.getStringAt(19, 2);
    cout << str << endl;
    free(str);

    byte *bytes = bytebuffer.getBytes();
    for (size_t i = 0; i < bytebuffer.getSize(); i++) {
        cout << (int) bytes[i] << " ";
    }
    cout << endl;

    char *hex1 = bytebuffer.getHexString();
    char  hex2[bytebuffer.getSize() * 2 + 1];

    bytebuffer.getHexString(hex2);

    cout << "HexString 1: " << hex1 << endl;
    cout << "HexString 2: " << hex2 << endl;

    // Liberar el devuelto
    free(hex1);

    // Creamos una copia del ByteBuffer
    ByteBuffer cloned = bytebuffer.clone();

    // Mostramos el contenido del ByteBuffer copiado
    printBB(&cloned);

    cout << endl
         << "s(int): " << sizeof(int) << ", s(long): " << sizeof(long)
         << ", s(long long): " << sizeof(long long)
         << ", s(float): " << sizeof(float) << ", s(double): " << sizeof(double)
         << ", s(u_int64_t): " << sizeof(u_int64_t) << endl;

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
        cout << (int) byteBuffer->getAt(i) << " ";
    }
    cout << endl;
}

ByteBuffer *test(ByteBuffer *b) {
    b = new ByteBuffer(1);
    b->put(64);
    return b;
}