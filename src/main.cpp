#include "bytebuffer.h"
#include <cstddef>
#include <iostream>
#include <stdlib.h>

using namespace std;

void printBB(ByteBuffer *byteBuffer);

int main(int argc, char const *argv[]) {

    // Creamos el ByteBuffer con un tamaño de 9 bytes
    ByteBuffer bytebuffer(13);

    // Comprobamos que el tamaño es el que le hemos dado
    cout << "Tamaño del buffer: " << bytebuffer.getSize() << " bytes" << endl;

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

    // Volvemos al principio del buffer para empezar a leer
    bytebuffer.reset();

    // Leemos un byte
    byte b = bytebuffer.get();
    // Leemos un byte
    byte c = bytebuffer.get();
    // Leemos un byte
    byte d = bytebuffer.get();
    // Leemos un short
    short s = bytebuffer.getShort();
    // Leemos un int
    int in = bytebuffer.getInt();
    // Leemos un float
    float f = bytebuffer.getFloat();

    cout << "Valores leídos: " << (int) b << ", " << (int) c << ", " << (int) d
         << ", " << (int) s << ", " << (int) in << ", " << (float) f << endl;

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

    return 0;
}

void printBB(ByteBuffer *byteBuffer) {
    // Mostramos el contenido del ByteBuffer
    for (size_t i = 0; i < byteBuffer->getSize(); i++) {
        cout << (int) byteBuffer->getAt(i) << " ";
    }
    cout << endl;
}