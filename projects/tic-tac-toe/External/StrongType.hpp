#pragma once

#include <functional>

template <class Type, class Tag>
class StrongType
{
public:
    explicit StrongType(const Type& value)
        : value(value)
    {
        Tag::verify(this->value);
    }
    StrongType(const StrongType<Type, Tag>& other)
        : value(other.value)
    {
    }

    explicit operator Type() const
    {
        return value;
    }

    StrongType<Type, Tag>& operator = (const StrongType<Type, Tag>& other)
    {
        value = other.value;
    }

    bool operator == (const StrongType<Type, Tag>& other) const
    {
        return value == other.value;
    }

    bool operator < (const StrongType<Type, Tag>& other) const
    {
        return value < other.value;
    }

private:
    Type value;
};
