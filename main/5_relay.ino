void setUpRelay(){
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, HIGH);

    pinMode(VENT_PIN, OUTPUT);
    digitalWrite(VENT_PIN, HIGH);

    pinMode(DEVICE_PIN, OUTPUT);
    digitalWrite(DEVICE_PIN, DEVICE_OFF);
}

void setRelayStatus(int pin, int action){
    digitalWrite(pin, action);   
}
