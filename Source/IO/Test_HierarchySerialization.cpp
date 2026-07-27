//! @file IO/Test_HierarchySerialzation.cpp
//! @brief The definition of unit tests for the Object/Array/Reader/Writer classes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/IO/HierarchySerialization.hpp"
#include "Ag/IO/MemoryStream.hpp"

#include "TestTools.hpp"

namespace Ag {
namespace IO {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
struct SampleData
{
    // Public Constants
    static constexpr size_t BlockSize = 4 * 1024;
    static constexpr size_t MaxBlockSize = 4 * 1024 * 1024;
    static constexpr size_t StreamSize = 64 * 1024;
    static constexpr size_t MaxStreamSize = 16 * 1024 * 1024;
    static constexpr size_t StreamTransferSize = 4096;

    // Public Types
    using UPtr = std::unique_ptr<SampleData>;
    using Collection = std::vector<UPtr>;

    // Public Fields
    bool BoolValue;
    int8_t Int8Value;
    uint8_t Uint8Value;
    int16_t Int16Value;
    uint16_t Uint16Value;
    int32_t Int32Value;
    uint32_t Uint32Value;
    int64_t Int64Value;
    uint64_t Uint64Value;
    char32_t CharValue;
    float FloatValue;
    double DoubleValue;
    String TextValue;
    ByteBlock BlockValue;
    ByteBlock StreamValue;

    UPtr Child;
    Collection Children;

    // Construction
    SampleData() :
        BoolValue(false),
        Int8Value(0),
        Uint8Value(0),
        Int16Value(0),
        Uint16Value(0),
        Int32Value(0),
        Uint32Value(0),
        Int64Value(0),
        Uint64Value(0),
        CharValue(U'\0'),
        FloatValue(0.0f),
        DoubleValue(0.0),
        TextValue(String::Empty)
    {
    }

    SampleData(const SampleData &rhs)
    {
        clone(rhs);
    }

    void clone(const SampleData &rhs)
    {
        // Reset the state of the object.
        Child.reset();
        Children.clear();

        // Copy fields
        BoolValue = rhs.BoolValue;
        Int8Value = rhs.Int8Value;
        Uint8Value = rhs.Uint8Value;
        Int16Value = rhs.Int16Value;
        Uint16Value = rhs.Uint16Value;
        Int32Value = rhs.Int32Value;
        Uint32Value = rhs.Uint32Value;
        Int64Value = rhs.Int64Value;
        Uint64Value = rhs.Uint64Value;
        CharValue = rhs.CharValue;
        FloatValue = rhs.FloatValue;
        DoubleValue = rhs.DoubleValue;
        TextValue = rhs.TextValue;
        BlockValue = rhs.BlockValue;
        StreamValue = rhs.StreamValue;

        // Copy the named child.
        if (rhs.Child)
        {
            Child = std::make_unique<SampleData>(*rhs.Child);
        }

        // Copy anonymous children.
        if (rhs.Children.empty() == false)
        {
            Children.reserve(rhs.Children.size());

            for (const auto &child : rhs.Children)
            {
                Children.push_back(std::make_unique<SampleData>(*child));
            }
        }
    }

    void makeEmpty()
    {
        BoolValue = false;
        Int8Value = 0;
        Uint8Value = 0;
        Int16Value = 0;
        Uint16Value = 0;
        Int32Value = 0;
        Uint32Value = 0;
        Int64Value = 0;
        Uint64Value = 0;
        CharValue = U'\0';
        FloatValue = 0.0f;
        DoubleValue = 0.0;
        TextValue = String::Empty;
        BlockValue.clear();
        StreamValue.clear();

        Child.reset();
        Children.clear();
    }

    void makeMinimum()
    {
        BoolValue = false;
        Int8Value = std::numeric_limits<decltype(Int8Value)>::min();
        Uint8Value = std::numeric_limits<decltype(Uint8Value)>::min();
        Int16Value = std::numeric_limits<decltype(Int16Value)>::min();
        Uint16Value = std::numeric_limits<decltype(Uint16Value)>::min();
        Int32Value = std::numeric_limits<decltype(Int32Value)>::min();
        Uint32Value = std::numeric_limits<decltype(Uint32Value)>::min();
        Int64Value = std::numeric_limits<decltype(Int64Value)>::min();
        Uint64Value = std::numeric_limits<decltype(Uint64Value)>::min();
        CharValue = std::numeric_limits<decltype(CharValue)>::min();
        FloatValue = std::numeric_limits<decltype(FloatValue)>::min();
        DoubleValue = std::numeric_limits<decltype(DoubleValue)>::min();
        TextValue = "A";
        BlockValue.clear();
        BlockValue.push_back(0xA5);
        StreamValue.clear();
        StreamValue.push_back(0x5A);
    }

    void makeMaximum()
    {
        RandomByteGenerator generator(255);

        size_t textLength = generator.nextValue<uint32_t>() % (1024 * 1024);

        BoolValue = true;
        Int8Value = std::numeric_limits<decltype(Int8Value)>::max();
        Uint8Value = std::numeric_limits<decltype(Uint8Value)>::max();
        Int16Value = std::numeric_limits<decltype(Int16Value)>::max();
        Uint16Value = std::numeric_limits<decltype(Uint16Value)>::max();
        Int32Value = std::numeric_limits<decltype(Int32Value)>::max();
        Uint32Value = std::numeric_limits<decltype(Uint32Value)>::max();
        Int64Value = std::numeric_limits<decltype(Int64Value)>::max();
        Uint64Value = std::numeric_limits<decltype(Uint64Value)>::max();
        CharValue = std::numeric_limits<decltype(CharValue)>::max();
        FloatValue = std::numeric_limits<decltype(FloatValue)>::max();
        DoubleValue = std::numeric_limits<decltype(DoubleValue)>::max();
        TextValue = generator.nextString(textLength);

        BlockValue.clear();
        BlockValue.reserve(BlockSize);
        std::generate_n(std::back_inserter(BlockValue), MaxBlockSize, generator);

        StreamValue.clear();
        StreamValue.reserve(StreamSize);
        std::generate_n(std::back_inserter(StreamValue), MaxStreamSize, generator);
    }

    void makeRandom(RandomByteGenerator &generator,
                    bool generateChild = false,
                    size_t generateChildCount = 0)
    {
        // Reset the state of the object.
        Child.reset();
        Children.clear();

        // Generate field values.
        BoolValue = generator() > 128;
        Int8Value = generator.nextValue<int8_t>();
        Uint8Value = generator();
        Int16Value = generator.nextValue<int16_t>();
        Uint16Value = generator.nextValue<uint16_t>();
        Int32Value = generator.nextValue<int32_t>();
        Uint32Value = generator.nextValue<uint32_t>();
        Int64Value = generator.nextValue<int64_t>();
        Uint64Value = generator.nextValue<uint64_t>();
        CharValue = static_cast<char32_t>(generator.nextValue<uint8_t>() + 32);
        FloatValue = generator.nextValue<float>();
        DoubleValue = generator.nextValue<double>();
        TextValue = generator.nextString();

        size_t blockSize = generator.nextValue<size_t>() % BlockSize;
        BlockValue.clear();
        BlockValue.reserve(blockSize);
        std::generate_n(std::back_inserter(BlockValue), blockSize, generator);

        size_t streamSize = generator.nextValue<size_t>() % StreamSize;
        StreamValue.clear();
        StreamValue.reserve(blockSize);
        std::generate_n(std::back_inserter(StreamValue), streamSize, generator);

        if (generateChild)
        {
            // Generate a named child.
            Child = std::make_unique<SampleData>();
            Child->makeRandom(generator, false, 0);
        }

        if (generateChildCount > 0)
        {
            // Generate anonymous children.
            Children.reserve(generateChildCount);

            for (size_t i = 0; i < generateChildCount; ++i)
            {
                Children.push_back(std::make_unique<SampleData>());
                Children.back()->makeRandom(generator, false, 0);
            }
        }
    }

    void write(ObjectWriter &writer) const
    {
        // Write fields.
        writer.write("BoolValue", BoolValue);
        writer.write("Int8Value", Int8Value);
        writer.write("Uint8Value", Uint8Value);
        writer.write("Int16Value", Int16Value);
        writer.write("Uint16Value", Uint16Value);
        writer.write("Int32Value", Int32Value);
        writer.write("Uint32Value", Uint32Value);
        writer.write("Int64Value", Int64Value);
        writer.write("Uint64Value", Uint64Value);
        writer.write("CharValue", CharValue);
        writer.write("FloatValue", FloatValue);
        writer.write("DoubleValue", DoubleValue);
        writer.write("TextValue", TextValue);
        writer.write("BlockValue", BlockValue.data(), BlockValue.size());
        writeStreamValue(writer.beginWriteBytes("StreamValue"));

        // Write Child/Children.
        if (Child)
        {
            ObjectWriter childWriter = writer.beginWriteObject("Child");

            Child->write(childWriter);
        }

        if (Children.empty() == false)
        {
            ArrayWriter childrenWriter = writer.beginWriteArray("Children");

            for (const auto &childPtr : Children)
            {
                ObjectWriter childWriter = childrenWriter.beginWriteObject();

                childPtr->write(childWriter);
            }
        }
    }

    void write(ArrayWriter &writer) const
    {
        // Write fields.
        writer.write(BoolValue);
        writer.write(Int8Value);
        writer.write(Uint8Value);
        writer.write(Int16Value);
        writer.write(Uint16Value);
        writer.write(Int32Value);
        writer.write(Uint32Value);
        writer.write(Int64Value);
        writer.write(Uint64Value);
        writer.write(CharValue);
        writer.write(FloatValue);
        writer.write(DoubleValue);
        writer.write(TextValue);
        writer.write(BlockValue.data(), BlockValue.size());
        writeStreamValue(writer.beginWriteBytes());

        // Write Child/Children.

        // Write bool to indicate if the Child property follows.
        if (Child)
        {
            writer.write(true);
            ObjectWriter childWriter = writer.beginWriteObject();

            Child->write(childWriter);
        }
        else
        {
            writer.write(false);
        }

        if (Children.empty() == false)
        {
            for (const auto &childPtr : Children)
            {
                ObjectWriter childWriter = writer.beginWriteObject();

                childPtr->write(childWriter);
            }
        }
    }

    void read(const ObjectReader &reader)
    {
        Child.reset();
        Children.clear();

        BoolValue = reader.readBool("BoolValue");
        Int8Value = reader.readInt8("Int8Value");
        Uint8Value = reader.readUint8("Uint8Value");
        Int16Value = reader.readInt16("Int16Value");
        Uint16Value = reader.readUint16("Uint16Value");
        Int32Value = reader.readInt32("Int32Value");
        Uint32Value = reader.readUint32("Uint32Value");
        Int64Value = reader.readInt64("Int64Value");
        Uint64Value = reader.readUint64("Uint64Value");
        CharValue = reader.readChar("CharValue");
        FloatValue = reader.readFloat("FloatValue");
        DoubleValue = reader.readDouble("DoubleValue");
        TextValue = reader.readString("TextValue");
        BlockValue = reader.readBytes("BlockValue");
        readStreamValue(reader.readBytesStream("StreamValue"));

        // Read Child/Children.
        ObjectReader childReader;
        ArrayReader childrenReader;

        if (reader.tryRead("Child", childReader))
        {
            Child = std::make_unique<SampleData>();
            Child->read(childReader);
        }

        if (reader.tryRead("Children", childrenReader))
        {
            Children.reserve(static_cast<size_t>(childrenReader.getElementCount()));

            while (childrenReader.hasMore())
            {
                childReader = childrenReader.readNextObject();

                Children.push_back(std::make_unique<SampleData>());
                Children.back()->read(childReader);
            }
        }
    }

    void read(ArrayReader &reader)
    {
        Child.reset();
        Children.clear();

        BoolValue = reader.readNextBool();
        Int8Value = reader.readNextInt8();
        Uint8Value = reader.readNextUint8();
        Int16Value = reader.readNextInt16();
        Uint16Value = reader.readNextUint16();
        Int32Value = reader.readNextInt32();
        Uint32Value = reader.readNextUint32();
        Int64Value = reader.readNextInt64();
        Uint64Value = reader.readNextUint64();
        CharValue = reader.readNextChar();
        FloatValue = reader.readNextFloat();
        DoubleValue = reader.readNextDouble();
        TextValue = reader.readNextString();
        BlockValue = reader.readNextBytes();
        readStreamValue(reader.readNextByteStream());

        // Read Child/Children.
        ObjectReader childReader;

        // Read bool field to determine of the child is written.
        if (reader.readNextBool())
        {
            childReader = reader.readNextObject();

            Child = std::make_unique<SampleData>();
            Child->read(childReader);
        }

        Children.reserve(static_cast<size_t>(reader.getElementCount() - reader.getCurrentElementIndex()));

        while (reader.hasMore())
        {
            childReader = reader.readNextObject();

            Children.push_back(std::make_unique<SampleData>());
            Children.back()->read(childReader);
        }
    }

    bool isEqual(const SampleData &rhs) const
    {
        if ((BoolValue == rhs.BoolValue) &&
            (Int8Value == rhs.Int8Value) &&
            (Uint8Value == rhs.Uint8Value) &&
            (Int16Value == rhs.Int16Value) &&
            (Uint16Value == rhs.Uint16Value) &&
            (Int32Value == rhs.Int32Value) &&
            (Uint32Value == rhs.Uint32Value) &&
            (Int64Value == rhs.Int64Value) &&
            (Uint64Value == rhs.Uint64Value) &&
            (CharValue == rhs.CharValue) &&
            (FloatValue == rhs.FloatValue) &&
            (DoubleValue == rhs.DoubleValue) &&
            (TextValue == rhs.TextValue) &&
            isEqual(BlockValue, rhs.BlockValue) &&
            isEqual(StreamValue, rhs.StreamValue) &&
            isEqual(Child, rhs.Child) &&
            (Children.size() == rhs.Children.size()))
        {
            for (size_t i = 0; i < Children.size(); ++i)
            {
                if (isEqual(Children.at(i), rhs.Children.at(i)) == false)
                    return false;
            }

            return true;
        }

        return false;
    }

    void writeStreamValue(IStreamUPtr valueStream) const
    {
        size_t bytesWritten = 0;

        while (bytesWritten < StreamValue.size())
        {
            size_t bytesToWrite = std::min(StreamValue.size() - bytesWritten,
                                           StreamTransferSize);

            size_t written = valueStream->write(StreamValue.data() + bytesWritten,
                                                bytesToWrite);

            if (written != bytesToWrite)
                throw IOException("Failed to write stream value.");

            bytesWritten += written;
        }
    }

    void readStreamValue(ISeekableStreamUPtr valueStream)
    {
        StreamValue.clear();
        StreamValue.reserve(static_cast<size_t>(valueStream->getLength()));

        size_t bytesRead = 0;

        do
        {
            size_t oldSize = StreamValue.size();
            size_t newSize = oldSize + StreamTransferSize;

            StreamValue.resize(newSize);

            bytesRead = valueStream->read(StreamValue.data() + oldSize,
                                          StreamTransferSize);

            newSize = oldSize + bytesRead;

            if (bytesRead < StreamTransferSize)
                StreamValue.resize(newSize);

            // Continue until we make a partial transfer.
        } while (bytesRead == StreamTransferSize);
    }

    static bool isEqual(const ByteBlock &lhs, const ByteBlock &rhs)
    {
        if (lhs.size() == rhs.size())
        {
            return std::memcmp(lhs.data(), rhs.data(), lhs.size()) == 0;
        }

        return false;
    }

    static bool isEqual(const UPtr &lhs, const UPtr &rhs)
    {
        if (lhs && rhs)
        {
            // Check for the same instance.
            if (lhs.get() == rhs.get())
                return true;

            return lhs->isEqual(*rhs);
        }

        return !lhs && !rhs;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(HierarchySerialization, A00_SampleData)
{
    SampleData sample1, sample2;

    // Compare empty objects.
    EXPECT_TRUE(sample1.isEqual(sample2));
    EXPECT_TRUE(sample1.isEqual(sample1));
    EXPECT_TRUE(sample2.isEqual(sample2));
    EXPECT_TRUE(sample2.isEqual(sample1));

    // Populate one object.
    RandomByteGenerator entropySource(12);
    sample2.makeRandom(entropySource);

    // Compare empty/non-empty.
    EXPECT_FALSE(sample1.isEqual(sample2));
    EXPECT_TRUE(sample2.isEqual(sample2));

    // Generate a child.
    sample1.makeRandom(entropySource, true);
    EXPECT_TRUE(sample1.Child);
    EXPECT_EQ(sample1.Children.size(), 0u);

    // Clone the result and compare.
    sample2.clone(sample1);
    EXPECT_TRUE(sample2.isEqual(sample1));
    EXPECT_NE(sample2.Child.get(), sample1.Child.get());

    // Generate anonymous children.
    sample2.makeRandom(entropySource, false, 3);

    EXPECT_FALSE(sample2.Children.empty());
    EXPECT_FALSE(sample2.isEqual(sample1));

    // Clone the result.
    sample1.clone(sample2);
    EXPECT_TRUE(sample1.isEqual(sample2));
}

GTEST_TEST(HierarchySerialization, A01_WriteEmptyObject)
{
    MemoryStream dataSource;

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ObjectWriter writer = beginSerializeObject(&dataSource, false);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);
}

GTEST_TEST(HierarchySerialization, A01_WriteEmptyArray)
{
    MemoryStream dataSource;

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ArrayWriter writer = beginSerializeArray(&dataSource, false);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);
}

GTEST_TEST(HierarchySerialization, A02_ReadEmptyObject)
{
    MemoryStream dataSource;

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ObjectWriter writer = beginSerializeObject(&dataSource, false);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    EXPECT_FALSE(root.hasRootArray());
    ASSERT_TRUE(root.hasRootObject());

    ObjectReader specimen = root.getRootObject();

    String propValue;
    EXPECT_TRUE(specimen.isBound());
    EXPECT_FALSE(specimen.tryRead("MyValue", propValue));
    EXPECT_FALSE(specimen.hasProperty("YourValue"));
}

GTEST_TEST(HierarchySerialization, A02_ReadEmptyArray)
{
    MemoryStream dataSource;

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ArrayWriter writer = beginSerializeArray(&dataSource, false);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootArray());
    EXPECT_FALSE(root.hasRootObject());

    ArrayReader specimen = root.getRootArray();

    EXPECT_TRUE(specimen.isBound());
    EXPECT_EQ(specimen.getCurrentElementIndex(), 0);
    EXPECT_FALSE(specimen.hasMore());
    EXPECT_EQ(specimen.getElementCount(), 0);
}

GTEST_TEST(HierarchySerialization, A03_ReadMinObject)
{
    MemoryStream dataSource;
    SampleData original;

    original.makeMinimum();

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ObjectWriter writer = beginSerializeObject(&dataSource, false);

        original.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootObject());

    ObjectReader specimen = root.getRootObject();
    SampleData readData;
    readData.read(specimen);

    EXPECT_TRUE(readData.isEqual(original));
}

GTEST_TEST(HierarchySerialization, A03_ReadMinArray)
{
    MemoryStream dataSource;
    SampleData originalData;

    originalData.makeMinimum();

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ArrayWriter writer = beginSerializeArray(&dataSource, false);

        originalData.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootArray());
    ArrayReader specimen = root.getRootArray();
    SampleData readData;

    readData.read(specimen);
    EXPECT_TRUE(readData.isEqual(originalData));
}

GTEST_TEST(HierarchySerialization, A03_ReadMaxObject)
{
    MemoryStream dataSource;
    SampleData original;

    original.makeMaximum();

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ObjectWriter writer = beginSerializeObject(&dataSource, false);

        original.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootObject());

    ObjectReader specimen = root.getRootObject();
    SampleData readData;
    readData.read(specimen);

    EXPECT_TRUE(readData.isEqual(original));
}

GTEST_TEST(HierarchySerialization, A03_ReadMaxArray)
{
    MemoryStream dataSource;
    SampleData originalData;

    originalData.makeMaximum();

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ArrayWriter writer = beginSerializeArray(&dataSource, false);

        originalData.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootArray());
    ArrayReader specimen = root.getRootArray();
    SampleData readData;

    readData.read(specimen);
    EXPECT_TRUE(readData.isEqual(originalData));
}

GTEST_TEST(HierarchySerialization, A03_ReadRandomObject)
{
    RandomByteGenerator entropySource(6);
    MemoryStream dataSource;
    SampleData original;

    original.makeRandom(entropySource);

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ObjectWriter writer = beginSerializeObject(&dataSource, false);

        original.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootObject());

    ObjectReader specimen = root.getRootObject();
    SampleData readData;
    readData.read(specimen);

    EXPECT_TRUE(readData.isEqual(original));
}

GTEST_TEST(HierarchySerialization, A03_ReadRandomArray)
{
    RandomByteGenerator entropySource(14);
    MemoryStream dataSource;
    SampleData originalData;

    originalData.makeRandom(entropySource);

    if (dataSource.getPosition() == 0)
    {
        // Ensure the writer is in a lexical scope so that
        // serialization completes at exit.
        ArrayWriter writer = beginSerializeArray(&dataSource, false);

        originalData.write(writer);
    }
    else
    {
        FAIL() << "Data source non-empty.";
    }

    EXPECT_GT(dataSource.getSize(), 0);

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootArray());
    ArrayReader specimen = root.getRootArray();
    SampleData readData;

    readData.read(specimen);
    EXPECT_TRUE(readData.isEqual(originalData));
}

GTEST_TEST(HierarchySerialization, A04_WriteNestedObject)
{
    RandomByteGenerator entropySource(37);
    MemoryStream dataSource;
    SampleData original;

    original.makeRandom(entropySource, true);
    ObjectWriter writer = beginSerializeObject(&dataSource, false);

    original.write(writer);

    // Ensure the writer is closed to simulate destruction.
    writer.close();

    EXPECT_GT(dataSource.getSize(), 0);
}

GTEST_TEST(HierarchySerialization, A04_WriteNestedArray)
{
    RandomByteGenerator entropySource(14);
    MemoryStream dataSource;
    SampleData originalData;
    constexpr size_t ChildCount = 3;

    originalData.makeRandom(entropySource, false, ChildCount);
    ArrayWriter writer = beginSerializeArray(&dataSource, false);

    originalData.write(writer);

    // Ensure the writer is closed to simulate destruction.
    writer.close();

    EXPECT_GT(dataSource.getSize(), 0);
}

GTEST_TEST(HierarchySerialization, A05_ReadNestedObject)
{
    RandomByteGenerator entropySource(37);
    MemoryStream dataSource;
    SampleData original;

    original.makeRandom(entropySource, true);

    ObjectWriter writer = beginSerializeObject(&dataSource, false);

    original.write(writer);

    // Ensure the writer is closed to simulate destruction.
    writer.close();

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootObject());

    ObjectReader specimen = root.getRootObject();
    SampleData readData;
    readData.read(specimen);

    EXPECT_TRUE(readData.Child);
    EXPECT_TRUE(readData.isEqual(original));
}

GTEST_TEST(HierarchySerialization, A05_ReadNestedArray)
{
    RandomByteGenerator entropySource(14);
    MemoryStream dataSource;
    SampleData originalData;
    constexpr size_t ChildCount = 3;

    originalData.makeRandom(entropySource, false, ChildCount);

    ArrayWriter writer = beginSerializeArray(&dataSource, false);

    originalData.write(writer);

    // Ensure the writer is closed to simulate destruction.
    writer.close();

    // Reset the stream back to the beginning.
    dataSource.setPosition(StreamRelative::Beginning, 0);

    HierarchyRoot root(&dataSource);

    ASSERT_TRUE(root.hasRootArray());
    ArrayReader specimen = root.getRootArray();
    SampleData readData;

    readData.read(specimen);
    EXPECT_EQ(readData.Children.size(), ChildCount);
    EXPECT_TRUE(readData.isEqual(originalData));
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

