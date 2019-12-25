#include "Wifi_Class.h"

WiFiUDP Wifi_Class::udp;
char Wifi_Class::incoming_packet[255];  // buffer for incoming packets
char Wifi_Class::reply_packet[255];  // a reply string to send back

int Wifi_Class::udpPort = 33333;

bool Wifi_Class::connected = false;
bool Wifi_Class::timeout = false;
long Wifi_Class::try_again_time = 0;

//char* Wifi_Class::ssid = "Trap_House";
//char* Wifi_Class::password = "ThIsHoUsEisatrap72";

//char* Wifi_Class::ssid = "ESP_Master";
//char* Wifi_Class::password = "ESP_Secure_Password";

char* Wifi_Class::ssid = "Bill wi the science fi-2.4";
char* Wifi_Class::password = "3096605290";


void Wifi_Class::WiFiEvent(WiFiEvent_t event) {

	START;

	switch (event) {

	case SYSTEM_EVENT_STA_GOT_IP:
		//When connected set
		Serial.print("WiFi connected! IP address: ");
		Serial.println(WiFi.localIP());
		Serial.println(WiFi.getHostname());
		//initializes the UDP state
		//This initializes the transfer buffer
		udp.begin(WiFi.localIP(), udpPort);
		connected = true;

		break;
	case SYSTEM_EVENT_STA_DISCONNECTED:
		Serial.println("WiFi lost connection");

		connected = false;

		break;
	default:
		break;
	}

	END;
}

void Wifi_Class::start_wifi()
{
	Serial.println("Connecting to WiFi network: " + String(ssid));

	WiFi.mode(WIFI_STA);

	timeout = false;

	while (connected == false && timeout == false)
	{
		static long int time = millis();

		static long int timeout_time = millis() + 10000;

		if (millis() > time + 2500)
		{
			// delete old config
			WiFi.disconnect(); // passed "true" in original
			//register event handler

			WiFi.onEvent(WiFiEvent);

			WiFi.enableSTA(true);

			//Initiate connection
			WiFi.begin(ssid, password);

			time = millis();
		}

		if (millis() > timeout_time)
		{
			timeout = true;
			try_again_time = millis() + 60000 * 5;
		}

	}

	WiFi.setSleep(false);
}

void Wifi_Class::get_udp_input()
{
	if (connected) {

		int packetSize = udp.parsePacket();
		if (packetSize)
		{
			// receive incoming UDP packets
			//Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
			int len = udp.read(incoming_packet, 255);
			if (len > 0)
			{
				incoming_packet[len] = 0; // don't know why this is here
			}
			//Serial.printf("UDP packet contents: %s\n", incomingPacket); // Original
			// I had some issues with casting types using Serial.printf(), use Serial.println() instead


			String valueFromPacket = String(incoming_packet); // cast incomingPacket char array to String to use substring()
			//Serial.println("UDP packet contents: " + valueFromPacket);
			// Format coming in: "brt 127" = brightness 127 = first value char is at position 4 (counts from 0)
			int value = valueFromPacket.substring(4, 7).toInt(); // positions 4, 5, and 6 (doesn't include 7)
			// Use this to set the actual parameters, but for Serial.println() they need to be cast to Strings

			String message = valueFromPacket.substring(0, 3);

			Serial.println(valueFromPacket);

			if (message == "brt")
			{
				FastLED.setBrightness(value);
				//Serial.println("Brightness = " + String(value));
			}
			else if (message == "spd")
			{
				//universe.ChangeSpeedFactor((float)value / 40);

				speed_scale_factor_modifier = (float)value / 40.0;

				//Serial.println("Speed = " + String(value));
			}
			else if (message == "hue")
			{
				Animation_Controller::current_animation->change_var(hue, a_value, value);
			}
			else if (message == "hsp")
			{
				Animation_Controller::current_animation->change_var(hue, a_speed, (float)value / 60.0);
			}
			else if (message == "off")
			{
				//universe.ChangeOffset(value);
				//Serial.println("Offset = " + String(value));
			}
			else if (message == "b00")
			{
				//universe.NextPattern();
			}
			else if (message == "b01")
			{
				//universe.PrevPattern();
			}
			else if (message == "t00")
			{
				Animation_Controller::autoplay = (bool)value;
				//universe.ToggleAutoplay();
			}
			else if (message == "b04")
			{
				Animation_Controller::current_animation->change_var(hue, a_value,
					int(Animation_Controller::current_animation->vars(hue, a_value)->value + 16) % 255);
			}
			else if (message == "b05")
			{
				Animation_Controller::current_animation->change_var(hue, a_value, random8());
			}
			else if (message == "str")
			{
				//universe.uStrobeTime = value;
			}
			else if (message == "t01")
			{
				//universe.uStrobe = (bool)value;
			}
			else if (message == "b06")
			{
				//Serial.println(value);
				Animation_Controller::set_transition(Transition_Type(value));
			}
			else if (message == "b07")
			{
				ESP.restart();
			}
			else if (message == "b02")
			{
				//universe.ChangeReflect();
			}
			else if (message == "pat")
			{
				//Serial.println("Pattern = " + String(value));
				//universe.SetPattern(value);

				static int current_ani = Animation_Name(value % NUM_AUTOPLAY_ANIMATIONS);

				//Serial.println(Animation_Name(value % NUM_AUTOPLAY_ANIMATIONS));
				//Serial.println(Animation_Name(ani_controller->current_animation->animations[0]->name));

				if (Animation_Name(value % NUM_AUTOPLAY_ANIMATIONS) != current_ani)
				{
					Animation_Controller::change_animation(Animation_Name(value % NUM_AUTOPLAY_ANIMATIONS));
					current_ani = Animation_Name(value % NUM_AUTOPLAY_ANIMATIONS);
				}
			}
			else if (message == "act")
			{
				//universe.uPower = (bool)value;
			}
			else if (message == "b03")
			{
				//universe.uSlowStart = millis();
				//universe.uSlow = (bool)value;
			}
			else if (message == "del")
			{
				Transition::total_time = value * 40;
			}
			else if (message == "min")
			{
				Animation_Controller::autoplay_min_time = value * 1000;
			}
			else if (message == "max")
			{
				Animation_Controller::autoplay_max_time = value * 1000;
			}

			//Serial.println(valueFromPacket);

		}

	}
	else
	{
		if (millis() > try_again_time && connected == false)
		{
			start_wifi();
		}
	}
}
