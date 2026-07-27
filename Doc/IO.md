# IO

IO is a platform independent Input/Output component with advanced serialization.

## Primitives

The component provides a number of useful primitive tools for binary serialization:

* `ISeekableStream` - An interface extending the primitive `Ag::IStream` that allows
the caller to reposition within a stream and have a concept of size and extent.
* `StreamRegion` - A data type which can be used to define a block of bytes within
a seekable stream.
* `BufferedInputStream` - An implementation of `IStream` which provides a buffer
of configurable size layered on top of an `IStream` implementation in order to
batch reads.
* `BufferedOutputStream` - An implementation of `IStream` which provides a buffer
of configurable size layered on top of an `IStream` implementation in order to
batch writes.
* `SeekableFileStream` - A platform independent wrapper around lowest-level
system file manipulation system calls. This can be combined with
BufferedInputStream and BufferedOutputStream to provide efficient I/O performance.
* `MemoryStream` - An `ISeekableStream` implementation backed by RAM, but not a
costly single linear block of memory.
* `MemoryMappedFile` - An platform independent wrapper around file mapping APIs
that allow a file to be read or written as if it were addressable memory.
* `copyStream()` - Utility functions for efficiently copying data between streams.

## Hierarchy Serialization

The IO component also contains tools for reading and writing structured hierarchies
of data as you might in JSON or XML, but in an efficient binary format which can
even be seamlessly compressed.

Individual values are efficiently encoded to require the minimum possible storage
before any compression is applied. The semantics of the value are encoded rather
than the actual value. For example, a double value of 1.0 could be thoughtlessly
stored as 8 bytes, but using hierarchy serialization is stored as a single byte
indicating that the storage is a small positive integer encoding a value of 1.

When reading back that value, it can be interpreted as an integer of any size, a
boolean, a Unicode character or a floating point scalar. However, if the
serialization code wrote the value as 1.0 and reads back a double value, it will
receive 1.0.

String values written to a serialization hierarchy are consolidated into a
dictionary so that each string is only stored once, no matter how often it is
used.

Individual values are either stored anonymously in a linear collection, or as
named properties of an object - which is essentially a set of key/value pairs.
Collection elements or object properties can themselves be nested collections
or objects, just as if they have been expressed using JSON or XML.

### Serializing a Hierarchy

To serialize a hierarchy with property set at its root, create an instance of
`Ag::IO::ObjectWriter`. To serialize with a collection root, create an instance
of `Ag::IO::ArrayWriter`. Values and nested data can be recorded to these objects
and those they spawn for their entire lifetime. When the writer object goes out
of scope, all the data recorded is written to the output stream passed to the
constructor.

``` C++
if (doWrite)
{
    ObjectWriter writer(myOutputStream, /* compress */ = true)
    writer.write("First", 1);
    writer.write("Second", 3.0);

    // Write out a field as a stream of bytes.
    if (IStreamUPtr fieldStream = writer.beginWriteBytes("Third"))
    {
        copyStream(fieldStream.get(), myOtherStream);
    } // The stream is disposed of at the end of the lexical scope.

    writer.write("Fourth", "IAmNumberFour");

} // The writer is destroyed at the end of the lexical scope
  //    at which point, all the data is written to myOutputStream.
```

The data is written out-of-order to temporary storage and then streamed out in
the correct order to the original output stream when writing is complete. The
result is a binary structure that is easy to read in as a single non-seekable
stream, such as from a network socket. Each object is proceeded by a header
that defines how big it is and this can be skipped if necessary.

All data is written with 64-bit sizes, even on a 32-bit platform, so that the
hierarchy can be used to package other files.

## Deserializing a Hierarchy

To deserialize a hierarchy previously serialized with `ObjectWriter` or
`ArrayWriter`, instantiate a `Ag::IO::HierarchyRoot` object and pass a stream
to its constructor. The `HierarchyRoot` will then be able to tell the caller
whether the root item is an object or an array and provide access to that
root item via an `Ag::IO::ObjectReader` or `Ag::IO::ArrayReader`.

When the `HierarchyRoot` object is initially created, the data from the stream
is read, possibly decompressed and copied to a memory buffer or a temporary
file, depending on the size. If a file is used, the contents of the file are
mapped into memory. Objects and Arrays can then be read randomly.

```C++
// Note: The root will determine if the stream is compressed
//   and decompress it.
HierarchyRoot root(myInputStream);

if (root.hasRootObject())
{
    ObjectReader reader = root.getRootObject();

    int first = reader.readInt("First");
    double second = reader.readDouble("Second");

    if (IStreamUPtr fieldStream = reader.readBytesStream("Third"))
    {
        // ...
    }

    Ag::String fourth;
    if (reader.tryRead("Fourth", fourth))
    {
        // ...
    }
}
```
The lifetime of the unpacked hierarchy matches that of the `HierarchyRoot` instance.
the temporary buffer or file is disposed of when the object is destroyed.