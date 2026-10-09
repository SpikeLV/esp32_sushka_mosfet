void setUpRelay(){
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, HIGH);

    pinMode(VENT_PIN, OUTPUT);
    digitalWrite(VENT_PIN, HIGH);
}

void setRelayStatus(int pin, int action){
    digitalWrite(pin, action);   
}
