void setAM2305(){
    dht.begin();
}

void getTemp_and_Humi(){
    temp_t = dht.readTemperature();
    temp_h = dht.readHumidity();

    // Check if any reads failed and exit early (to try again).
    if ( isnan(temp_h) || isnan(temp_t) || temp_t>100 ) {
        debug_println(F("Failed to read from DHT sensor!"));    
        return;
    }
    curent_temp = (int)temp_t;
    curent_humi = (int)temp_h;
}
