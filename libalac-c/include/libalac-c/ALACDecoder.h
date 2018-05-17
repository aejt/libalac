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

#ifndef __ALACDECODER_H
#define __ALACDECODER_H

#include "alac/ALACBitUtilities.h"
#include "alac/ALACAudioTypes.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
	typedef struct ALACDecoder ALACDecoder;

	ALACDecoder* ALACDecoder_New();
	void ALACDecoder_Delete(ALACDecoder* decoder);
	int32_t ALACDecoder_Init(ALACDecoder* decoder, void* inMagicCookie, uint32_t inMagicCookieSize);
	int32_t ALACDecoder_Decode(ALACDecoder* decoder, struct BitBuffer * bits, uint8_t * sampleBuffer, uint32_t numSamples, uint32_t numChannels, uint32_t * outNumSamples);
	ALACSpecificConfig ALACDecoder_GetConfig(ALACDecoder* decoder);
	


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__ALACDECODER_H