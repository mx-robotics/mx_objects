#ifndef MX_OBJECTS_STAMPOBJECT_H
#define MX_OBJECTS_STAMPOBJECT_H

#include <cstdint>
#include <cstring>
#include <mx/objects/time.h>

#if defined(__amd64__)
#include <iostream>
#endif


namespace mx
{
namespace objects
{
template <typename Object, typename Stamp>
class StampedObject : public Object
{
public:
    Stamp stamp;
    StampedObject()
        : Object()
        , stamp(){}
    StampedObject(const Object &value)
        : Object(value)
        , stamp() {}
    StampedObject(const StampedObject &m)
        : Object(m)
        , stamp(m.stamp) {}
    StampedObject(const Object &value, const Stamp &stamp)
        : Object(value)
        , stamp(stamp) {}
    StampedObject &operator+=(const StampedObject &rhs)
    {
        stamp += rhs.stamp;
        *this += (const Object &) rhs.value;
        return *this;
    }
    StampedObject &operator-=(const StampedObject &rhs)
    {
        stamp -= rhs.stamp;
        *this -= (const Object &) rhs.value;
        return *this;
    }
    friend StampedObject operator+(StampedObject lhs, const StampedObject &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend StampedObject operator-(StampedObject lhs, const StampedObject &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
#if defined(__amd64__)
    
    friend std::ostream &operator << ( std::ostream &os, const StampedObject &o ) {
        os << o.getToString();
        return os;
    };
    std::string getToStringReadable() const {
        char buf[0xFF];
        sprintf ( buf, "[%s, %s ]", stamp.getToStringReadable().c_str(), Object::getToStringReadable().c_str());
        return std::string ( buf );
    }
#endif
};
};     // namespace objects
};     // namespace mx
#endif //MX_OBJECTS_STAMPOBJECT_H

