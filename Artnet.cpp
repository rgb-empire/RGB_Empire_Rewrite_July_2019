#include "Artnet.h"

// General pointer to facilitate calling back to non-static function Artnet::on_DMX_frame()
void* pt2Object;

int Artnet::num_universes = 0;
int Artnet::total_num_leds = 0;

bool Artnet::started = false;
int Artnet::previous_data_length = 0;

//bool connect_wifi(void)
//{
//	START;
//
//	char* ssid = "Trap_House";
//	char* password = "ThIsHoUsEisatrap72";
//
//
//	boolean state = true;
//	int i = 0;
//
//	WiFi.begin(ssid, password);
//	Serial.println("");
//	Serial.println("Connecting to WiFi");
//
//	// Wait for connection
//	Serial.print("Connecting");
//	while (WiFi.status() != WL_CONNECTED)
//	{
//		delay(500);
//		Serial.print(".");
//		if (i > 40) {
//			state = false;
//			break;
//		}
//		i++;
//	}
//	if (state) {
//		Serial.println("");
//		Serial.print("Connected to ");
//		Serial.println(ssid);
//		Serial.print("IP address: ");
//		Serial.println(WiFi.localIP());
//	}
//	else {
//		Serial.println("");
//		Serial.println("Connection failed.");
//	}
//
//	MEM;
//	END;
//
//	return state;
//}

Artnet::Artnet(LED_Group* new_group)
	:Animation(new_group),
	send_frame(1)
{
	START;

	total_num_leds += num_leds;

	num_universes = (total_num_leds * 3) / 512 + (((total_num_leds * 3) % 512) ? 1 : 0);



	universes_received = new bool[num_universes];
	
	if (started == false)
	{
		// If this is the startup animation we havn't connected to wifi yet!
		if (Wifi_Class::connected == false)
		{
			//Wifi_Class::start_wifi();
		}

		artnet.begin();
		artnet.setArtDmxCallback(Artnet::on_DMX_frame_wrapper);
		started = true;
	}

	start_pos = previous_data_length + 1;
	previous_data_length += num_leds;

	pt2Object = (void*) this;

	END;
}

void Artnet::run()
{
	START;

	artnet.read();

	END;
}

void Artnet::on_DMX_frame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
	START;

	// set brightness of the whole strip
	if (universe == 15)
	{
		FastLED.setBrightness(data[0]);
		//FastLED.show();
		//FastLED_Show_ESP32();
	}

	for (int i = 0; i < length / 3; i++)
	{
		if (i + universe * 512 / 3 >= start_pos && i + universe * 512 / 3 < start_pos + num_leds)
		{
			leds[i] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
		}
	}

	//if (start_pos >= universe * 512 / 3)
	//{
	//	// read universe and put into the right part of the display buffer
	//	for (int i = 0; i < length / 3; i++)
	//	{
	//		int led = i + universe * 512 / 3 - start_pos;

	//		if (led < num_leds)
	//			leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
	//	}
	//}

	END;
}


void Artnet::on_DMX_frame_wrapper(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
	START;

	// explicitly cast to a pointer to Classname
	Artnet* mySelf = (Artnet*)pt2Object;

	// call member
	mySelf->on_DMX_frame(universe, length, sequence, data);

	END;
}