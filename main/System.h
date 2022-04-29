/*
 * System.h
 *
 *  Created on: 13 сент. 2019 г.
 *      Author: producer
 */

//********** Activating services **********
//#define SERVICE_FTP			// FTP-server
//#define SERVICE_WEB		// Web-server
//#define SERVICE_BT			// Bluetooth
//#define SERVICE_WIFI		// WiFi non-secure. If SERVICE_WIFISEC defined, then secure wifi will be active
//#define SERVICE_WIFISEC		// WiFi secure


//********** End of services **********

#ifndef MAIN_SYSTEM_H_
	#define MAIN_SYSTEM_H_

	//#define FTP_DEBUG

	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "esp_task_wdt.h"
	#include <Arduino.h>
	#include <FS.h>
	#include "ESP32_SPIDisplay.h"
	#include "Graphics.h"
	#include "Touch.h"

#include "Font.h"

	#include "Types.h"

	#include "Extensions/cBuffer.h"
	#include "Extensions/TextBlock.h"
	#include "ESP32_System.h"
#include "Extensions/Network/wifi/WiFi.h"
#include "Extensions/IO.h"

//	#include <SPI.h>
//	#include <ESPmDNS.h>

	#ifdef SERVICE_FTP
		#include "FtpServer.h"
	#endif

	#ifdef SERVICE_WEB
		#include "WebService.h"
	#endif

	#ifdef SERVICE_BT
		#include <BluetoothSerial.h>
	#endif

	#ifdef SERVICE_WIFISEC
		#include <WiFiClientSecure.h>
	#else
		#ifdef SERVICE_WIFI
			#include <WiFi.h>
			#include <WiFiClient.h>
		#endif
	#endif

	#define TFT_GREY 0x5AEB // New colour

#ifdef GRAPH_PNG
	#include "upng.h"
	using Device::Display::uPNG::uPNG;
#endif

using Device::Display::Graphics::Graph;
using namespace Device::Display;
using Device::Display::Graphics::TextBlock;

class System {


		private:
			#ifdef _BLUETOOTH_SERIAL_H_
				#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
					#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
				#else
					BluetoothSerial SerialBT;
				#endif
			#endif

			#ifdef WiFiClientSecure_h
				WiFiClientSecure WiFi_client;
			#endif
				Device::Display::Graphics::Font *Fonts;

		public:
			#ifdef _BLUETOOTH_SERIAL_H_
				#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
					#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
				#else

					void BTInit();

					bool BTbegin(String);
					int BTavailable(void);
					int BTpeek(void);
					bool BThasClient(void);
					int BTread(void);
					size_t BTwrite(uint8_t c);
					size_t BTwrite(const uint8_t *buffer, size_t size);
					void BTflush();
					void BTend(void);
					esp_err_t BTregister_callback(esp_spp_cb_t * callback);

				#endif

			#endif

			#ifdef WiFiClientSecure_h
				void WFAPInit();
				IPAddress WFlocalIP();
			#endif


				void DrawPng();

		System();
		virtual ~System();



		handler_type handler(Device::Hardware::t_Data * data); //defining by user for Hardware usage
		handler_type hGraphics(Device::Display::Graphics::t_Graphics * data);
		//void InitFS();

	};







#endif /* MAIN_SYSTEM_H_ */
