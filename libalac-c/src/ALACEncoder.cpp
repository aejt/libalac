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

#include "alac/ALACEncoder.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	ALACEncoder* ALACEncoder_New()
	{
		return new ALACEncoder();
	}

	void ALACEncoder_Delete(ALACEncoder* encoder)
	{
		delete encoder;
	}

	int32_t	ALACEncoder_Encode(ALACEncoder* encoder, AudioFormatDescription theInputFormat, AudioFormatDescription theOutputFormat,
							unsigned char * theReadBuffer, unsigned char * theWriteBuffer, int32_t * ioNumBytes) 
	{
		return encoder->Encode(theInputFormat, theOutputFormat, theReadBuffer, theWriteBuffer, ioNumBytes);
	}

	int32_t	ALACEncoder_Finish(ALACEncoder* encoder) 
	{
		return encoder->Finish();
	}

	void ALACEncoder_SetFastMode(ALACEncoder* encoder, int fast) 
	{
		encoder->SetFastMode(fast > 0);
	}

	// this must be called *before* InitializeEncoder()
	void ALACEncoder_SetFrameSize(ALACEncoder* encoder, uint32_t frameSize)
	{
		encoder->SetFrameSize(frameSize);
	}

	ALACSpecificConfig ALACEncoder_GetConfig(ALACEncoder* encoder)
	{
		ALACSpecificConfig config;
		encoder->GetConfig(config);
		return config;
	}

	uint32_t ALACEncoder_GetMagicCookieSize(ALACEncoder* encoder, uint32_t inNumChannels)
	{
		return encoder->GetMagicCookieSize(inNumChannels);
	}

	void ALACEncoder_GetMagicCookie(ALACEncoder* encoder, void *outCookie, uint32_t * ioSize)
	{
		encoder->GetMagicCookie(outCookie, ioSize);
	}

	int32_t	ALACEncoder_InitializeEncoder(ALACEncoder* encoder, AudioFormatDescription theOutputFormat)
	{
		return encoder->InitializeEncoder(theOutputFormat);
	}

#ifdef __cplusplus
}
#endif //__cplusplus
