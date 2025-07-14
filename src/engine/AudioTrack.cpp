#include "AudioTrack.h"

#include <stdlib.h>
#include <cstring> // why is memcpy in here?
#include <exception>

AudioTrack::AudioTrack(int initialCapacity) {
	buffer = malloc(initialCapacity);
	length = 0;
	capacity = initialCapacity;
}

AudioTrack::~AudioTrack() {
	free(buffer);
}

void AudioTrack::add(uchar* data, int dataLength) {
	if (dataLength > capacity) {
		newBuffer = realloc(buffer, capacity * 2);

		if (!newBuffer) {
			throw new std::exception("Not enough room to expand Audio Track")
		}

		buffer = newBuffer;
	}

	// Layer new data over any existing data we have
	int i = 0;
	for (; i < length; i++)
		buffer[i] += data[i];

	// Any remaining data should directly copied
	for (; i < dataLength; i++)
		buffer[i] = data[i];

	// Don't forget to set the length
	if (dataLength > length)
		length = dataLength;
}

uchar* AudioTrack::remove(int amountRemoved) {
	if (amountRemoved < 0)
		throw new std::exception("Cannot remove negative amount of data");
	if (amountRemoved > length)
		throw new std::exception("Audio Track does not contain enough data");

	uchar* dest = malloc(amountRemoved);

	memcpy(dest, buffer, amountRemoved);

	return dest;
}
