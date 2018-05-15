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

#include "libalac/ALACDecoder.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	ALACDecoder* ALACDecoder_New()
	{
		return new ALACDecoder();
	}

	void ALACDecoder_Delete(ALACDecoder* decoder)
	{
		delete decoder;
	}

	int32_t ALACDecoder_Init(ALACDecoder* decoder, void* inMagicCookie, uint32_t inMagicCookieSize)
	{
		return decoder->Init(inMagicCookie, inMagicCookieSize);
	}

	int32_t ALACDecoder_Decode(ALACDecoder* decoder, struct BitBuffer * bits, uint8_t * sampleBuffer, uint32_t numSamples, uint32_t numChannels, uint32_t * outNumSamples)
	{
		return decoder->Decode(bits, sampleBuffer, numSamples, numChannels, outNumSamples);
	}

	ALACSpecificConfig ALACDecoder_GetConfig(ALACDecoder* decoder) {
		return decoder->mConfig;
	}


#ifdef __cplusplus
}
#endif //__cplusplus
