void configurationPin(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  MP3.begin(9600);
  send_command_to_MP3_player(select_SD_card, 5);
  send_command_to_MP3_player(soundConfig, 5);
  send_command_to_MP3_player(bienvenue, 6);
}
