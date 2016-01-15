#ifndef DYNAMIXEL_PROTOCOL1_HPP_
#define DYNAMIXEL_PROTOCOL1_HPP_

#include <stdint.h>
#include <vector>
#include <cassert>

namespace dynamixel {
    class Protocol1 {
    public:
        typedef uint8_t id_t;
        typedef uint8_t instr_t;
        typedef uint8_t address_t;
        typedef uint8_t length_t;

        struct Instructions {
            static const instr_t ping = 0x01;
            static const instr_t read = 0x02;
            static const instr_t write = 0x03;
            static const instr_t reg_write = 0x4;
            static const instr_t action = 0x05;
            static const instr_t factory_reset = 0x06;
            static const instr_t sync_write = 0x83;
        };

        static std::vector<uint8_t> pack(id_t id, instr_t instr, const std::vector<uint8_t>& parameters)
        {
            size_t packet_size = 2 // header
                + 1 // id
                + 1 // length
                + 1 // instruction
                + parameters.size() // parameters
                + 1; // checksum

            std::vector<uint8_t> packet(packet_size);

            packet[0] = 0xFF;
            packet[1] = 0xFF;
            packet[2] = id;
            packet[3] = (uint8_t)(parameters.size() + 2);
            packet[4] = instr;

            for (size_t i = 0; i < parameters.size(); ++i)
                packet[5 + i] = parameters[i];

            packet[packet_size - 1] = _checksum(packet);

            return packet;
        }

    protected:
        static uint8_t _checksum(const std::vector<uint8_t>& packet)
        {
            assert(packet.size());
            int sum = 0;
            for (size_t i = 2; i < packet.size() - 1; ++i)
                sum += packet[i];
            uint8_t checksum = (sum & 0xFF);
            assert((sum > 255) || (sum == checksum));
            return ~checksum;
        }
    };
}

#endif
