// Bug.h

// This is where my elf file is stored. I'd assume yours is in a similar location.
// Use the elf file and the ESP32 Exception Decoder in the Arduino IDE to decode your backtrace.
// elf file location
// C:\Users\pikipupiba\AppData\Local\Temp\VMBuilds\RGB_Empire_Rewrite_July_2019\esp32_esp32wrover\Release/RGB_Empire_Rewrite_July_2019.ino.elf

// All functions and variables related to BUGging will go here.

// Use the macro D(1-5)(*your code here*) when putting in BUG code.

// Uncomment the following lines to enable debugging code.
#define BUG_1	// Free memory after constructors and FPS.
//#define BUG_2	// Used to selectively enable certain macros.
//#define BUG_3	// 
//#define BUG_4	// 

//#define BUG_5	// Beginning, middle, and end of every function.

#ifndef _BUG_h
#define _BUG_h

//#include "StandardCplusplus.h"

#include "Arduino.h"
#include <vector>
#include "FastLED.h"

#define START BUG5(Bug::start(__PRETTY_FUNCTION__))
#define START2 BUG2(Bug::start(__PRETTY_FUNCTION__))
#define THING BUG5(Bug::thing_counter(__PRETTY_FUNCTION__))
#define THING2 BUG2(Bug::thing_counter(__PRETTY_FUNCTION__))
#define END BUG5(Bug::end(__PRETTY_FUNCTION__))
//#define END(x) BUG5(Bug::end(__PRETTY_FUNCTION__ + x))
#define END2 BUG2(Bug::end(__PRETTY_FUNCTION__))
#define MEM Bug::display_memory(" after " + String(__PRETTY_FUNCTION__))


#define P(x) Bug::print(#x, x)
#define P1(x) BUG1(Bug::print(#x, x))
#define P2(x) BUG2(Bug::print(#x, x))
#define P3(x) BUG3(Bug::print(#x, x))
#define P4(x) BUG4(Bug::print(#x, x))
#define P5(x) BUG5(Bug::print(#x, x))

#if defined BUG_1
#	define BUG1(x) x
#else
#	define BUG1(x)
#endif

#if defined BUG_2
#	define BUG2(x) x
#else
#	define BUG2(x)
#endif

#if defined BUG_3
#	define BUG3(x) x
#else
#	define BUG3(x)
#endif

#if defined BUG_4
#	define BUG4(x) x
#else
#	define BUG4(x)
#endif

#if defined BUG_5
#	define BUG5(x) x
#else
#	define BUG5(x)
#endif

// This line is used to selectively enable BUGging code without enabling BUG_(1-5)
#define BUG(x) x

// Struct used to store the start times of functions for code analysis.
struct name_and_time
{
	String function_name;
	unsigned long start_time;
};

extern float speed_scale_factor;
extern float speed_scale_factor_modifier;

class Bug
{
protected:

	static std::vector<name_and_time> function_stack;
	static std::vector<int> thing_stack;

public:
	//static int framesPerSecond;

	Bug();

	//static void fps(const int mseconds, const int display_interval);

	static inline void display_memory(String new_string);

	// Made all of these inline to keep the framerate up when using BUG_5

	static inline void start(String new_string);

	static inline int end(String new_string);

	static inline void thing_counter(String new_string);

	static inline void print(String new_string, float value);

	static inline void print(String new_string, int value);

	static inline void check_memory();
};

inline void Bug::display_memory(String new_string)
{

	//Serial.println();

	if (!function_stack.empty())
	{
		for (int i = 0; i < function_stack.size() - 1; i++)
		{
			Serial.print("      ");
		}
	}

	Serial.print("Memory remaining " + new_string + ": ");

	Serial.print((ESP.getFreeHeap() / 1024));

	Serial.println(" KB");

	heap_caps_check_integrity_all(true);
}

inline void Bug::start(String new_string)
{
	name_and_time n_and_t;

	n_and_t.function_name = new_string;
	n_and_t.start_time = millis();

	function_stack.push_back(n_and_t);
	thing_stack.push_back(0);

	String string_me = "";

		for (int i = 0; i < function_stack.size() - 1; i++)
		{
			string_me += "      ";
		}

		string_me += "Starting ";

		Serial.println(string_me + new_string);

	heap_caps_check_integrity_all(true);

}

inline int Bug::end(String new_string)
{
	heap_caps_check_integrity_all(true);

	name_and_time n_and_t = function_stack.back();

	int function_time = millis() - n_and_t.start_time;

	String string_me = "";

	if (n_and_t.function_name.equals(new_string))
	{

		for (int i = 0; i < function_stack.size() - 1; i++)
		{
			string_me += "      ";
		}

		string_me += "Ending ";

		function_stack.pop_back();
		thing_stack.pop_back();

		Serial.println(string_me + n_and_t.function_name + " after " + (function_time)+" millis");
	}
	else
	{
		Serial.println("START/END MISMATCH IN " + new_string);
	}

	return function_time;
}

inline void Bug::thing_counter(String new_string)
{
	heap_caps_check_integrity_all(true);

	if (thing_stack.empty())
	{
		thing_stack.push_back(0);
	}

	thing_stack.back()++;

	String string_me = "";

	for (int i = 0; i < thing_stack.size() - 1; i++)
	{
		string_me += "      ";
	}

	Serial.println(string_me + "Thing #" + (String)thing_stack.back() + " in " + new_string);
}

inline void Bug::print(String new_string, float value)
{
	Serial.println(new_string + ": " + String(value));
}

inline void Bug::print(String new_string, int value)
{
	Serial.println(new_string + ": " + String(value));
}

inline void Bug::check_memory() {

	Serial.print("Memory remaining: ");

	Serial.print((ESP.getFreeHeap() / 1024));

	Serial.print(" KB  ");

	Serial.print("and running at ");

	Serial.print(FastLED.getFPS());

	Serial.println(" FPS");

	heap_caps_check_integrity_all(true);
}

#endif
