#pragma once

// This animation creates an Artnet recieving thing and does it.

#include "Animation.h"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#include "Wifi_Class.h"

#include "Tasks.h"

class Artnet :
	public Animation
{
protected:
	const Animation_Name name = _Artnet;

	ArtnetWifi artnet;
	const int start_universe = 0;

	static int num_universes;
	static int total_num_leds;
	bool* universes_received;
	bool send_frame;
	static int previous_data_length;
	int start_pos;

	static bool started;

public:
	Artnet(LED_Group* new_group);

	void run();

	void on_DMX_frame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);
	static void on_DMX_frame_wrapper(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);
};

