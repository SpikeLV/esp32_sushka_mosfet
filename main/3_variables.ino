// string readed from Display
String tmp_action = "";
uint8_t tmp_time = 0;
uint8_t tmp_temp = 0;

uint8_t action_time = 0;  // timer in minutes to run (from Display)
uint8_t action_temp = 0;  // temperature settings (from Display)

volatile uint32_t lastIsrAt5 = millis();
volatile uint32_t timer_running = millis();

uint8_t action_status = NONE;
uint8_t heater_status = RELAY_OFF;

// AM2305
DHT dht(DHTPIN, DHTTYPE);
int8_t curent_temp = 0;
uint8_t curent_humi = 0;
float temp_t;
float temp_h;


// Nextion
String nextion_action = "";
uint8_t nextion_action_timer = 0;
uint8_t nextion_action_temp = 0;
uint8_t one_min = 0;
uint8_t dispay_sec = 0;