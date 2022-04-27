
void loop() {
  afficherHeure();
  verifierWifi();
  publierEtat(verifierChute());
  modifier();
  alertSound();
}
