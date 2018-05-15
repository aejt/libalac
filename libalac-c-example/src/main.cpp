/*
* Copyright (c) 2018 André Terranchie. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <iostream>
#include <vector>
#include <random>
#include <memory>

#include "libalac-c/ALACDecoder.h"
#include "libalac-c/ALACEncoder.h"

// Set all necessary variables once
static const int	FRAMES_PER_PACKET = kALACDefaultFramesPerPacket;
static const double	SAMPLE_RATE = 44100.00f;
static const int	BIT_DEPTH = 16;
static const int	CHANNELS = 2;
static const int	BYTES_PER_FRAME = (BIT_DEPTH * CHANNELS) / 8;
static const int	PCM_BUFFER_SIZE = FRAMES_PER_PACKET * BYTES_PER_FRAME;
static const int	ENCODED_MAX_SIZE = PCM_BUFFER_SIZE + kALACMaxEscapeHeaderBytes;


enum
{
	kTestFormatFlag_16BitSourceData = 1,
	kTestFormatFlag_20BitSourceData = 2,
	kTestFormatFlag_24BitSourceData = 3,
	kTestFormatFlag_32BitSourceData = 4
};

int getAlacFormatFlag(int bit_depth)
{
	int alacFormatFlags;
	switch (bit_depth)
	{
	case 16:
		return  kTestFormatFlag_16BitSourceData;
		break;
	case 20:
		return kTestFormatFlag_20BitSourceData;
		break;
	case 24:
		return kTestFormatFlag_24BitSourceData;
		break;
	case 32:
		return kTestFormatFlag_32BitSourceData;
		break;
	}
}

int main()
{
	// Set up random generator
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 255);

	// Set up description of the pcm format (each PCM packet should have size of 1 frame)
	AudioFormatDescription pcm_description {
		SAMPLE_RATE,					// mSampleRate
		kALACFormatLinearPCM,			// mFormatID
		kALACFormatFlagsNativeEndian,   // mFormatFlags
		1 * BYTES_PER_FRAME,			// mBytesPerPacket
		1,								// mFramesPerPacket
		BYTES_PER_FRAME,				// mBytesPerFrame
		CHANNELS,						// mChannelsPerFrame
		BIT_DEPTH,						// mBitsPerChannel
		0								// mReserved
	};


	// Set up description of the alac format
	AudioFormatDescription alac_description{
		SAMPLE_RATE,					// mSampleRate
		kALACFormatAppleLossless,		// mFormatID
		getAlacFormatFlag(BIT_DEPTH),	// mFormatFlags
		0,								// mBytesPerPacket
		FRAMES_PER_PACKET,				// mFramesPerPacket
		0,								// mBytesPerFrame
		CHANNELS,						// mChannelsPerFrame
		0,								// mBitsPerChannel
		0								// mReserved
	};

	// Create a buffer of PCM values
	std::vector<uint8_t> pcm_buffer(PCM_BUFFER_SIZE);
	for (int i = 0; i < PCM_BUFFER_SIZE; i++)
	{
		pcm_buffer[i] = i % 256; // <-- Commenting this line and uncommenting the line below makes it work
		//pcm_buffer[i] = distribution(generator);
	}

	// Create and initialize encoder
	auto encoder = ALACEncoder_New();
	ALACEncoder_SetFrameSize(encoder, FRAMES_PER_PACKET);
	ALACEncoder_SetFastMode(encoder, false);
	ALACEncoder_InitializeEncoder(encoder, alac_description);

	// Allocate buffer to store encoded data, then resize it to the size that was actually read
	std::vector<uint8_t> encoded_buffer(ENCODED_MAX_SIZE);
	int ioNumBytes = PCM_BUFFER_SIZE;
	int encode_status = ALACEncoder_Encode(encoder, pcm_description, alac_description, pcm_buffer.data(), encoded_buffer.data(), &ioNumBytes);
	if (encode_status == ALAC_noErr)
		std::cout << "Encoding succeeded (" << ioNumBytes << " bytes)" << std::endl;
	else
		std::cout << "Decoding failed with error " << encode_status << "!" << std::endl;
	encoded_buffer.resize(ioNumBytes); //<-- Tried both with and without this; the converter example seems to let this stay at the max encoded buffer size.

	// Get cookie from encoder
	uint32_t cookie_size = ALACEncoder_GetMagicCookieSize(encoder, CHANNELS);
	std::vector<uint8_t> cookie(cookie_size);
	ALACEncoder_GetMagicCookie(encoder, cookie.data(), &cookie_size);

	// Create and initialize decoder using the encoder's cookie
	auto decoder = ALACDecoder_New();
	ALACDecoder_Init(decoder, cookie.data(), cookie.size());
	
	// Set up a BitBuffer pointing to the encoded data
	BitBuffer bit_buffer{0};
	BitBufferInit(&bit_buffer, encoded_buffer.data(), encoded_buffer.size());

	// Allocate buffer to store decoded data
	std::vector<uint8_t> decoded_buffer(PCM_BUFFER_SIZE);
	uint32_t frames_read;
	int decode_status = ALACDecoder_Decode(decoder, &bit_buffer, decoded_buffer.data(), FRAMES_PER_PACKET, CHANNELS, &frames_read);
	if (decode_status == ALAC_noErr)
		std::cout << "Decoding succeeded (" << frames_read*BYTES_PER_FRAME << " bytes)" << std::endl;
	else
		std::cout << "Decoding failed with error " << decode_status << "!" << std::endl;

	std::cin.get();
}