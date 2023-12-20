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

#ifndef TRINITYCORE_WORLDPACKET_H
#define TRINITYCORE_WORLDPACKET_H

#include "Common.h"
#include "Opcodes.h"
#include "ByteBuffer.h"
#include "Duration.h"
#include <chrono>
#include "MessageBuffer.h"

struct z_stream_s;

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket() : ByteBuffer(0), m_opcode(UNKNOWN_OPCODE), m_rcvdOpcodeNumber(0), _compressionStream(NULL)
        {
        }

        WorldPacket(Opcodes opcode, size_t res = 200) : ByteBuffer(res), m_opcode(opcode), m_rcvdOpcodeNumber(0), _compressionStream(NULL)
        {
        }

                                                            // copy constructor
        WorldPacket(WorldPacket const& packet) : ByteBuffer(packet), m_opcode(packet.m_opcode), m_rcvdOpcodeNumber(0), _compressionStream(NULL)
        {
        }

        WorldPacket(WorldPacket&& packet) : ByteBuffer(std::move(packet)), m_opcode(packet.m_opcode)
        {
        }


        WorldPacket& operator=(WorldPacket const& right)
        {
            if (this != &right)
            {
                m_opcode = right.m_opcode;
                ByteBuffer::operator=(right);
            }

            return *this;
        }

        WorldPacket& operator=(WorldPacket&& right)
        {
            if (this != &right)
            {
                m_opcode = right.m_opcode;
                ByteBuffer::operator=(std::move(right));
            }

            return *this;
        }

        WorldPacket(Opcodes opcode, MessageBuffer&& buffer) : ByteBuffer(std::move(buffer)), m_opcode(opcode) { }


        void Initialize(Opcodes opcode, size_t newres = 200)
        {
            clear();
            _storage.reserve(newres);
            m_opcode = opcode;
        }

        Opcodes GetOpcode() const { return m_opcode; }
        void SetOpcode(Opcodes opcode) { m_opcode = opcode; }
        void Compress(z_stream_s* compressionStream);
        void Compress(z_stream_s* compressionStream, WorldPacket const* source);
        void SetReceivedOpcode(uint16 opcode) { m_rcvdOpcodeNumber = opcode; }
        uint16 GetReceivedOpcode() { return m_rcvdOpcodeNumber; }

        TimePoint GetReceivedTime() const { return m_receivedTime; }

    protected:
        Opcodes m_opcode;
        uint16 m_rcvdOpcodeNumber;
        void Compress(void* dst, uint32 *dst_size, const void* src, int src_size);
        z_stream_s* _compressionStream = nullptr;
        TimePoint m_receivedTime; // only set for a specific set of opcodes, for performance reasons.
        
};
#endif
