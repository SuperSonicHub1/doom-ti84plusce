#include "doomkeys.h"

#include "doomgeneric.h"

#include <string.h>
#include <time.h>

#include <graphx.h>
#include <tice.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned int key)
{
}

static void addKeyToQueue(int pressed, unsigned int keyCode)
{
	unsigned char key = convertToDoomKey(keyCode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DG_Init()
{
	// Intialize the key queue.
	memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));

	// Initialize the graphics library setup.
	gfx_Begin();

	// Draw to the buffer to avoid rendering artifacts
	gfx_SetDrawBuffer();

	// Close the graphics setup on exit.
	atexit(gfx_End);
}


void DG_DrawFrame()
{
}

void DG_SleepMs(uint32_t ms)
{
    usleep(ms * 1000);
}

uint32_t DG_GetTicksMs()
{
	return (uint32_t)((double) clock() / CLOCKS_PER_SEC * 1000);
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
	{
		//key queue is empty

		return 0;
	}
	else
	{
		unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
		s_KeyQueueReadIndex++;
		s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

		*pressed = keyData >> 8;
		*doomKey = keyData & 0xFF;

		return 1;
	}
}

void DG_SetWindowTitle(const char * title)
{
	// The calculator has no concept of windowing.
}
