#ifndef PACKET_DATA_TYPE_HPP
#define PACKET_DATA_TYPE_HPP

#include <cstdint>

// 単一の enum class にまとめた PacketDataType
enum class PacketDataType : uint8_t {
    // int32_t (上位2ビット = 00 -> 0x00〜0x3F)
    SAMPLE = 0x30,

    // uint32_t (上位2ビット = 01 -> 0x40〜0x7F)
    PRESS  = 0x40,

    // float (上位2ビット = 10 -> 0x80〜0xBF)
    ACCEL_X = 0x80,
    ACCEL_Y = 0x81,
    ACCEL_Z = 0x82,
    GYRO_X  = 0x83,
    GYRO_Y  = 0x84,
    GYRO_Z  = 0x85,
    MAG_X   = 0x86,
    MAG_Y   = 0x87,
    MAG_Z   = 0x88,
    TEMP    = 0x89,
};

#endif // PACKET_DATA_TYPE_HPP
