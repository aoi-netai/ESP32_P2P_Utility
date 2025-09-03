#include "PacketEncoder.hpp"
#include "../src/PacketDataType.hpp"
#include "../src/PacketUtility.hpp"

// 共通ロジック：4バイト値をパケットに追加する
// AddValueToPacket は Packet のみを操作する
static PacketError AddValueToPacket(EncodedPacket &packet, uint8_t type, const void* valuePtr) {

	const size_t needed = 5; // type(1) + value(4)

    // パケットサイズが足りない時
	if (static_cast<size_t>(packet.current_packet_size) + needed > packet.data.size()) {

		return PacketError::PACKET_OVERFLOW;
	}

    // 現在のパケットサイズを取得
	size_t idx = packet.current_packet_size;
	packet.data[idx] = type;

    // データ型1byteと4byte変数を格納
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(valuePtr);
	packet.data[idx + 1] = bytes[0];
	packet.data[idx + 2] = bytes[1];
	packet.data[idx + 3] = bytes[2];
	packet.data[idx + 4] = bytes[3];

    // パケットサイズを更新
	packet.current_packet_size = static_cast<uint8_t>(idx + 5);
    
    return PacketError::SUCCESS;
}

// floatデータを追加
PacketError PacketEncoder::AddData(PacketDataType type, float data) {

    // Beginが呼ばれていない場合
	if (!has_begin_){

        return PacketError::PACKET_NOT_INITIALIZED;
    }

    // Endが呼ばれている場合
    if (has_end_){

        return PacketError::TYPE_MISMATCH;
    } 

	return AddValueToPacket(packet, (uint8_t)type, &data);
}

// uint32_tデータを追加
PacketError PacketEncoder::AddData(PacketDataType type, uint32_t data) {

    // Beginが呼ばれていない場合
	if (!has_begin_){

	return PacketError::PACKET_NOT_INITIALIZED;
    }

    // Endが呼ばれている場合
    if (has_end_) {

        return PacketError::TYPE_MISMATCH;
    } 

	return AddValueToPacket(packet, (uint8_t)type, &data);
}

// int32_tデータを追加
PacketError PacketEncoder::AddData(PacketDataType type, int32_t data) {

    // Beginが呼ばれていない場合
	if (!has_begin_){

	return PacketError::PACKET_NOT_INITIALIZED;
    }

    // Endが呼ばれている場合
    if (has_end_){

        return PacketError::TYPE_MISMATCH;
    } 

	return AddValueToPacket(packet, (uint8_t)type, &data);
}

// パケットのポインタを取得
PacketError PacketEncoder::GetPacketPtr(uint8_t** outPtr, uint8_t* outSize) {

	// 引数のポインタが無効な場合
	if (outPtr == nullptr || outSize == nullptr){
		
		return PacketError::TYPE_MISMATCH;
	}

	// Beginが呼ばれていない場合
	if (!has_begin_) {

		*outPtr = nullptr;
		*outSize = 0;

		return PacketError::PACKET_NOT_INITIALIZED;
	}

	// Endが呼ばれていない場合
	if (!has_end_) {

		*outPtr = nullptr;
		*outSize = 0;

		return PacketError::PACKET_NOT_ENDED;
	}

	// すでにポインタが渡されている場合
	if (ptr_given_) {

		*outPtr = nullptr;
		*outSize = 0;

		return PacketError::PACKET_ALREADY_RETRIEVED;
	}

	// ポインタを渡す
	*outPtr = packet.data.data();
	*outSize = packet.current_packet_size;
	ptr_given_ = true;

	// 内部状態をリセットする
	has_end_ = false;
	has_begin_ = false; // Reset has_begin_ to allow Begin() to be called again
	packet.current_packet_size = 0;

	return PacketError::SUCCESS;
}

// 現在のパケットサイズを取得
uint8_t PacketEncoder::GetPacketSize() const {

	return packet.current_packet_size;
}

// StartBitを追加
PacketError PacketEncoder::Begin() {

    // すでに追加済みの場合
	if (has_begin_){
        
        return PacketError::TYPE_MISMATCH; 
    }

	// 開始ビットを先頭にセット
	packet.current_packet_size = 0;
	packet.data[0] = 0x00;

	// サイズとフラグを設定
	packet.current_packet_size = 1;
	has_begin_ = true;
	has_end_ = false;
	ptr_given_ = false;

	return PacketError::SUCCESS;
}

PacketError PacketEncoder::End() {

    // 開始されていない場合
	if (!has_begin_){
        
        return PacketError::TYPE_MISMATCH;
	}

    // 終了されていない場合
	if (has_end_){

        return PacketError::TYPE_MISMATCH;
    }

	// 終了ビットが入るか確認
	if (static_cast<size_t>(packet.current_packet_size) + 1 > packet.data.size()) {

		return PacketError::PACKET_OVERFLOW;
	}

    // 終了ビットを追加
	packet.data[packet.current_packet_size] = 0xFF;
	packet.current_packet_size = static_cast<uint8_t>(packet.current_packet_size + 1);
	has_end_ = true;

	return PacketError::SUCCESS;
}
