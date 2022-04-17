/*
 * System.cpp
 *
 *  Created on: 13 сент. 2019 г.
 *      Author: producer
 */

#include "System.h"

		TextBlock *text;
		TextBlock *AItext;
		TextBlock *DItext;
		unsigned int HW_DI_lastvalue_GPIO35, HW_DI_lastvalue_GPIO0, postext, HW_DI_lastvalue_GPIO26, HW_DI_lastvalue_GPIO27;
		Device::Display::Graphics::t_Graphics *hGraph1;
		uint8_t Ghand1, Ghand2, Ghand3;


System::System() {
	// TODO Auto-generated constructor stub

#ifdef FTP_SERVERESP_H
	//FTP_Server = new Service::FTP::FtpServer();
#endif

	Device::Display::init();
	Device::Display::Graphics::init(TFT_BLUE);
	Fonts=new Device::Display::Graphics::Font();
	Fonts->setTextColor(0x000000);
	text=new(TextBlock);
	AItext=new(TextBlock);
	DItext=new(TextBlock);
	Device::Hardware::init();

	Device::Display::Graphics::t_Coordinate2D 	boxcords;
	Device::Display::Graphics::t_Size2D			boxsize;
	Device::Display::Graphics::t_color_r8g8b8	fgcolor,
												bgcolor;
	fgcolor.r=255;
	fgcolor.g=255;
	fgcolor.b=255;
	bgcolor.r=0;
	bgcolor.g=0;
	bgcolor.b=255;

	boxcords.x = 5;
	boxcords.y = 20;
	boxsize.width = 85;
	boxsize.height = 110;


	Device::Hardware::Bus->addDI(GPIO35, &System::handler);
	Device::Hardware::Bus->addDI(GPIO0, &System::handler);
	Device::Hardware::Bus->addDI(GPIO26, &System::handler);
	Device::Hardware::Bus->addAI(GPIO27, &System::handler);

	hGraph1 = new(Device::Display::Graphics::t_Graphics);
	hGraph1->ID=0;
	hGraph1->position.x=5;
	hGraph1->position.y=20;
	hGraph1->size.width=85;
	hGraph1->size.height=110;
	hGraph1->callbackHandler=&System::hGraphics;
	Ghand1 = Graph->registerHandler(hGraph1); // For GPIO35 and GPIO0
	hGraph1->position.x=10;
	hGraph1->position.y=130;
	hGraph1->size.width=85;
	hGraph1->size.height=16;
	Ghand2= Graph->registerHandler(hGraph1); // For GPIO26
	AItext->setPosition(hGraph1->position.x, hGraph1->position.y);
	AItext->setSize(hGraph1->size.width, hGraph1->size.height);
	hGraph1->position.x=10;
	hGraph1->position.y=150;
	hGraph1->size.width=85;
	hGraph1->size.height=16;
	Ghand3 = Graph->registerHandler(hGraph1); // For GPIO27
	DItext->setPosition(hGraph1->position.x, hGraph1->position.y);
	DItext->setSize(hGraph1->size.width, hGraph1->size.height);

	AItext->setBGColor(bgcolor);
	AItext->setFGColor(fgcolor);
	AItext->setLineSpace(3);
	AItext->setSymbolSpace(2);
	AItext->setTextFont(2);
	AItext->setTextColor(TFT_WHITE,TFT_BLUE);
	AItext->setTextSize(1);
	AItext->setMoveWholeWord(true);
	AItext->setSkipFistSpace(true);
	AItext->setText("N\\A");

	DItext->setBGColor(bgcolor);
	DItext->setFGColor(fgcolor);
	DItext->setLineSpace(3);
	DItext->setSymbolSpace(2);
	DItext->setTextFont(2);
	DItext->setTextColor(TFT_WHITE,TFT_BLUE);
	DItext->setTextSize(1);
	DItext->setMoveWholeWord(true);
	DItext->setSkipFistSpace(true);
	DItext->setText("N\\A");

	text->setBGColor(bgcolor);
	text->setFGColor(fgcolor);
	text->setPosition(boxcords.x, boxcords.y);
	text->setSize(boxsize.width, boxsize.height);
	text->setLineSpace(3);
	text->setSymbolSpace(2);
	text->setTextFont(2);
	text->setTextColor(TFT_WHITE,TFT_BLUE);
	text->setTextSize(1);
	text->setMoveWholeWord(true);
	text->setSkipFistSpace(true);


	HW_DI_lastvalue_GPIO0=1;
	HW_DI_lastvalue_GPIO35=1;
	HW_DI_lastvalue_GPIO26=1;
	HW_DI_lastvalue_GPIO27=4095;
	postext = 0;

}

System::~System() {
	// TODO Auto-generated destructor stub
	//delete (tft);
	//~text();
	Device::Display::remove();

}

#ifdef _BLUETOOTH_SERIAL_H_
//#include "../modules/Bluetooth.cpp"
void System::BTInit() {
	this->BTbegin("ESP32-Autohome"); //Bluetooth device name
	Serial.println("[Bluetooth] started!");
}

bool System::BTbegin(String localName = String()) { //String localName){//
	return SerialBT.begin(localName);
}

int System::BTavailable(void) {
	return SerialBT.available();
}

int System::BTpeek(void) {
	return SerialBT.peek();
}

bool System::BThasClient(void) {
	return SerialBT.hasClient();
}

int System::BTread(void) {
	return SerialBT.read();
}

size_t System::BTwrite(uint8_t c) {
	return SerialBT.write(c);
}

size_t System::BTwrite(const uint8_t *buffer, size_t size) {
	return SerialBT.write(buffer, size);
}

void System::BTflush() {
	SerialBT.flush();
}

void System::BTend(void) {
	SerialBT.end();
}

esp_err_t System::BTregister_callback(esp_spp_cb_t *callback) {
	return SerialBT.register_callback(callback);
}

#endif

#ifdef WiFiClientSecure_h
//#include "../modules/WiFiClient.cpp"

void System::WFAPInit() {
#include "../../wf.pass"

	//contains initialization for ssid and password for wifi
	WiFi.begin(ssid, password);

	// attempt to connect to Wifi network:
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
#ifdef _BLUETOOTH_SERIAL_H_
		this->BTwrite((const unsigned char*) ".", 1);
#endif
		// wait 1 second for re-trying
		delay(1000);
	}
#ifdef _BLUETOOTH_SERIAL_H_
	this->BTwrite((const unsigned char*) "WiFiConnected", 13);
#endif

}

IPAddress System::WFlocalIP() {
	return WiFi.localIP();
}

#endif

void System::DrawPng() {



	Serial.printf("\nstart draw\n");
	int maxfiles = 1;
	char *filenames[maxfiles] = { "/t.png"};//, "/24wifi.png", "/t.png"};
	//char xx = 0, yy = 0;
	//const char *string = "bhe";
	//const char *texttext = "hblahblah that is fun, that text do not fit all blocxk. and errors in text";
	//t_DispCoords hbox = 53;

	AItext->Draw();

	DItext->Draw();

	text->setText("  hblahblah   that is fun, that text do not fit all blocxk. and errors in text");

	for (int numfiles = 0; numfiles < maxfiles; numfiles++) {
#ifdef GRAPH_PNG
		Device::Display::uPNG::uPNG->DrawFile(filenames[numfiles], 80, 100);
#endif
		//Fonts->setFreeFont(&Device::Display::Graphics::FreeMono9pt7b);
		//Fonts->setTextFont(1);
		//Fonts->drawGlyph((uint16_t)'x', 20, 25);
/*		Fonts->setTextFont(2);
		Fonts->setTextColor(TFT_WHITE, TFT_BLUE);
		Fonts->setTextSize(4);
		Fonts->drawChar((uint16_t)'y', (t_DispCoords)2, (t_DispCoords)45);
		Fonts->setTextColor(TFT_WHITE, TFT_BLACK);
		Fonts->setTextSize(3);
		Fonts->drawChar((uint16_t)'X', 4, 45);
		Fonts->setTextColor(TFT_DARKGREEN, TFT_BLUE);
		Fonts->setTextSize(2);
		Fonts->drawChar((uint16_t)'y', 5, 33);
// 		Fonts->drawString(texttext,52,100);

		Fonts->drawNumber((long int)Fonts->textWidthFit(string,2,hbox), 52, 150);

*/		Serial.printf("Text->Draw()\n");
//		text->drawString(string, 2, 2);
//		Fonts->drawNumber((long int)text->textWidthFit(string,2,hbox), 52, 180);
		text->Draw();

	}
}

void System::handler(Device::Hardware::t_Data * data){
	// test hardware
	int rvalue=0;
	rvalue = (int)(*(int *)data->data);

	if (data->pin == GPIO35){

		if(rvalue != HW_DI_lastvalue_GPIO35){
			if(rvalue==0){
				postext++;//else postext--;

//				Graph->fillRect(hGraph1->position.x, hGraph1->position.y, hGraph1->size.width, hGraph1->size.height, TFT_BLUE);
				text->Clear();
				hGraph1->ID=Ghand1;
				Graph->redraw(Ghand1);
				text->Draw(0,postext);
			}
		}
		HW_DI_lastvalue_GPIO35=rvalue;
	}
	if (data->pin == GPIO0){

		if(rvalue != HW_DI_lastvalue_GPIO0){
			if(rvalue==0){
				postext--;//else postext--;

//				Graph->fillRect(hGraph1->position.x, hGraph1->position.y, hGraph1->size.width, hGraph1->size.height, TFT_BLUE);
				text->Clear();
				hGraph1->ID=Ghand1;
				Graph->redraw(Ghand1);
				text->Draw(0,postext);
			}
		}
		HW_DI_lastvalue_GPIO0=rvalue;

	}

	if (data->pin == GPIO26){

		if(rvalue != HW_DI_lastvalue_GPIO26){
			if(rvalue==0)
				DItext->setText("false");
			else
				DItext->setText("true");
//			Graph->fillRect(hGraph3->position.x, hGraph3->position.y, hGraph3->size.width, hGraph3->size.height, TFT_BLUE);
//			hGraph3->ID=Ghand3;
			DItext->Clear();
			Graph->redraw(Ghand3);
			DItext->Draw();

		}
		HW_DI_lastvalue_GPIO26=rvalue;

	}
	if (data->pin == GPIO27){
		rvalue = ((4095 - rvalue)>>4)*100/255;
		if(rvalue != HW_DI_lastvalue_GPIO27){
			std::string tmp_ss = std::to_string(rvalue);
			AItext->setText((char const *)tmp_ss.c_str());
//			Graph->fillRect(hGraph2->position.x, hGraph2->position.y, hGraph2->size.width, hGraph2->size.height, TFT_BLUE);
			AItext->Clear();
//			hGraph2->ID=Ghand2;
			Graph->redraw(Ghand2);
			AItext->Draw();

		}
		HW_DI_lastvalue_GPIO27=rvalue;

	}


}

void System::hGraphics(Device::Display::Graphics::t_Graphics * data) {
	if(data->ID != Ghand1){
		text->Draw(0,postext);
	}
	if(data->ID != Ghand2){
		DItext->Draw();
	}
	if(data->ID != Ghand3){
		AItext->Draw();
	}
}

