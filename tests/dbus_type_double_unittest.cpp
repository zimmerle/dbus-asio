#include "test_unmarshall.h"
#include "dbus_type_double.h"
#include "dbus_messageprotocol.h"
#include "dbus_messageostream.h"

namespace DBus { namespace test {

void TestUnmarshallFromMessageIStream(Type::Double& dbusType, double value, unsigned byteOrder)
{
    uint64_t u = *reinterpret_cast<uint64_t *>(&value);

    // __FLOAT_WORD_ORDER__ is the same as __BYTE_ORDER__ on almost
    // everything in the world. We only swap or not so we couldn't
    // cope if it is not. Let's use __FLOAT_WORD_ORDER__ here so at
    // least this test will fail in that case.
    if (byteOrder != __FLOAT_WORD_ORDER__)
        u = __bswap_64(u);

    MessageIStream stream((uint8_t*)&u, sizeof(u), byteOrder != __BYTE_ORDER);
    dbusType.unmarshall(stream);

    std::stringstream ss;
    ss << value;
    REQUIRE(dbusType.asString() == ss.str());
}

TEST_CASE("Unmarshall double little endian from MessageIStream")
{
    Type::Double dbusType;
    TestUnmarshallFromMessageIStream(dbusType, 5346.12, __LITTLE_ENDIAN);
}

TEST_CASE("Unmarshall double big endian from MessageIStream")
{
    Type::Double dbusType;
    TestUnmarshallFromMessageIStream(dbusType, 67.25, __BIG_ENDIAN);
}

TEST_CASE("Marshall and unmarshall double")
{
    MessageOStream stream;
    double value = 1.2234;
    stream.writeDouble(value);

    Type::Double dbusType;
    MessageIStream istream((uint8_t*)stream.data.data(), stream.size(), false);
    dbusType.unmarshall(istream);

    std::stringstream ss;
    ss << value;
    REQUIRE(dbusType.asString() == ss.str());
}


}} // namespace DBus::test

using namespace DBus::test;