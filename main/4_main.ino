HardwareSerial nextionSerial(1);

void setup() {
    debug.begin(115200);
    debug_println("Shkaf R.032-mosfet"); // relay for ventilation and heating logic
    
    //Serial2.begin(9600); // pins 33 rx, 32 tx, 9600 bps, 8 bits no parity 1 stop bit

    nextionSerial.begin(9600, SERIAL_8N1, NEXTION_RX, NEXTION_TX);
    
    Nextion_send_Str("loading.txt=\"Loading relay\"");
    setUpRelay();
    delay(500);

    Nextion_send_Str("loading.txt=\"Loading sensor\"");
    
    setAM2305();
    delay(500);

    getTemp_and_Humi();
    Nextion_displayTemperature(curent_temp);
    Nextion_displayHumidity(curent_humi);

    delay(500);
    Nextion_setScreen();
}

void loop() {
    Nextion_read();

//  -------- Reading sensor each X seconds
    if ((millis() - lastIsrAt5) > 2000) {
        lastIsrAt5 = millis();
        getTemp_and_Humi();
        
        Nextion_displayTemperature(curent_temp);
        Nextion_displayHumidity(curent_humi);
    }
    if(lastIsrAt5>millis()){
        lastIsrAt5 = 0;
    }
    
    
///  ----------- info form DISPLAY
    if(nextion_action.indexOf("VENT_ON") != -1){
        setRelayStatus(VENT_PIN, RELAY_ON);
    }
    if(nextion_action.indexOf("VENT_OFF") != -1){
        setRelayStatus(VENT_PIN, RELAY_OFF);
    }
    
    if(nextion_action.indexOf("STARTING") != -1){
        nextion_action_temp = Nextion_readVal(nextion_action, 2);
        nextion_action_timer = Nextion_readVal(nextion_action, 1);
        debug.print("nextion_action_temp = ");
        debug.println(nextion_action_temp);
        
        debug.print("nextion_action_timer = ");
        debug.println(nextion_action_timer);

        action_status = STARTING;
        digitalWrite(DEVICE_PIN, DEVICE_ON);
        debug.println("STARTING");
    }
    if(nextion_action.indexOf("STOPPING") != -1){
        nextion_action_timer = 0;
        action_status = STOPPING;
        debug.print(nextion_action);
        debug.print(" = ");
        debug.println("STOP");
    }

///   ----    ACTIONS 
    if( action_status == STARTING ){
        if( curent_temp < nextion_action_temp ){
            action_status = WARMUP; 
            setRelayStatus(VENT_PIN, RELAY_OFF);
            setRelayStatus(HEATER_PIN, RELAY_ON);
            heater_status=RELAY_ON;
            debug.println("WARMUP");
        }
    }
    
    if( action_status == WARMUP ){
        if( curent_temp >= nextion_action_temp){
            action_status = RUNNING;
            Nextion_send_Int("p_live.run_time.pco", 65535);
            Nextion_send_Int("p_live.action_temp.pco", 65535);
            one_min = 0;
            debug.println("RUNNING");
        }
    }
    
    if( action_status == RUNNING ){
        if ((millis() - timer_running) > 1000) {
            timer_running = millis();
            one_min += 1;
            dispay_sec = map(one_min, 0, 60, 0, 100);
            Nextion_send_Int("p_live.tim_sec.val",dispay_sec);
            if(one_min == 60){
                nextion_action_timer -= 1;
                one_min = 0;
                Nextion_displayTime(nextion_action_timer);
            }
        }
        
        if(timer_running>millis()){
            timer_running = 0;
        }

        if(nextion_action_timer == 0){
            action_status = STOPPING;
        }

        if( (curent_temp>=nextion_action_temp) && (heater_status==RELAY_ON) ){
            setRelayStatus(HEATER_PIN, RELAY_OFF);
            setRelayStatus(VENT_PIN, RELAY_ON);
            heater_status = RELAY_OFF;
            Nextion_send_Int("p_live.action_temp.pco", 65535);
            
            debug.println("HEATER_PIN, RELAY_OFF");
        }
        if( (curent_temp<=nextion_action_temp-TRASHOLE_MIN) && (heater_status==RELAY_OFF)){
            setRelayStatus(HEATER_PIN, RELAY_ON);
            setRelayStatus(VENT_PIN, RELAY_OFF);
            heater_status = RELAY_ON;
            Nextion_send_Int("p_live.action_temp.pco", 35921);
            
            debug.println("HEATER_PIN, RELAY_ON");
            
        }   
    }
    if( action_status == STOPPING ){
        setRelayStatus(VENT_PIN, RELAY_OFF);
        setRelayStatus(HEATER_PIN, RELAY_OFF);
        digitalWrite(DEVICE_PIN, DEVICE_OFF);
        heater_status = RELAY_OFF;
        action_status = STOPPED;
        dispay_sec = 0;

        Nextion_setScreen();
    }
}
