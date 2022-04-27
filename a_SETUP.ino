void setup() {
  configurationPin();
  configurationEcran();
  Serial.println("Accelerometer Found!");
  configurationAccelerometre();
  erreurIMU();
  msa.read();
  prevz = msa.z;
  configurationWifi();
  timeClient.update();
  nextMinuteHour = timeClient.getMinutes()+1;
  setupMqtt();
  afficherFirstHeure();
  afficherDateStart();
}
