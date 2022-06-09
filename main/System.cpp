/*
 * System.cpp
 *
 *  Created on: 13 сент. 2019 г.
 *      Author: producer
 */
#include "System.h"


#include "nvs_flash.h"
#define DEFAULT_SCAN_LIST_SIZE 10

static const char *TAG = "scan";

static void print_auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
        break;
    case WIFI_AUTH_WEP:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
        break;
    case WIFI_AUTH_WPA_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
        break;
    case WIFI_AUTH_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
        break;
    default:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
        break;
    }
}

static void print_cipher_type(int pairwise_cipher, int group_cipher)
{
    switch (pairwise_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    default:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }

    switch (group_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    default:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }
}

/* Initialize Wi-Fi as sta and set scan method */
static void wifi_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    //ESP_ERROR_CHECK(esp_event_loop_create_default());
    //esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    //assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
        ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
        ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
        print_auth_mode(ap_info[i].authmode);
        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
        }
        ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
    }

}



		TextBlock *text;
		TextBlock *AItext;
		TextBlock *DItext;
		unsigned int HW_DI_lastvalue_GPIO35, HW_DI_lastvalue_GPIO0, postext, HW_DI_lastvalue_GPIO26, HW_DI_lastvalue_GPIO27;
		Device::Display::Graphics::t_Graphics *hGraph1;
		uint8_t Ghand1, Ghand2, Ghand3;

		tcpip_adapter_ip_info_t System::ip;
		TextBlock *IPlistHeader;
		TextBlock *STAinfo;
		TextBlock *APinfo;
		uint8_t h_IPlistHeader, handlerSTAlist, handlerAPlist;


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
	Device::Hardware::IO_init();
#ifndef WiFiClientSecure_h
	Device::Hardware::Network::WiFi_init();
	//Device::Hardware::Network::WiFi->startSTA();
	//Device::Hardware::Network::WiFi->startAP();
#endif
    memset(&ip, 0, sizeof(esp_netif_ip_info_t));
    vTaskDelay(2000 / portTICK_PERIOD_MS);

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


	Device::Hardware::IO->addDI(GPIO0, &System::handler);
	Device::Hardware::IO->addDI(GPIO35, &System::handler);
//	io->addDI(GPIO26, &System::handler);
//	Device::Hardware::Bus->addAI(GPIO35, &System::handler);

	text->setSymbolSpace(2);
	text->setTextFont(2);
	text->setTextSize(1);
	text->setText("moisture:\nas\nasd asdf");
	hGraph1 = new(Device::Display::Graphics::t_Graphics);
	hGraph1->ID=0;
	hGraph1->position.x=5;
	hGraph1->position.y=20;
	hGraph1->size.width=text->getWidth();
	hGraph1->size.height=text->fontHeight();
	hGraph1->callbackHandler=&System::hGraphics;
	Ghand1 = Graph->registerHandler(hGraph1); // For GPIO35 and GPIO0
	text->setBGColor(bgcolor);
	text->setFGColor(fgcolor);
	text->setPosition(hGraph1->position.x, hGraph1->position.y=20);
	text->setSize(hGraph1->size.width, text->height());
	text->setLineSpace(3);
	text->setTextColor(TFT_WHITE,TFT_BLUE);
	text->setMoveWholeWord(true);
	text->setSkipFistSpace(true);


	AItext->setBGColor(bgcolor);
	AItext->setFGColor(fgcolor);
	AItext->setLineSpace(3);
	AItext->setSymbolSpace(2);
	AItext->setTextFont(2);
	AItext->setTextColor(TFT_WHITE,TFT_BLUE);
	AItext->setTextSize(1);
	AItext->setMoveWholeWord(true);
	AItext->setSkipFistSpace(true);
	AItext->setText("N\\A ");
	hGraph1->position.x=text->getPosition().x + text->getWidth()+2;
	hGraph1->position.y=text->getPosition().y;
	hGraph1->size.width=AItext->getWidth();
	hGraph1->size.height=AItext->fontHeight();
	Ghand2= Graph->registerHandler(hGraph1); // For GPIO26
	AItext->setPosition(hGraph1->position.x, hGraph1->position.y);
	AItext->setSize(hGraph1->size.width, hGraph1->size.height);



	DItext->setBGColor(bgcolor);
	DItext->setFGColor(fgcolor);
	DItext->setLineSpace(3);
	DItext->setSymbolSpace(2);
	DItext->setTextFont(2);
	DItext->setTextColor(TFT_WHITE,TFT_BLUE);
	DItext->setTextSize(1);
	DItext->setMoveWholeWord(true);
	DItext->setSkipFistSpace(true);
	DItext->setText("false");
	hGraph1->position.x=10;
	hGraph1->position.y=150;
	hGraph1->size.width=DItext->getWidth();
	hGraph1->size.height=DItext->fontHeight();
	Ghand3 = Graph->registerHandler(hGraph1); // For GPIO27
	DItext->setPosition(hGraph1->position.x, hGraph1->position.y);
	DItext->setSize(hGraph1->size.width, hGraph1->size.height);



	HW_DI_lastvalue_GPIO0=1;
	HW_DI_lastvalue_GPIO35=1;
	HW_DI_lastvalue_GPIO26=1;
	HW_DI_lastvalue_GPIO27=4095;
	postext = 0;



	// Next part of code initializes TextBlocks for STAlist information
	STAinfo=new(TextBlock);
	IPlistHeader=new(TextBlock);


	//STAinfo->setBGColor(bgcolor);
	//STAinfo->setFGColor(fgcolor);
	STAinfo->setLineSpace(2);
	STAinfo->setSymbolSpace(1);
	STAinfo->setTextFont(2);
	STAinfo->setTextColor(TFT_WHITE,TFT_BLUE);
	STAinfo->setTextSize(1);
	STAinfo->setMoveWholeWord(true);
	STAinfo->setSkipFistSpace(true);
	STAinfo->setText("");
	STAinfo->setSize(Graph->width(), (STAinfo->fontHeight()+1)*8);
	STAinfo->setPosition(0, STAinfo->fontHeight()+1);
	hGraph1->position.x=STAinfo->getPosition().x;
	hGraph1->position.y=STAinfo->getPosition().y;
	hGraph1->size.width=STAinfo->getWidth();
	hGraph1->size.height=STAinfo->fontHeight();
	handlerSTAlist= Graph->registerHandler(hGraph1);

	IPlistHeader->setLineSpace(0);
	IPlistHeader->setSymbolSpace(1);
	IPlistHeader->setTextFont(2);
	IPlistHeader->setTextColor(TFT_WHITE,TFT_BLUE);
	IPlistHeader->setTextSize(1);
	IPlistHeader->setMoveWholeWord(true);
	IPlistHeader->setSkipFistSpace(true);
	IPlistHeader->setText("");
	IPlistHeader->setSize(Graph->width(), IPlistHeader->fontHeight()+1);
	IPlistHeader->setPosition(0, 1);
	hGraph1->position.x=IPlistHeader->getPosition().x;
	hGraph1->position.y=IPlistHeader->getPosition().y;
	hGraph1->size.width=IPlistHeader->getWidth();
	hGraph1->size.height=IPlistHeader->fontHeight();
	h_IPlistHeader = Graph->registerHandler(hGraph1);


	// Next block for APlist information
	APinfo=new(TextBlock);
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
	WiFi.begin(CONFIG_ESP32_SYSTEM_HW_NETWORK_WIFI_STA_SSID,CONFIG_ESP32_SYSTEM_HW_NETWORK_WIFI_STA_PASSWORD);//ssid, password);

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

//	AItext->Draw();

//	DItext->Draw();

    //IPlistHeader->setText("Client list:");
    IPlistHeader->Draw();

	for (int numfiles = 0; numfiles < maxfiles; numfiles++) {
#ifdef CONFIG_ESP32_SPIDISPLAY_GRAPHICS_PNG
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
//		text->Draw();
//		STAinfo->Draw();

	}
}

void System::InitModbus(){
	mbtcp=new(Device::Hardware::Modbus_TCP);

	mbtcp->initializeParameters(7);

	bool b_result = mbtcp->createParam(0, CID_INP_DATA_0, STR("Data_channel_0"), STR("Volts"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 0, 2,
            INPUT_OFFSET(input_data0),
			PARAM_TYPE_FLOAT, 4,
			OPTS( -10, 10, 1 ),
			PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(1, CID_HOLD_DATA_0, STR("Humidity_1"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 0, 2,\
            HOLD_OFFSET(holding_data0), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(2, CID_INP_DATA_1, STR("Temperature_1"), STR("C"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 2, 2,\
            INPUT_OFFSET(input_data1), PARAM_TYPE_FLOAT, 4, OPTS( -40, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(3, CID_HOLD_DATA_1, STR("Humidity_2"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 2, 2,\
            HOLD_OFFSET(holding_data1), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(4, CID_INP_DATA_2, STR("Temperature_2"), STR("C"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 4, 2,\
            INPUT_OFFSET(input_data2), PARAM_TYPE_FLOAT, 4, OPTS( -40, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(5, CID_HOLD_DATA_2, STR("Humidity_3"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 4, 2,\
            HOLD_OFFSET(holding_data2), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(6, CID_RELAY_P1, STR("RelayP1"), STR("on/off"), MB_DEVICE_ADDR1, MB_PARAM_COIL, 0, 8,\
            COIL_OFFSET(coils_port0), PARAM_TYPE_U16, 2, OPTS( BIT1, 0, 0 ), PAR_PERMS_READ_WRITE_TRIGGER);
	b_result = mbtcp->createParam(7, CID_RELAY_P2, STR("RelayP2"), STR("on/off"), MB_DEVICE_ADDR1, MB_PARAM_COIL, 8, 8,\
            COIL_OFFSET(coils_port1), PARAM_TYPE_U16, 2, OPTS( BIT0, 0, 0 ), PAR_PERMS_READ_WRITE_TRIGGER);
//	b_result = mbtcp->createParam(8, );
    // { CID, Param Name, Units, Modbus Slave Addr, Modbus Reg Type, Reg Start, Reg Size, Instance Offset, Data Type, Data Size, Parameter Options, Access Mode}
/*
//     { CID_INP_DATA_0, STR("Data_channel_0"), STR("Volts"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 0, 2,
                    INPUT_OFFSET(input_data0), PARAM_TYPE_FLOAT, 4, OPTS( -10, 10, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
//    { CID_HOLD_DATA_0, STR("Humidity_1"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 0, 2,
            HOLD_OFFSET(holding_data0), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
//    { CID_INP_DATA_1, STR("Temperature_1"), STR("C"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 2, 2,
            INPUT_OFFSET(input_data1), PARAM_TYPE_FLOAT, 4, OPTS( -40, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
//    { CID_HOLD_DATA_1, STR("Humidity_2"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 2, 2,
            HOLD_OFFSET(holding_data1), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
4    { CID_INP_DATA_2, STR("Temperature_2"), STR("C"), MB_DEVICE_ADDR1, MB_PARAM_INPUT, 4, 2,
            INPUT_OFFSET(input_data2), PARAM_TYPE_FLOAT, 4, OPTS( -40, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
5    { CID_HOLD_DATA_2, STR("Humidity_3"), STR("%rH"), MB_DEVICE_ADDR1, MB_PARAM_HOLDING, 4, 2,
            HOLD_OFFSET(holding_data2), PARAM_TYPE_FLOAT, 4, OPTS( 0, 100, 1 ), PAR_PERMS_READ_WRITE_TRIGGER },
6    { CID_RELAY_P1, STR("RelayP1"), STR("on/off"), MB_DEVICE_ADDR1, MB_PARAM_COIL, 0, 8,
            COIL_OFFSET(coils_port0), PARAM_TYPE_U16, 2, OPTS( BIT1, 0, 0 ), PAR_PERMS_READ_WRITE_TRIGGER },
7    { CID_RELAY_P2, STR("RelayP2"), STR("on/off"), MB_DEVICE_ADDR1, MB_PARAM_COIL, 8, 8,
            COIL_OFFSET(coils_port1), PARAM_TYPE_U16, 2, OPTS( BIT0, 0, 0 ), PAR_PERMS_READ_WRITE_TRIGGER }
*/

}

void System::handler(Device::Hardware::t_Data * data){
	// test hardware
	int rvalue=0;
	rvalue = (int)(*(int *)data->data);

	if (data->pin == GPIO35){

		if(rvalue != HW_DI_lastvalue_GPIO35){
			if(rvalue==0){
		        if (Device::Hardware::Network::WiFi->getAPIPInfo(&ip)){//esp_netif_get_ip_info(Device::Hardware::Network::class_WiFi::ap_netif, &ip) == 0) {
		            ESP_LOGW("System", "~~~~~~~~~~~");
		            ESP_LOGW("System", "IP:"IPSTR, IP2STR(&ip.ip));
		            ESP_LOGW("System", "MASK:"IPSTR, IP2STR(&ip.netmask));
		            ESP_LOGW("System", "GW:"IPSTR, IP2STR(&ip.gw));
		            ESP_LOGW("System", "~~~~~~~~~~~");
		        }


		        wifi_sta_list_t stalist;
		        tcpip_adapter_sta_list_t ipInfoList;
		        if (Device::Hardware::Network::WiFi->STAlist(&stalist)){
		        	if (Device::Hardware::Network::WiFi->STAlistIPInfo(&stalist, &ipInfoList)){
			        	char textContent[256] = {0,};
			        	memset(&textContent,0,256);
			        	char tmp[17] = {0,};
			        	int tmp_pos = 0;

			        	IPlistHeader->setText("Client list:");
			        	IPlistHeader->Clear();
			        	IPlistHeader->Draw();

			        	for (int tmp_num=0; tmp_num<ipInfoList.num;tmp_num++) {

			        		snprintf(tmp, 17, IPSTR"\n",IP2STR(&ipInfoList.sta[tmp_num].ip));
			        		memcpy(&textContent[tmp_pos],&tmp,strlen(tmp) );
							tmp_pos += strlen(tmp) + 1;
			        	}


			        	STAinfo->Clear();
			        	STAinfo->setText(textContent);
			        	STAinfo->Draw();
		        	}



		        	//text->setText(textContent);

		        }

	//			postext++;//else postext--;

//				Graph->fillRect(hGraph1->position.x, hGraph1->position.y, hGraph1->size.width, hGraph1->size.height, TFT_BLUE);
				//text->Clear();
	//			hGraph1->ID=Ghand1;
		        //Graph->redraw(Ghand1);
				//text->Draw(0,postext);
			}
		}
		HW_DI_lastvalue_GPIO35=rvalue;
	}
	if (data->pin == GPIO0){

		if(rvalue != HW_DI_lastvalue_GPIO0){
			if(rvalue==0){

		        if (Device::Hardware::Network::WiFi->getSTAIPInfo(&ip)) {
		            ESP_LOGW("System", "~~~~~~~~~~~");
		            ESP_LOGW("System", "IP:"IPSTR, IP2STR(&ip.ip));
		            ESP_LOGW("System", "MASK:"IPSTR, IP2STR(&ip.netmask));
		            ESP_LOGW("System", "GW:"IPSTR, IP2STR(&ip.gw));
		            ESP_LOGW("System", "~~~~~~~~~~~");
		        }


	//			postext--;//else postext--;

//				Graph->fillRect(hGraph1->position.x, hGraph1->position.y, hGraph1->size.width, hGraph1->size.height, TFT_BLUE);
	//			text->Clear();
	//			hGraph1->ID=Ghand1;
	//			Graph->redraw(Ghand1);
	//			text->Draw(0,postext);
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
		//text->Draw(0,postext);
	}
	if(data->ID != Ghand2){
	//	DItext->Draw();
	}
	if(data->ID != Ghand3){
	//	AItext->Draw();
	}

	if(data->ID !=h_IPlistHeader){
		IPlistHeader->Draw();
	}
}



