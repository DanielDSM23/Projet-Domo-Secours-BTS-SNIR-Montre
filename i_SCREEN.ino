
void configurationEcran(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  displayText("Bienvenue!", 2, SCREEN_WIDTH/3-40, SCREEN_HEIGHT/3);
  delay(500);   
  displayText("Projet Domo-secours.", 2, SCREEN_WIDTH/3-40, SCREEN_HEIGHT/3);
  delay(500); 
  displayText("Partie", 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
  addText("Daniel M.", 2, SCREEN_WIDTH/3-15, 2*SCREEN_HEIGHT/3);
  delay(500);
}


void afficherHeure(){
  timeClient.update();
  static unsigned long long previousMillis = millis();
  if(timeClient.getMinutes() == nextMinuteHour || timeClient.getMinutes() == 0){
    strcpy(heure, timeClient.getFormattedTimeWithoutSeconds().c_str());
    displayText(heure, 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
    afficherDateStart();
    if(nextMinuteHour == 61){
      nextMinuteHour == 1;
    }
    else{
      nextMinuteHour = timeClient.getMinutes()+1;
    }
  }
  if (millis() - previousMillis >= 1000){
      if(heure[2] == ':'){heure[2] = ' ';}
      else{heure[2] = ':';}
      displayText(heure, 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
      afficherDateStart();
      previousMillis += 1000;
   }
  }


void afficherDateStart(){
  String day = String(timeClient.getDate());
  //sprintf(day, "%d", timeClient.getDate()); // Conversion de l'entier day = mois
  String year = String(timeClient.getYear());
  //sprintf(year, "%d", timeClient.getYear()); // Conversion de l'entier year = annee
  String month;
  String dayWeek;
  //jour de la semaine
  if(timeClient.getDay() == 0){
    dayWeek = "Dimanche";
  }
  if(timeClient.getDay() == 1){
    dayWeek = "Lundi";
  }
  if(timeClient.getDay() == 2){
    dayWeek = "Mardi";
  }
  if(timeClient.getDay() == 3){
    dayWeek = "Mercredi";
  }
  if(timeClient.getDay() == 4){
    dayWeek = "Jeudi";
  }
  if(timeClient.getDay() == 5){
    dayWeek = "Vendredi";
  }
  if(timeClient.getDay() == 6){
    dayWeek = "Samedi";
  }
  if(timeClient.getDay() == 7){
    dayWeek = "Dimanche";
  }
  //mois de l'année
  if(timeClient.getMonth() == 1){
    month = "Janvier";
  }
  if(timeClient.getMonth() == 2){
    month = "Fevrier";
  }
  if(timeClient.getMonth() == 3){
    month = "Mars";
  }
  if(timeClient.getMonth() == 4){
    month = "Avril";
  }
  if(timeClient.getMonth() == 5){
    month = "Mai";
  }
  if(timeClient.getMonth() == 6){
    month = "Juin";
  }
  if(timeClient.getMonth() == 7){
    char month[12]= "Juillet";
  }
  if(timeClient.getMonth() == 8){
    month = "Aout";
  }
  if(timeClient.getMonth() == 9){
    month = "Septembre";
  }
  if(timeClient.getMonth() == 10){
    month = "Octobre";
  }
  if(timeClient.getMonth() == 11){
    month = "Novembre";
  }
  if(timeClient.getMonth() == 12){
    month = "Decembre";
  }
 //conversion
    String dateEntiere = dayWeek + " " +  day + " " + month + " " + year;
    //strcat(dateEntiere,day); strcat(dateEntiere," "); strcat(dateEntiere,month); strcat(dateEntiere," "); strcat(dateEntiere,year);
    char dateEntiereChar[50];
    dateEntiere.toCharArray(dateEntiereChar, 50);
    addText(dateEntiereChar,1 , 0, SCREEN_HEIGHT-10);
}

void afficherFirstHeure(){
    //char *heure = new char[timeClient.getFormattedTimeWithoutSeconds().length() + 1];
    strcpy(heure, timeClient.getFormattedTimeWithoutSeconds().c_str());
    displayText(heure, 2, SCREEN_WIDTH/3-10, SCREEN_HEIGHT/3);
    nextMinuteHour = timeClient.getMinutes();
    Serial.print(timeClient.getFormattedTime());
    Serial.print(" ");
    Serial.print(timeClient.getDate());
    Serial.print("/");
    Serial.print(timeClient.getMonth());
    Serial.print("/");
    Serial.println(timeClient.getYear());
  }

void displayText(char text[], int textSize, int xCursor, int yCursor)
{
  display.clearDisplay();
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(xCursor, yCursor);
  // Display static text
  display.println(text);
  display.display();   
}

void addText(char text[], int textSize, int xCursor, int yCursor){
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(xCursor, yCursor);
  // Display static text
  display.println(text);
  display.display();
}
