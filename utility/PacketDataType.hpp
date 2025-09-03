#ifndef SOFTAP_UTILITY_PACKETDATATYPE_HPP
#define SOFTAP_UTILITY_PACKETDATATYPE_HPP

#include <cstdint>

// 上位2ビットで型を判別
//   00 -> int32_t
//   01 -> uint32_t
//   10 -> float
//   11 -> 未定義 / 予約

enum class PacketDataFloat : uint8_t {

    // float (上位2ビット = 10 -> 0x80〜0xBF)
    ACCEL_X = 0x80, // 1000 0000
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

enum class PacketDataUint32_t{

    // uint32_t (上位2ビット = 01 -> 0x40〜0x7F)
    PRESS   = 0x40,
};

enum class PacketDataInt32_t{

    // int32_t(上位2ビット = 00 -> 0x00〜0x3F)
    SAMPLE  = 0x30,
};

#endif // SOFTAP_UTILITY_PACKETDATATYPE_HPP
