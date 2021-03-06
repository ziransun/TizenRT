/* ****************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include <tinyara/config.h>
#include <assert.h>
#include <debug.h>
#include <unistd.h>
#include <media/InputDataSource.h>
#include "Decoder.h"
#include "MediaPlayerImpl.h"
#include "StreamBuffer.h"
#include "StreamBufferReader.h"
#include "StreamBufferWriter.h"

#ifndef CONFIG_INPUT_DATASOURCE_STACKSIZE
#define CONFIG_INPUT_DATASOURCE_STACKSIZE 4096
#endif

namespace media {
namespace stream {

InputDataSource::InputDataSource() :
	DataSource(),
	mAudioType(AUDIO_TYPE_INVALID)
{
}

InputDataSource::InputDataSource(const InputDataSource &source) :
	DataSource(source),
	mAudioType(source.mAudioType)
{
}

InputDataSource &InputDataSource::operator=(const InputDataSource &source)
{
	DataSource::operator=(source);
	this->mAudioType = source.mAudioType;

	return *this;
}

InputDataSource::~InputDataSource()
{
}

void InputDataSource::setAudioType(audio_type_t audioType)
{
	mAudioType = audioType;
}

audio_type_t InputDataSource::getAudioType()
{
	return mAudioType;
}

int InputDataSource::readAt(long offset, int origin, unsigned char *buf, size_t size)
{
	if (seek(offset, origin) != 0) {
		meddbg("InputDataSource::readAt : fail to seek\n");
		return -1;
	}

	return read(buf, size);
}

} // namespace stream
} // namespace media
