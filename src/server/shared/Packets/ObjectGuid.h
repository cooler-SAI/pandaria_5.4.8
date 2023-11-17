/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ObjectGuid_h__
#define ObjectGuid_h__

//! Structure to ease conversions from single 64 bit integer guid into individual bytes, for packet sending purposes
//! Nuke this out when porting ObjectGuid from MaNGOS, but preserve the per-byte storage
class TC_GAME_API ObjectGuid
{
public:
    ObjectGuid() { _data.u64 = UI64LIT(0); }
    ObjectGuid(uint64 guid) { _data.u64 = guid; }
    ObjectGuid(ObjectGuid const& other) { _data.u64 = other._data.u64; }

    uint8& operator[](uint32 index)
    {
        ASSERT(index < sizeof(uint64));

#if TRINITY_ENDIAN == TRINITY_LITTLEENDIAN
        return _data.byte[index];
#else
        return _data.byte[7 - index];
#endif
    }

    uint8 const& operator[](uint32 index) const
    {
        ASSERT(index < sizeof(uint64));

#if TRINITY_ENDIAN == TRINITY_LITTLEENDIAN
        return _data.byte[index];
#else
        return _data.byte[7 - index];
#endif
    }

    operator uint64()
    {
        return _data.u64;
    }

    ObjectGuid& operator=(uint64 guid)
    {
        _data.u64 = guid;
        return *this;
    }

    ObjectGuid& operator=(ObjectGuid const& other)
    {
        _data.u64 = other._data.u64;
        return *this;
    }

    void Clear() 
    {
        _data.u64 = 0;
    }

private:
    union
    {
        uint64 u64;
        uint8 byte[8];
    } _data;

};

#endif // ObjectGuid_h__