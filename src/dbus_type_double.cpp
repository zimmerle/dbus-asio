#include <iomanip>
#include <sstream>

#include <boost/thread/recursive_mutex.hpp>

#include "dbus_type.h"
#include "dbus_type_base.h"
#include "dbus_type_double.h"

#include "dbus_message.h"
#include "dbus_messageprotocol.h"
#include "dbus_messagestream.h"
#include "dbus_type_struct.h"

const std::string DBus::Type::Double::s_StaticTypeCode("d");

DBus::Type::Double::Double()
    : m_Value(0)
{
    setSignature(s_StaticTypeCode);
}

DBus::Type::Double::Double(double v)
    : m_Value(v)
{
    setSignature(s_StaticTypeCode);
}

void DBus::Type::Double::marshall(MessageStream& stream) const { stream.writeDouble(m_Value); }

bool DBus::Type::Double::unmarshall(const UnmarshallingData& data)
{
    if (m_Unmarshalling.areWeSkippingPadding && !Utils::isAlignedTo(getAlignment(), data.offset)) {
        return false;
    }
    m_Unmarshalling.areWeSkippingPadding = false;

    m_Unmarshalling.value <<= 8;
    m_Unmarshalling.value += data.c;

    if (++m_Unmarshalling.count == 8) {
        m_Unmarshalling.value = doSwap64(m_Unmarshalling.value);
        m_Value = *(double*)&m_Unmarshalling.value;
        return true;
    }
    return false;
}

std::string DBus::Type::Double::toString(const std::string& prefix) const
{
    std::stringstream ss;

    ss << prefix << "Double ";
    ss << m_Value << "\n";

    return ss.str();
}

std::string DBus::Type::Double::asString() const
{
    std::stringstream ss;
    ss << m_Value;
    return ss.str();
}