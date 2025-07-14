#pragma once

typedef unsigned char uchar;

class AudioTrack {
private:
	uchar* buffer;
	int capacity;
	int length;

public:
	AudioTrack(int initialCapacity = 64);
	~AudioTrack();

	/* Adds data to the given track, layering over the data that was already there. 
	   If the data is longer than the data that is already there, expands the track's buffer.
	*/
	void add(uchar* data, int dataLength);

	/* Removes the specified amount of data from the front of the track,
	   pushing the rest forward in the queue. Returns a pointer to the removed data.
	 */
	uchar* remove(int amountRemoved);
};
