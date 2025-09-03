#ifndef PACKET_DECODER_HPP
#define PACKET_DECODER_HPP

#include <array>

struct DecodedPacket {

    std::array<uint8_t, 256> data;
    uint8_t current_packet_size = 0;
};


class PacketDecoder {

public:

};

#endif // PACKET_DECODER_HPP
