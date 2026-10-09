#define debug Serial
#define DEBUG 1

#if DEBUG == 1
#define debug_print(x) debug.print(x)
#define debug_println(x) debug.println(x)
#else
#define debug_print(x)
#define debug_println(x)
#endif

// devices status
#define NONE      0
#define STARTING  1
#define WARMUP    2
#define RUNNING   3
#define COOLDOWN  4
#define STOPPING  5
#define STOPPED   6

#define RELAY_ON 0
#define RELAY_OFF 1

#define TRASHOLE_MIN 3

#define HEATER_PIN 17       // MOSFET1
#define VENT_PIN 18         // MOSFET2
#define MOSFET3_PIN 26      // MOSFET3
#define MOSFET4_PIN 27      // MOSFET4

// temperature and humidity AM2305
#define DHTPIN 14
#define DHTTYPE DHT22

// UART1 for Display
#define NEXTION_RX 35  // Connect to Nextion TX
#define NEXTION_TX 32  // Connect to Nextion RX

// 1 while the dryer cycle is running, 0 when idle or stopped
#define POWER_LED 23