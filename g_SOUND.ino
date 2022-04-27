 void alertSound(){
  static unsigned long long previousMillis = millis();
  if(alertSoundBool == true){
    if(millis() - previousMillis >= 3000){
      send_command_to_MP3_player(alert, 6);
      addText("chute detectee!", 1, SCREEN_WIDTH, 0);
      previousMillis+=3000;
    }
 }
 }



 void send_command_to_MP3_player(int8_t command[], int len){
  for(int i=0;i<len;i++){ MP3.write(command[i]); }
  delay(1000);
}
