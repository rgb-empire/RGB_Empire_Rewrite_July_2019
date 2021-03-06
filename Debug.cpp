// 
// 
// 

#include "Bug.h"


Bug::Bug()
{
}

void Bug::fps(const int seconds) {
	// Create static variables so that the code and variables can
	// all be declared inside a function
	static unsigned long lastMillis;
	static unsigned long frameCount;
	static unsigned int framesPerSecond;

	// It is best if we declare millis() only once
	unsigned long now = millis();

	frameCount++;

	if (now - lastMillis >= seconds * 1000) {
		framesPerSecond = frameCount / seconds;
		Serial.println(framesPerSecond);
		frameCount = 0;
		lastMillis = now;
	}
}

void Bug::display_memory(String new_string)
{
	Serial.println();

	Serial.print("Memory remaining " + new_string + ": ");

	Serial.print((ESP.getFreeHeap() / 1024));

	Serial.println(" KB");
}

void Bug::start(String new_string)
{
	Serial.println("Starting " + new_string);

	function_stack.push_back({new_string, millis()});
}

void Bug::end()
{
	name_and_time n_and_t = function_stack.pop_back;

	Serial.println("Ending " + n_and_t.function_name + " after " + (millis() - n_and_t.start_time) + " millis");
}
