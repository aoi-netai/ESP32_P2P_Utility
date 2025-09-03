#include <Arduino.h>
#include "P2PPacketEncoder.hpp"
#include "P2PPacketDecoder.hpp"

void setup() {
	Serial.begin(115200);
	while (!Serial) { delay(10); }

	P2PPacketEncoder encoder;
	encoder.Begin();
	encoder.AddData(PacketDataType::PRESS, (uint32_t)101325);
	encoder.AddData(PacketDataType::SAMPLE, (int32_t)-12345);
	encoder.AddData(PacketDataType::ACCEL_X, 1.234f);
	encoder.End();

	uint8_t* buf = nullptr;
	uint8_t size = 0;
	if (encoder.GetData(&buf, &size) == PacketError::SUCCESS) {
		Serial.print("Encoded size: ");
		Serial.println(size);

		// feed to decoder
		P2PPacketDecoder decoder;
		if (decoder.SetData(buf, size) == PacketError::SUCCESS) {
			uint32_t press = 0;
			int32_t sample = 0;
			float accel = 0.0f;
			if (decoder.GetData(PacketDataType::PRESS, press) == PacketError::SUCCESS) {
				Serial.print("PRESS: "); Serial.println(press);
			}
			if (decoder.GetData(PacketDataType::SAMPLE, sample) == PacketError::SUCCESS) {
				Serial.print("SAMPLE: "); Serial.println(sample);
			}
			if (decoder.GetData(PacketDataType::ACCEL_X, accel) == PacketError::SUCCESS) {
				Serial.print("ACCEL_X: "); Serial.println(accel, 6);
			}
		} else {
			Serial.println("Decoder SetData failed");
		}
	} else {
		Serial.println("GetData failed");
	}

}

void loop() {
  

}
