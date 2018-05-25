# ByteBuffer #
ByteBuffer implementation on C++

## How to use ##

```c++
// Create a ByteBuffer of a given size in bytes
ByteBuffer bytebuffer(11);

// Insert data at the current position
bytebuffer.put(64);
bytebuffer.putShort(256);
bytebuffer.putInt(3645);
bytebuffer.putFloat(123.45f);

// Insert data at a certain position
bytebuffer.putAt(64, 0);
bytebuffer.putShortAt(256, 1);
bytebuffer.putIntAt(3645, 3);
bytebuffer.putFloatAt(123.45f, 7);

// Reset the current position to the beggining
bytebuffer.reset();

// Read data at the current position
bytebuffer.get();
bytebuffer.getShort();
bytebuffer.getInt();
bytebuffer.getFloat();

// Read data at a certain position
bytebuffer.getAt(0);
bytebuffer.getShortAt(1);
bytebuffer.getIntAt(3);
bytebuffer.getFloatAt(7);

// Get the bytes array
byte *bytes = bytebuffer.getBytes();

// Print the hex string
char *hex = bytebuffer.getHexString();
std::cout << "HexString: " << hex << std::endl;
free(hex);

// Clone the ByteBuffer
ByteBuffer cloned = bytebuffer.clone();
```