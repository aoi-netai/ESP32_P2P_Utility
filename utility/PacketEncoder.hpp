#ifndef SOFTAP_UTILITY_PACKETENCODER_HPP
#define SOFTAP_UTILITY_PACKETENCODER_HPP

#include <cstdint>
#include <array>
#include <cstring>
#include <type_traits>

#include "../src/PacketDataType.hpp"
#include "../src/PacketUtility.hpp"

struct EncodedPacket {

    std::array<uint8_t, 256> data;
    uint8_t current_packet_size = 0;
};


class PacketEncoder {

public:
    PacketEncoder() = default;

    // 明示的オーバーロードで .cpp に実装
    PacketError AddData(PacketDataType type, float data);
    PacketError AddData(PacketDataType type, uint32_t data);
    PacketError AddData(PacketDataType type, int32_t data);


    // パケットのポインタとサイズを取得
    PacketError GetPacketPtr(uint8_t** outPtr, uint8_t* outSize);
    uint8_t GetPacketSize() const;

    // パケットの開始/終了を明示的に制御
    PacketError Begin();
    PacketError End();

private:

    EncodedPacket packet;
    bool has_begin_ = false;
    bool has_end_ = false;
    bool ptr_given_ = false;
};

#endif // SOFTAP_UTILITY_PACKETENCODER_HPP

