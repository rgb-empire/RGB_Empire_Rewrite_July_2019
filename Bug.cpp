// 
// 
// 

#include "Bug.h"

std::vector<name_and_time> Bug::function_stack;
std::vector<int> Bug::thing_stack;
//int Bug::framesPerSecond = 0;

Bug::Bug()
{
}

//void Bug::fps(int mseconds, int display_interval)
//{
//	START;
//
//	// Create static variables so that the code and variables can
//	// all be declared inside a function
//	static unsigned long lastMillis;
//	static unsigned long lastDisplayMillis;
//	static unsigned long frameCount;
//
//	// It is best if we declare millis() only once
//	unsigned long now = millis();
//
//	frameCount++;
//	//FastLED.countFPS();
//
//	// Update fps for anything that requires it.
//	if (now - lastMillis >= mseconds)
//	{
//		framesPerSecond = frameCount / ((float)mseconds / 1000.0);
//		frameCount = 0;
//		lastMillis = now;
//	}
//
//	// Show fps on the serial monitor.
//	if (now - lastDisplayMillis >= display_interval * 1000)
//	{
//		Serial.println(framesPerSecond);
//		Serial.println(FastLED.getFPS());
//
//		lastDisplayMillis = now;
//
//		MEM;
//	}
//
//	END;
//}

void Bug::display_memory(String new_string)
{

	//Serial.println();

	BUG5(
	for (int i = 0; i < function_stack.size() - 1; i++)
	{
		Serial.print("      ");
	})

	Serial.print("Memory remaining " + new_string + ": ");

	Serial.print((ESP.getFreeHeap() / 1024));

	Serial.println(" KB");
}

