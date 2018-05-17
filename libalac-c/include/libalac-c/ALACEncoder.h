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

#ifndef __ALACENCODER_H
#define __ALACENCODER_H

#include "alac/ALACBitUtilities.h"
#include "alac/ALACAudioTypes.h"


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
	typedef struct ALACEncoder ALACEncoder;

	ALACEncoder*		ALACEncoder_New();
	void				ALACEncoder_Delete(ALACEncoder* decoder);

	int32_t				ALACEncoder_Encode(ALACEncoder* encoder, AudioFormatDescription theInputFormat, AudioFormatDescription theOutputFormat,
							unsigned char * theReadBuffer, unsigned char * theWriteBuffer, int32_t * ioNumBytes);

	int32_t				ALACEncoder_Finish(ALACEncoder* encoder);

	void				ALACEncoder_SetFastMode(ALACEncoder* encoder, int fast);

	// this must be called *before* InitializeEncoder()
	void				ALACEncoder_SetFrameSize(ALACEncoder* encoder, uint32_t frameSize);

	ALACSpecificConfig	ALACEncoder_GetConfig(ALACEncoder* encoder);
	uint32_t			ALACEncoder_GetMagicCookieSize(ALACEncoder* encoder, uint32_t inNumChannels);
	void				ALACEncoder_GetMagicCookie(ALACEncoder* encoder, void * outCookie, uint32_t * ioSize);

	int32_t				ALACEncoder_InitializeEncoder(ALACEncoder* encoder, AudioFormatDescription theOutputFormat);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__ALACENCODER_H