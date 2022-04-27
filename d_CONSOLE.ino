

void modifier(){
  String command;
  if(Serial.available()){
        command = Serial.readStringUntil('\n'); 
        if(command.equals("set wifi")){
              displayText("MAJ..", 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
              char * newSsid = ssid;
              char * newPassword = password;
              String strSsid;
              String strPassword;
              String passwordTechStr, oldPasswordTechStr;
              //while(newSsid == ssid && newPassword == password){
              Serial.println("Mot de passe technicien (exit pour sortir):");
              do{
                
                while(passwordTechStr == NULL || oldPasswordTechStr == passwordTechStr){
                  passwordTechStr = Serial.readStringUntil('\n'); 
                }
                if(passwordTechStr == "exit"){
                  configurationWifi();
                }
                passwordTechStr=md5(passwordTechStr);
                if(passwordTechStr == "8652704bc952486f6c273ccdc1cd148c"){
                  Serial.println("OK!");
                }
                else{
                  Serial.println("MDP INCORRECT!");
                }
                oldPasswordTechStr = passwordTechStr;
              }
              while(passwordTechStr != "8652704bc952486f6c273ccdc1cd148c");
              
              Serial.println("put SSID :");
              while(strSsid == NULL){
               strSsid = Serial.readStringUntil('\n'); 
              }
              Serial.println("OK !");
              Serial.println("put password :");
              while(strPassword == NULL){
               strPassword = Serial.readStringUntil('\n'); 
              }
              Serial.println("OK !");
            //}
           Serial.println("modification.");
           strSsid.toCharArray(ssid, 30);
           strPassword.toCharArray(password, 30);
           Serial.println("modification OK.");
           configurationWifi();
        }
        else if(command.equals("set mqtt")){
          displayText("MAJ..", 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
          if(conn.connect(server_addr, 3306, user, passwordDb)){
            Serial.println("BDD connectée");
            cursor = new MySQL_Cursor(&conn);
          }
          else{
            Serial.println("BDD non connectée. Veuillez contacter un admin!");
            setupMqtt();
          }
          String idDB, passDB, oldIdDB, oldPassDB;
          boolean canEnter;
          do{
            Serial.println("Identifiant technicien :");
            while(idDB == NULL || oldIdDB == idDB){
             idDB = Serial.readStringUntil('\n'); 
            }
            Serial.println("MDP technicien :");
            while(passDB == NULL|| oldPassDB == passDB){
             passDB = Serial.readStringUntil('\n'); 
            } 
            String queryStr = "USE domosecours_btssn;\nSELECT Admin_System.nom FROM Admin_System WHERE Admin_System.password = MD5('"+passDB+"') AND Admin_System.login = '"+idDB+"';";
            char query[200];
            queryStr.toCharArray(query, 200);
            cursor->execute(query);
            Serial.println(canEnter);
            oldIdDB = idDB; oldPassDB = passDB;
          }
          while(1);
          
          char * newMqtt = mqttServer;
          String strMqttServer;
          Serial.println("put MQTT Server :");
          while(strMqttServer == NULL){
           strMqttServer = Serial.readStringUntil('\n'); 
          }
          Serial.println("OK !");
          Serial.println("modification.");
          strMqttServer.toCharArray(mqttServer, 30);
          Serial.println("modification OK.");
          setupMqtt();
        }
        else if(command.equals("set ntp")){
          displayText("MAJ..", 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
          char * newNTP = ntpServer;
          String strNetServer;
          Serial.println("put NTP Server :");
          while(strNetServer == NULL){
           strNetServer = Serial.readStringUntil('\n'); 
          }
          Serial.println("OK !");
          Serial.println("modification.");
          strNetServer.toCharArray(mqttServer, 30);
          Serial.println("modification OK.");
          timeClient.setPoolServerName(mqttServer);
          timeClient.update();
        }
        else if(command.equals("getIP")){
          getIP();
        }
        else{
            Serial.println("Invalid command");
        }
  }

}


String md5(String str) {
  _md5.begin();
  _md5.add(String(str));
  _md5.calculate();
  return _md5.toString();
}
