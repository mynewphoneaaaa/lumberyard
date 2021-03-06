#ifndef AZ_CORE_GUID_H
#define AZ_CORE_GUID_H 1

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID {
    _GUID(unsigned long d1, unsigned short d2, unsigned short d3, std::initializer_list<unsigned char> d4)
    : Data1(d1),
    Data2(d2),
    Data3(d3)
    {
        for (auto it = d4.begin(); it != d4.end(); ++it)
            Data4[it - d4.begin()] = *it;
    }

#ifdef QUUID_H
    _GUID(const QUuid& guid = QUuid())
    {
        *this = guid;
    }
    _GUID& operator=(const QUuid& id)
    {
        *this = _GUID({id.data1, id.data2, id.data3, {id.data4[0], id.data4[1], id.data4[2], id.data4[3], id.data4[4], id.data4[5], id.data4[6], id.data4[7] }});
        return *this;
    }
    
    operator QUuid() const
    {
        return QUuid(Data1, Data2, Data3, Data4[0], Data4[1], Data4[2], Data4[3], Data4[4], Data4[5], Data4[6], Data4[7]);
    }
#else
    _GUID() = default;
#endif // QUUID_H

    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;
#endif // GUID_DEFINED

#if !defined _SYS_GUID_OPERATOR_EQ_ && !defined _NO_SYS_GUID_OPERATOR_EQ_
#define _SYS_GUID_OPERATOR_EQ_
static bool inline operator==(const _GUID& lhs, const _GUID& rhs)
{
    return lhs.Data1 == rhs.Data1 &&
           lhs.Data2 == rhs.Data2 &&
           lhs.Data3 == rhs.Data3 &&
           memcmp(lhs.Data4, rhs.Data4, 8) == 0;
}
static bool inline operator!=(const _GUID& lhs, const _GUID& rhs)
{
    return !operator==(lhs, rhs);
}
#endif //  !defined _SYS_GUID_OPERATOR_EQ_

#ifdef AZ_PLATFORM_APPLE

#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID const GUID &
#endif

# ifndef IID_DEFINED
# define IID_DEFINED
typedef GUID IID;
typedef const IID& REFIID;
# endif

#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
typedef const GUID& REFIID;
#endif

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
const GUID name \
= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

static REFGUID GUID_NULL()
{
    static const GUID guid = { 0x00000000L, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} };
    return guid;
}

#define GUID_NULL GUID_NULL()

#endif

#endif // AZ_CORE_GUID_H
#pragma once
