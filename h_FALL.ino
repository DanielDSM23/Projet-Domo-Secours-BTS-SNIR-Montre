bool detectionChute(){
  msa.read(); 
  sensors_event_t event; 
  msa.getEvent(&event);
  if((prevz + 3000 < msa.z || prevz - 3000 > msa.z) && (event.acceleration.z > 12 || event.acceleration.z < 8)){
      return true;
    }
  else{
    return false;
  }
}


bool verifierChute(){
  int numberElements = 5;
  numberOfTimeLoop++;
  bool finalState;
  if(numberOfTimeLoop >numberElements){
    numberOfTimeLoop = 0;
  }
  stateValue[numberOfTimeLoop] = detectionChute();
  if((stateValue[0] & stateValue[1] & stateValue[2] & stateValue[3] & stateValue[4]) == 1){
    finalState = true;
  }
  else{
    finalState = false;
  }
  digitalWrite(LED_BUILTIN, !finalState);
  if(finalState == true){
    displayText("CHUTE !", 2, SCREEN_WIDTH/3-13, SCREEN_HEIGHT/3);
    afficherFirstHeure();
  }
  return finalState;
}
