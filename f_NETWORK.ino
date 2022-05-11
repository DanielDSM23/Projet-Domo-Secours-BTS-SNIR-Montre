void configurationWifi(){
   WiFi.begin(ssid, password); //configuration wifi
   send_command_to_MP3_player(configurationWifiSound, 6); //envoie données mp3
  Serial.println();
  while ( WiFi.status() != WL_CONNECTED ) { //tentative connexion wifi
    static bool active = true;
    if(active==true){
      Serial.print( "Connecting to " );
      Serial.print(ssid);
      displayText("Wi-Fi..", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
      active = false;
      }
    //animation ecran connexion au wifi
    static unsigned long long previousMillis = millis();
    static uint8_t active2 = 1;
    if(millis() - previousMillis >= 500){ 
      Serial.print ( "." );
      switch(active2){
         case 1:
          displayText("Wi-Fi.", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
          break;
         case 2:
          displayText("Wi-Fi..", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
         case 3:
          displayText("Wi-Fi...", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
      }
      active2++;
      if(active2 > 4){
        active2 = 1;
      }
      previousMillis += 500;
      modifier();//modification via port serie si besoin
    }
  }
    if(WiFi.status() == WL_CONNECTED)//si le wifi est connecte
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println();
      Serial.print("Connected to ");
      Serial.print(ssid);
      Serial.print(". IP : ");
      Serial.println(WiFi.localIP());
      displayText("Connecte!", 2, SCREEN_WIDTH/3-30, SCREEN_HEIGHT/3);
      send_command_to_MP3_player(connecteWifi, 6);
      delay(50);
    
    }
}


void verifierWifi(){
  //verifie si le wifi est connecté durant la fonction loop()
  while(WiFi.status() != WL_CONNECTED){configurationWifi(); afficherFirstHeure();}
}


void setupMqtt(){
  client.setServer(mqttServer, MQTTPORT); //modifie les valeurs du serveur (en String) et du port (en int?)
  unsigned long long previousMillis = millis(); //mise en place d'une attente reactive
  uint8_t active2 = 1;
  while (!client.connected()) {
    if(millis() - previousMillis >= 500){
      Serial.print ( "." );
      switch(active2){ //animation MQTT ecran
         case 1:
          displayText("MQTT.", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
          break;
         case 2:
          displayText("MQTT..", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
         case 3:
          displayText("MQTT...", 2, SCREEN_WIDTH/3-15, SCREEN_HEIGHT/3);
      }
      active2++;
      if(active2 > 4){
        active2 = 1;
      }
      previousMillis += 500;
    }
    Serial.println("Connection au serveur MQTT ...");
    if (client.connect("ESP32Client")) {
      Serial.println("MQTT connecté");
      displayText("MQTT OK!", 2, SCREEN_WIDTH/3-13, SCREEN_HEIGHT/3);
    }
    else {
      Serial.print("echec, code erreur= ");
      Serial.println(client.state());
      displayText("MQTT ERROR!", 2, SCREEN_WIDTH/3-6, SCREEN_HEIGHT/3);
    }
    client.subscribe("esp/sensor/imu/fall"); //souscription au topic "esp/sensor/imu/fall"
    }
}

void publierEtat(bool etat){
  if(etat == true){ //si la personne à chutée
    while(1){ //sort de la fonction loop
      static unsigned long long previousMillis = millis();
      send_command_to_MP3_player(chuteDetectee, 6);
      while(!client.connected()){ //verification de la connexion au mqtt
       setupMqtt(); 
      }
      client.publish("esp/sensor/imu/fall", "personne a terre"); //publication du message
      displayText("Message", 2, SCREEN_WIDTH/3-17, SCREEN_HEIGHT/3);
      addText("envoye!", 2, SCREEN_WIDTH/3-17, 3*SCREEN_HEIGHT/4); //affiche "Message envoye!" sur l'écran
      send_command_to_MP3_player(centraleInforme, 6); //avertie la victime via un message sonore que le mmessage a été envoyé
      displayText("envoie", 2, SCREEN_WIDTH/3-17, SCREEN_HEIGHT/3);
      addText("BDD...", 2, SCREEN_WIDTH/3-17, 3*SCREEN_HEIGHT/4); //affiche "envoie BDD!" sur l'écran
      sendDataSql("chute"); //envoie à la BDD
      alertSoundBool = true; //mise en place d'un avertissement sonore
      delay(1000);
      break;
   }
  }
}


void sendDataSql(String raison){
  String lieu = "chambre";
  if(conn.connect(server_addr, 3306, user, passwordDb)){ //connexion à la BDD
    Serial.println("BDD connectée");
    cursor = new MySQL_Cursor(&conn); //creation d'un nouvel object
    String queryStr="USE domosecours_btssn;\nINSERT INTO `detect_chute` (`info_client_client_id`, `dateHeure`, `raison`, `localisation`) VALUES ('"+String(clientId)+"', SYSDATE(), '"+raison+"', '"+lieu+"');";
    char query[200];
    queryStr.toCharArray(query, 200); //convertion String en char array
    //Serial.println(query);
    Serial.println("envoie BDD...");
    cursor->execute(query); //envoie requête sql
  }
  else{
    Serial.println("BDD non connectée");
  }
}

void getIP(){
  String url = "http://daniel.monteiro1.free.fr/espFall/getIP.php";
  http.begin(espClient, url.c_str());
  int httpResponseCode = http.GET(); 
  if (httpResponseCode>0) {
    String payload = http.getString();
    Serial.println(payload);
  }
  http.end();
}
