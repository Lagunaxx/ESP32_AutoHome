/* ############################################################################
 *
 * ESP32-AutoHome project
 * 	Made for automation process for plants, flowers, etc.
 *
 * Creator: Novoselov Vitaliy
 * Author URI: https://github.com/lagunax
 * Project URI: https://github.com/lagunax/ESP32-AutoHome
 *
 * Info:
 * 	Project created for chipsets ESP32
 * 	Official Web site (URI): https://www.espressif.com/en/products/hardware/esp32/overview
 * 	Official Github URI: https://github.com/espressif/esp-idf
 * 	Arduino add-on Github URI: https://github.com/espressif/arduino-esp32
 *
 * 	Hardware tested:
 * 		TTGO-T-Display (got from  Aliexpress.com)
 *
 */ // ############################################################################

#include "System.h"

System *sys;


TaskHandle_t loopTaskHandle = NULL;
//System *sys;
//Service::FTP::FtpServer ftpSrv;   //set #define FTP_DEBUG in ESP8266FtpServer.h to see ftp verbose on serial

Device::Memory::c_Buffer *testBuffer;

#if CONFIG_AUTOSTART_ARDUINO

bool loopTaskWDTEnabled;

using Device::Display::Graphics::t_Size2D;

void setup() {

	Serial.begin(115200);

	sys = new System();
	testBuffer = new Device::Memory::c_Buffer(2,sizeof(t_DispCoords),10,10);
	t_DispCoords ttestValue=11, *testReturn;

	void *testbuf;
	t_Size2D *pos=new t_Size2D();
	t_Size2D *szs = new t_Size2D();

	Serial.println("\nBuffer test:\n");
	for (int xx=0;xx<10;xx++) {
		for (int yy=0;yy<10;yy++) {
			testBuffer->set(&ttestValue,xx,yy);
			Serial.printf("%i\t",(int)ttestValue);
			ttestValue++;
		}
		Serial.print("\n");
	}

	Serial.print("\n-------\n");
	pos->width=2;
	pos->height=3; //+ready
	szs->width=6;
	szs->height=5;
	testbuf=testBuffer->copyBuffer((void*)pos,(void*)szs);
	Serial.print("\n-------\n");
	for (int yy=0;yy<szs->height;yy++) {
		for (int xx=0;xx<szs->width;xx++) {
			memcpy(&ttestValue,testbuf+(xx*testBuffer->getUnitSize()+yy*szs->width*testBuffer->getUnitSize()),testBuffer->getUnitSize());
			//testBuffer->set(&testValue,xx,yy);
			Serial.printf("%i\t",(int)ttestValue);
		}
		Serial.print("\n");
	}

// f_srcpos
	Serial.println("\nEnd Buffer test.\n");
// */
	SPIFFS.begin(true);
	//sys->tft->println("SPIFFS");

#ifdef _BLUETOOTH_SERIAL_H_
	sys->BTInit();
	//sys->tft->println("BT");
#endif

#ifdef WiFiClientSecure_h
	sys->WFAPInit();
	//sys->tft->println("WiFi");
#endif

#ifdef SERVICE_WEB
	Service::HTTP::Start();
	//sys->tft->println("HTTP");
#endif
#ifdef SERVICE_FTP
	Service::FTP::Start("user", "pass");
	//sys->tft->println("FTP");
#endif

	//sys->tft->fillScreen(TFT_BLACK);

	sys->DrawPng();

}

void loop() {

#ifdef _BLUETOOTH_SERIAL_H_
	//Bluetooth module

//		if (sys->BTavailable()) {
//			sys->BTwrite(Serial.read());
//		}
	/*		if (sys->BTavailable()) {
	 input=sys->BTread();
	 //Serial.printf("\ninput=%i pos=%i",input, (int) pos);
	 if ((input>=48)&&(input<=49)){
	 *(buff+pos)=(char)input-48;
	 pos++;
	 }
	 if ((pos>31)||(input==13)){
	 pos=0;
	 //sys->BTwrite((const unsigned char *)"\n",1);
	 for(byte ipos=0;ipos<31;ipos++){
	 //Serial.printf("\n buff=%i | %i",(int) *(buff+ipos),(int)(((char)*(buff+ipos))*pow((double)2,(double)ipos)));
	 *color+=(((char)*(buff+ipos))*pow((double)2,(double)ipos));
	 }
	 //Serial.printf("\ncolor=%i",color);
	 color_R8G8B8toR5G6B5(Color16b, Color24b);
	 Serial.printf("\ncolor=%i",*(int*)Color24b);
	 Serial.printf("\ncolor16=%i\n",*(int*)Color16b);

	 for (int xx=70;xx<100;xx++){
	 for (int yy=70;yy<100;yy++){
	 sys->tft->drawPixel(xx,yy,*(unsigned int*)Color16b);
	 }
	 }
	 for(byte ipos=0;ipos<31;ipos++){
	 *(buff+ipos)=0;
	 }
	 //color=0;
	 }
	 }

	 */

	//testi=sys->BTread();
	//Serial.write(input);
	//sys->BTwrite((const unsigned char *)"test",4);
	//sys->BTwrite(testi);

#endif

#ifdef SERVICE_FTP
	Service::FTP::Handle();
#endif
#ifdef SERVICE_WEB
	Service::HTTP::Handle();
#endif
	Device::Hardware::Handle(); //Bus->run(); // ToDo: make Handle() like in FTP and HTTP
	delay(10);
}

//Starting Programm

void loopTask(void *pvParameters) {
	setup();
	for (;;) {
		if (loopTaskWDTEnabled) {
			esp_task_wdt_reset();
		}
		loop();
	}
}

extern "C" void app_main() {
	loopTaskWDTEnabled = true; //false;
	initArduino();
	xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 1, &loopTaskHandle,
			CONFIG_ARDUINO_RUNNING_CORE);
}

#endif

