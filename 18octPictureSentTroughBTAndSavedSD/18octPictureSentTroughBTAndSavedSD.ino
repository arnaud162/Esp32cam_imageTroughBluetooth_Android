/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-cam-take-photo-save-microsd-card
  
  IMPORTANT!!! 
   - Select Board "AI Thinker ESP32-CAM"
   - GPIO 0 must be connected to GND to upload a sketch
   - After connecting GPIO 0 to GND, press the ESP32-CAM on-board RESET button to put your board in flashing mode
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include "setup.h"
  BluetoothSerial SerialBT;


void setup() {
  setupCameraAndSDCard();

Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

/*  
  // Take Picture with Camera
     camera_fb_t * fb = NULL; 
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
  pictureNumber = EEPROM.read(0) + 1;

  // Path where new picture will be saved in SD Card
  String path = "/picture" + String(pictureNumber) +".jpg";

  fs::FS &fs = SD_MMC; 
  Serial.printf("Picture file name: %s\n", path.c_str());
  
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file in writing mode");
  } 
  else {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.printf("Saved file to path: %s\n", path.c_str());
    EEPROM.write(0, pictureNumber);
    EEPROM.commit();
  }
  file.close();
  esp_camera_fb_return(fb); 
  
  // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  rtc_gpio_hold_en(GPIO_NUM_4);
  
  delay(2000);
  Serial.println("Going to sleep now");
  delay(2000);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");*/
}



void loop() {
  if (Serial.available()) {
    String readFromSerial = Serial.readString();
    Serial.print(readFromSerial);
    if(readFromSerial.equals("p\n")){
      Serial.printf("about to take photo");
      SerialBT.print("about to take photo\n");
      camera_fb_t * fb = NULL; 
      fb = esp_camera_fb_get();
      SerialBT.write(fb->buf,fb->len);
      esp_camera_fb_return(fb); 
      SerialBT.print("finished sending photo");
    }
    else{
      Serial.printf("not about to take photo");
      SerialBT.print(readFromSerial);
    }
  }

  if (SerialBT.available()) { //receving from smartphone, not used here
    Serial.write(SerialBT.read());
  }
  delay(20);
  
}
