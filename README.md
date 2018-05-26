# ByteBuffer #
ByteBuffer implementation on C++

- `byte` type is `typedef unsigned char byte` (1 byte)
- `Long` type is `typedef long long Long` (8 bytes)

## How to use ##

```c++
// Create a ByteBuffer of a given size in bytes
ByteBuffer bytebuffer(19);

// Insert data at the current position
bytebuffer.put(64);              // 1 byte
bytebuffer.putShort(256);        // 2 bytes
bytebuffer.putInt(3645);         // 4 bytes
bytebuffer.putFloat(123.45f);    // 4 bytes
bytebuffer.putLong(123456789LL); // 8 bytes

// Insert data at a certain position
bytebuffer.putAt(64, 0);
bytebuffer.putShortAt(256, 1);
bytebuffer.putIntAt(3645, 3);
bytebuffer.putFloatAt(123.45f, 7);
bytebuffer.putLong(123456789LL, 11);

// Reset the current position to the beggining
bytebuffer.reset();

// Read data at the current position
bytebuffer.get();
bytebuffer.getShort();
bytebuffer.getInt();
bytebuffer.getFloat();
bytebuffer.getLong();

// Read data at a certain position
bytebuffer.getAt(0);
bytebuffer.getShortAt(1);
bytebuffer.getIntAt(3);
bytebuffer.getFloatAt(7);
bytebuffer.getLongAt(11);

// Get the bytes array
byte *bytes = bytebuffer.getBytes();

// Print the hex string
char *hex = bytebuffer.getHexString();
std::cout << "HexString: " << hex << std::endl;
free(hex);

// Clone the ByteBuffer
ByteBuffer cloned = bytebuffer.clone();
```