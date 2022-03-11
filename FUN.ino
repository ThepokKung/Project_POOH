void Read_SOIL() {
  sensor_Value = analogRead(Sensor);

  Serial.print("Sensor = ");
  Serial.print(sensor_Value);
  Serial.print(">>>");

  Soil_Value = map(sensor_Value, 0, 1023, 100, 0);
  Serial.print("Soil Mositure = ");
  Serial.print(Soil_Value);
  Serial.println("%");
}

void save_data() {
  doc["deviceid"] = deviceid;
  doc["sensor_Value"] = sensor_Value;
  doc["Soil_Value"] = Soil_Value;
}

void send_data() {
  /* json flie */
  for (int i = 5; i > -1; i--) {
    delay(1000);
    Serial.println("Countdown" + String(i));
    Serial.println("Check_time : " + String(check_time));
    check_time++;
  }
  if (check_time >= 15) {
    save_data();
    /* MQTT Send to mqtt*/
    MQTT_senddata();
    /* Reset */
    check_time = 0;
  }
}

void working() {
  if ( millis() - last_time > period) {
    last_time = millis();
    if (Soil_Value <= 50)
    {
      digitalWrite(Relay, HIGH);
      delay(7000);
    }
    else
    {
      digitalWrite(Relay, LOW);
    }
  }
}

void Setup_WM() {
  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  //wm.resetSettings();

  /*
  for (int i = 5; i > -1; i--) {
    delay(1000);
    lcd.print("Press For Res WM");
    int But_S = digitalRead(Pull_But);
    Serial.print("Time out in : ");
    lcd.print("Timeout in : ");
    Serial.println(i);
    lcd.setCursor(13, 1);
    lcd.print(i);
    Serial.print("Button Status : ");
    Serial.println(But_S);
    if (But_S == HIGH) {
      wm.resetSettings();
      lcd.setCursor(0, 1);
      lcd.print("Reset WM Waiting");
      break;
    }
    Serial.println("=======");
  }
  */

  bool res;
  res = wm.autoConnect("Project_2_64");

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
}
