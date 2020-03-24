

#ifndef _TRINITY_AUTO_PTR_H
#define _TRINITY_AUTO_PTR_H

#include <ace/Bound_Ptr.h>

namespace Trinity
{

template <class Pointer, class Lock>
class AutoPtr : public ACE_Strong_Bound_Ptr<Pointer, Lock>
{
    typedef ACE_Strong_Bound_Ptr<Pointer, Lock> Base;

public:
    AutoPtr()
        : Base()
    { }

    AutoPtr(Pointer* x)
        : Base(x)
    { }

    operator bool() const
    {
        return !Base::null();
    }

    bool operator !() const
    {
        return Base::null();
    }
};

} // namespace Trinity

#endif
