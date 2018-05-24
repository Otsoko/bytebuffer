# ByteBuffer #
ByteBuffer implementation on C++

## How to use ##

```c++
// Create a ByteBuffer of a given size in bytes
ByteBuffer bytebuffer(7);

// Insert data at the current position
bytebuffer.put(64);
bytebuffer.putShort(256);
bytebuffer.putInt(3645);

// Insert data at a certain position
bytebuffer.putAt(64, 0);
bytebuffer.putShortAt(256, 1);
bytebuffer.putIntAt(3645, 3);

// Reset the current position to the beggining
bytebuffer.reset();

// Read data at the current position
bytebuffer.get();
bytebuffer.getShort();
bytebuffer.getInt();

// Read data at a certain position
bytebuffer.getAt(0);
bytebuffer.getShortAt(1);
bytebuffer.getIntAt(3);

// Get the bytes array
byte *bytes = bytebuffer.getBytes();

// Print the hex string
std::cout << "HexString: " << bytebuffer.getHexString() << std::endl;
```