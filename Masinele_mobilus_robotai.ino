#include <TimerOne.h>
#include <SharpIR.h>
#include <SoftwareSerial.h>


// Pirmas hbridge
// desnys
#define enA 5      // enable line A
#define in1 7      // h bridge valdymo signalai
#define in2 8     // h bridge valdymo signalai
// kairys
#define enB 6    // enable line B
#define in3 9     // h bridge valdymo signalai
#define in4 10     // h bridge valdymo signalai

//  Enkoderiai //////////////////////////////////////////
#define enkoderis_1 A2 // kairys
#define enkoderis_2 A3 // desnys
//is esp8266 valdymas/////////////////////////////////
#define pirmyn 38
#define kaire 42
#define desne 40
#define atgal 44
// ir sensoriai/////////////////////////////////////////
#define IR1 A0  // priekis
#define IR2 A1  // desne
#define model1 1080 // for GP2Y0A21YK0F  used 1080
#define model2 1080 // for GP2Y0A21YK0F  used 1080


/*
2 to 15 cm GP2Y0A51SK0F  use 215
4 to 30 cm GP2Y0A41SK0F / GP2Y0AF30 series  use 430
10 to 80 cm GP2Y0A21YK0F  use 1080
10 to 150 cm GP2Y0A60SZLF use 10150
20 to 150 cm GP2Y0A02YK0F use 20150
100 to 550 cm GP2Y0A710K0F  use 100550
*/
SharpIR IRpin_priekio(IR1, model1);  //  priekis
SharpIR IRpin_desne(IR2, model2);  //  desne

  // Pirmas enkoderis
  int pirmo_enkoderio_verte = 0;
  int pirmo_enkoderio_suma = 0;
  bool pirmo_enkoderio_flegas = false;
  int pirmo_analog_to_digital = 0;
  int pirmas_enkoderis = 0;

  // Antras enkoderis
  int antro_enkoderio_verte = 0;
  int antro_enkoderio_suma = 0;
  bool antro_enkoderio_flegas = false;
  int antro_analog_to_digital = 0;
  int antras_enkoderis = 0;
  
  // Skaiciavimas enkoderiu
  const int ddistance = 100;   // cm
  const int motor_power = 200;      // 0-255
  const int motor_offset = 5;       // Diff. when driving straight
  const float wheel_d = 68;           // Wheel diameter (mm)
  const float wheel_c = PI * wheel_d; // Wheel circumference (mm)
  const int counts_per_rev = 40;   // 
  
////////////////////////////////VAZIAVIMO FLEGAI///////////////////////////////////////
int speeed_kaires = 100;
int speeed_dsnes = 100;

int A = 0;
int B = 0;
int AA = 0;
int BB = 0;
int AAA = 0;

int pirmo_flegas = 0;
int antro_flegas = 0;
int trecio_flegas = 0;
int ketvirto_flegas = 0;
int penkto_flegas = 0;
int sesto_flegas = 0;

int pirmo_skaiciuokle = 0;
int antro_skaiciuokle = 0;
int trecio_skaiciuokle = 0;
int ketvirto_skaiciuokle = 0;
int penkto_skaiciuokle = 0;
int sesto_skaiciuokle = 0;

int pirmo_skaiciuokle_papildoma = 0;
int antro_skaiciuokle_papildoma  = 0;
int trecio_skaiciuokle_papildoma  = 0;
int ketvirto_skaiciuokle_papildoma  = 0;
int penkto_skaiciuokle_papildoma  = 0;
int sesto_skaiciuokle_papildoma  = 0;

///////////////////////////////////////////////////////////////////////////////////////


int dis1_priekis = 0;
int dis2_desne = 0;

void setup()
{
  Serial.begin(9600);
  // motor 1
  pinMode(enA, OUTPUT);   
  pinMode(in1, OUTPUT);     
  pinMode(in2, OUTPUT);    
  // motor 2
  pinMode(enB, OUTPUT);   
  pinMode(in3, OUTPUT);      
  pinMode(in4, OUTPUT);     
 
  //Enkoderiai
  pinMode(enkoderis_1, INPUT);   
  pinMode(enkoderis_2, INPUT);  
  //esp8266 valdymas
  pinMode(pirmyn, INPUT);
  pinMode(kaire, INPUT);
  pinMode(desne, INPUT);
  pinMode(atgal, INPUT);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(IR_sensoriai);
}

void IR_sensoriai(){
  //Timer1.detachInterrupt();
  dis1_priekis = IRpin_priekio.distance();  // this returns the distance for sensor 1
  delay(5);
  dis2_desne = IRpin_desne.distance();  // this returns the distance for sensor 2
  delay(5);
  //Timer1.attachInterrupt(IR_sensoriai);
}

void Pirmas_enkoderis(){
  pirmo_enkoderio_verte = analogRead(enkoderis_1);
  pirmo_analog_to_digital = map(pirmo_enkoderio_verte, 0, 1023, 0, 255);
    Serial.println(pirmo_enkoderio_suma);
    Serial.println("\n");
  if ((pirmo_analog_to_digital >= 8) && (pirmo_enkoderio_flegas == false)) {
    pirmas_enkoderis = HIGH;
    pirmo_enkoderio_flegas = 1;
    pirmo_enkoderio_verte = pirmo_enkoderio_suma + 1 ;
    }
  else if ((pirmo_analog_to_digital >= 8) && (pirmo_enkoderio_flegas == true)){
    }
  else if ((pirmo_analog_to_digital <= 8) && (pirmo_enkoderio_flegas == true)){
    pirmas_enkoderis = LOW;
    pirmo_enkoderio_flegas = 0;
    pirmo_enkoderio_suma = pirmo_enkoderio_suma + 1 ;
    }
  else if ((pirmo_analog_to_digital <= 8) && (pirmo_enkoderio_flegas == false)){
    }
  else {
    Serial.println("something is wrong with first encoder");
    }
  }
  
void Antras_enkoderis(){
  antro_enkoderio_verte = analogRead(enkoderis_2);
  antro_analog_to_digital = map(antro_enkoderio_verte, 0, 1023, 0, 255);
    Serial.println(antro_enkoderio_suma);
    Serial.println("\n");
  if ((antro_analog_to_digital >= 8) && (antro_enkoderio_flegas == false)) {
    antras_enkoderis = HIGH;
    antro_enkoderio_flegas = 1;
    antro_enkoderio_suma = antro_enkoderio_suma + 1 ;
    }
  else if ((antro_analog_to_digital >= 8) && (antro_enkoderio_flegas == true)){
    }
  else if ((antro_analog_to_digital <= 8) && (antro_enkoderio_flegas == true)){
    antras_enkoderis = LOW;
    antro_enkoderio_flegas = 0;
    antro_enkoderio_suma = antro_enkoderio_suma + 1 ;
    }
  else if ((antro_analog_to_digital <= 8) && (antro_enkoderio_flegas == false)){
    }

  else {
    Serial.println("something is wrong with second encoder");
    }
  }
  
  int Target_count(){
  float num_rev = (ddistance * 10) / wheel_c;  // Convert to mm
  unsigned long target_count = num_rev * counts_per_rev;
  return target_count;
  }


void vaziavimo_kryptys_I_prieki(){
  // desnys
  analogWrite(enA, speeed_dsnes);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //kairys
  analogWrite(enB, speeed_kaires);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}
void Stovejimas(){
// desnys
  analogWrite(enA, speeed_dsnes);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //kairys
  analogWrite(enB, speeed_kaires);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
  

void vaziavimo_kryptys_suktis_i_kaire(){
  // desnys
  analogWrite(enA, speeed_dsnes);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //kairys
  analogWrite(enB, speeed_kaires);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void vaziavimo_kryptys_suktis_i_desne(){
  // desnys
  analogWrite(enA, speeed_dsnes);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //kairys
  analogWrite(enB, speeed_kaires);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void vaziavimo_kryptys_atgal(){
  // desnys
  analogWrite(enA, speeed_dsnes);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //kairys
  analogWrite(enB, speeed_kaires);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void Vaziavimas(){    
/////////////////////////////////////////////////////////PIRMAS///////////////////////////////////////////////////////////////

if ((dis1_priekis >= 60) && (dis2_desne >= 25)){  // pirmas ---

  if ((pirmo_flegas == 1) && (pirmo_skaiciuokle >= 0) && (pirmo_skaiciuokle_papildoma == 0)){
  speeed_dsnes = 80;
  speeed_kaires = 80;
  vaziavimo_kryptys_I_prieki();
  
  if (pirmo_skaiciuokle % 2 ) {  // if --even-- than
      Stovejimas(); 
    }
  
  }
  
  
  if (trecio_flegas == 1){
    
  }
  if (ketvirto_flegas == 1){
    
  }
  if (penkto_flegas == 1){
    
  }
  if (pirmo_skaiciuokle_papildoma > 0){  // is 5 ir 6 ateina signalas kad turi prasideti posukis i desne
      speeed_dsnes = 70;
  speeed_kaires = 70;
    vaziavimo_kryptys_suktis_i_desne();
    delay(250);
    pirmo_skaiciuokle_papildoma++;
  //  AA = 1;  // jeigu po 1 veiksmo(bandymo sukti i desne), vel griztama prie 6 didinamas pasukimas i desne
   // BB = 1;  // // jeigu po 1 veiksmo(bandymo sukti i desne), pereinama prie 3 veiksmo didinamas pasukimas i desne
  }
/////////////////////////////
pirmo_flegas = 1;
antro_flegas = 0;
trecio_flegas = 0;
ketvirto_flegas = 0;
penkto_flegas = 0;
sesto_flegas = 0;
/////////////////////////////
antro_skaiciuokle = 0;
trecio_skaiciuokle = 0;
ketvirto_skaiciuokle = 0;
penkto_skaiciuokle = 0;
sesto_skaiciuokle = 0;
///////////////////////////// 
antro_skaiciuokle_papildoma  = 0;
trecio_skaiciuokle_papildoma  = 0;
ketvirto_skaiciuokle_papildoma  = 0;
penkto_skaiciuokle_papildoma  = 0;
sesto_skaiciuokle_papildoma  = 0;
/////////////////////////////   
 pirmo_skaiciuokle++; 
 B = 1;  // kai ivyksta pakibimas sukant i desne

  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////ANTRAS/////////////////////////////////////////////////////////////
if ((dis1_priekis >= 25) && (dis1_priekis <= 60)&& (dis2_desne >= 25)){  // antras --- suletejimas pries priekine kliuti
  
  if (pirmo_flegas == 1) {
    
  }
  
  if ((antro_flegas == 1) && (antro_skaiciuokle >= 0) && (antro_skaiciuokle_papildoma == 0)){
      speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_I_prieki();
    
  if (antro_skaiciuokle % 2 ) {  // if --even-- than
      Stovejimas(); 
    }
    
  antro_skaiciuokle++;
    
  }
  if (trecio_flegas == 1){
    
  }
  if (ketvirto_flegas == 1){
    
  }
  if (penkto_flegas == 1){
    
  }
  if (antro_skaiciuokle_papildoma > 0){  // is 5 ir 6 ateina signalas kad turi prasideti posukis i desne
      speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_suktis_i_desne();
    delay(250);
    antro_skaiciuokle_papildoma++;
   // AA = 1;  // jeigu po 2 veiksmo(bandymo sukti i desne), vel griztama prie 6 didinamas pasukimas i desne
  //  BB = 1;  // jeigu po 2 veiksmo(bandymo sukti i desne), pereinama prie 3 veiksmo didinamas pasukimas i desne
  }
  
/////////////////////////////
pirmo_flegas = 0;
antro_flegas = 1;
trecio_flegas = 0;
ketvirto_flegas = 0;
penkto_flegas = 0;
sesto_flegas = 0;
/////////////////////////////
pirmo_skaiciuokle = 0;
trecio_skaiciuokle = 0;
ketvirto_skaiciuokle = 0;
penkto_skaiciuokle = 0;
sesto_skaiciuokle = 0;
/////////////////////////////
pirmo_skaiciuokle_papildoma = 0;
trecio_skaiciuokle_papildoma  = 0;
ketvirto_skaiciuokle_papildoma  = 0;
penkto_skaiciuokle_papildoma  = 0;
sesto_skaiciuokle_papildoma  = 0;
/////////////////////////////  
A = 1;  // primenama 1, kad nepamirstu sukti i desne uz posukio
B = 1;  // kai ivyksta pakibimas sukant i desne
antro_skaiciuokle++;  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////TRECIAS////////////////////////////////////////////////////////////////
if ((dis1_priekis <= 25) && (dis2_desne >= 25)){  //trecias
  if ((dis1_priekis <= 5) && (dis2_desne >= 25)){  //jeigu triacias prasideda prie sienos
  speeed_dsnes = 80;
  speeed_kaires = 80;
  vaziavimo_kryptys_atgal();
  delay(200);
  vaziavimo_kryptys_suktis_i_kaire();
  delay(400);
  vaziavimo_kryptys_I_prieki(); 
  delay(400); 
  }
  /*
  if (BB > 0) {    // jeigu po 2 arba 1 veiksmo(bandymo sukti i kaire), pereinama prie 3 veiksmo didinamas pasukimas i desne
  speeed_dsnes = 80;
  speeed_kaires = 80;
  vaziavimo_kryptys_suktis_i_kaire();
  delay(500);
  vaziavimo_kryptys_I_prieki(); 
  delay(400);
  vaziavimo_kryptys_suktis_i_desne();
  delay(500);
  vaziavimo_kryptys_I_prieki(); 
  }
  */
  if (antro_flegas == 1){
    
  }

  if ((trecio_flegas == 1) && (trecio_skaiciuokle >= 0)){
     speeed_dsnes = 80;
  speeed_kaires = 80;
vaziavimo_kryptys_suktis_i_kaire();
delay(300);
if (trecio_skaiciuokle % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
    }

   
  }
  if (ketvirto_flegas == 1){
    
  }
  if (penkto_flegas == 1){
    
  }
  if (sesto_flegas == 1){
    
  }
/////////////////////////////
pirmo_flegas = 0;
antro_flegas = 0;
trecio_flegas = 1;
ketvirto_flegas = 0;
penkto_flegas = 0;
sesto_flegas = 0;
/////////////////////////////
pirmo_skaiciuokle = 0;
antro_skaiciuokle = 0;
ketvirto_skaiciuokle = 0;
penkto_skaiciuokle = 0;
sesto_skaiciuokle = 0;
/////////////////////////////
pirmo_skaiciuokle_papildoma = 0;
antro_skaiciuokle_papildoma  = 0;
ketvirto_skaiciuokle_papildoma  = 0;
penkto_skaiciuokle_papildoma  = 0;
sesto_skaiciuokle_papildoma  = 0;
/////////////////////////////  
A = 0;  
B = 0;
AA = 0;
BB = 0;
trecio_skaiciuokle++;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////KETVIRTAS///////////////////////////////////////////////////////////////
if ((dis1_priekis <= 25) &&  (dis2_desne <= 25)){  // ketvirtas
  if ((dis1_priekis <= 7) &&  (dis2_desne <= 30)){  // atgal jei buggas
  speeed_dsnes = 80;
  speeed_kaires = 80;
  vaziavimo_kryptys_atgal();
  delay(300);
  vaziavimo_kryptys_suktis_i_kaire();
  delay(700);
  vaziavimo_kryptys_I_prieki();
  delay(600);
  }
  if (pirmo_flegas == 1) {
    
  }
  if (antro_flegas == 1){
    
  }
  if (trecio_flegas == 1){
    
  }
 
  if ((ketvirto_flegas == 1) && (ketvirto_skaiciuokle >= 0)){
     speeed_dsnes = 80;
  speeed_kaires = 80;
vaziavimo_kryptys_suktis_i_kaire();
delay(300);
if (ketvirto_skaiciuokle % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
    }
    
  }
  if (penkto_flegas == 1){
    
  }
  if (sesto_flegas == 1){
    
  }
/////////////////////////////
pirmo_flegas = 0;
antro_flegas = 0;
trecio_flegas = 0;
ketvirto_flegas = 1;
penkto_flegas = 0;
sesto_flegas = 0;
/////////////////////////////
pirmo_skaiciuokle = 0;
antro_skaiciuokle = 0;
trecio_skaiciuokle = 0;
penkto_skaiciuokle = 0;
sesto_skaiciuokle = 0;
///////////////////////////// 
pirmo_skaiciuokle_papildoma = 0;
antro_skaiciuokle_papildoma  = 0;
trecio_skaiciuokle_papildoma  = 0;
penkto_skaiciuokle_papildoma  = 0;
sesto_skaiciuokle_papildoma  = 1;
/////////////////////////////  
A = 0; 
B = 0;
AA = 0;
BB = 0;
ketvirto_skaiciuokle++;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////PENKTAS///////////////////////////////////////////////////////////
if((dis1_priekis <= 35)&&(dis1_priekis > 25) && (dis2_desne > 25) && (dis2_desne <= 35)){
  speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_suktis_i_desne();
    if (penkto_skaiciuokle_papildoma % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
    }
}
if ((dis1_priekis >= 25) && (dis2_desne >= 10) && (dis2_desne <= 25)){  // penktas
 
  if (B > 1) {  // atvejis kai sukant i desne uz kliuties atsimusa su desniu ratu ir pakimba
    speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_suktis_i_desne();
    if (B % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
      delay(200);
    }
  }

  
  if (antro_flegas == 1){
    
  }
  if (trecio_flegas == 1){
    
  }
  if (ketvirto_flegas == 1){
    
  }
 
  if ((penkto_flegas == 1) && (penkto_skaiciuokle >= 0) && (penkto_skaiciuokle_papildoma ==0)){
  speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_suktis_i_desne();
    if (penkto_skaiciuokle_papildoma % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
    }
  }
  if (penkto_skaiciuokle_papildoma >0 ){ // is sesto ateina, kad nepamestu trasos
   speeed_dsnes = 80;
  speeed_kaires = 80;
    vaziavimo_kryptys_suktis_i_desne();
    
    penkto_skaiciuokle_papildoma++;
    if (penkto_skaiciuokle_papildoma % 2 ) {  // if --even-- than
      vaziavimo_kryptys_I_prieki(); 
      
    }
  }
/////////////////////////////
pirmo_flegas = 0;
antro_flegas = 0;
trecio_flegas = 0;
ketvirto_flegas = 0;
penkto_flegas = 1;
sesto_flegas = 0;
/////////////////////////////
pirmo_skaiciuokle = 0;
antro_skaiciuokle = 0;
trecio_skaiciuokle = 0;
ketvirto_skaiciuokle = 0;
sesto_skaiciuokle = 0;
/////////////////////////////
pirmo_skaiciuokle_papildoma = 1;  // tam kad uzsisuktu uz desnio kampo
antro_skaiciuokle_papildoma  = 1;  // tam kad uzsisuktu uz desnio kampo
trecio_skaiciuokle_papildoma  = 0;
ketvirto_skaiciuokle_papildoma  = 0;
sesto_skaiciuokle_papildoma  = 1;  // pranesa 6, kad katik buvo 5
/////////////////////////////  
A = 0;  
AA = 0;
BB = 0;
penkto_skaiciuokle++;  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////SESTAS//////////////////////////////////////////////////////////
if ((dis1_priekis >= 25) &&  (dis2_desne <= 10)){  //sestas
  if (AA > 0){  // jeigu po 1 veiksmo(bandymo sukti i kaire), vel griztama prie 6 didinamas pasukimas i desne
  speeed_dsnes = 80;
  speeed_kaires = 80;
  vaziavimo_kryptys_I_prieki();
  delay(500);
  vaziavimo_kryptys_suktis_i_desne();
  delay(1000);

  }
  if (pirmo_flegas == 1) {
    
    
  }
  if (antro_flegas == 1){
    
  }
  if (trecio_flegas == 1){
    
  }
  if (ketvirto_flegas == 1){
    
  }
  if (sesto_skaiciuokle_papildoma > 0){  // is penkto ateina, kad kompensuotu krypti
   speeed_dsnes = 80;
  speeed_kaires = 80; 
  vaziavimo_kryptys_I_prieki();
  sesto_skaiciuokle_papildoma++;
  if (sesto_skaiciuokle_papildoma % 2){
    vaziavimo_kryptys_suktis_i_kaire();
  }
  }

  if ((sesto_flegas == 1) && (sesto_skaiciuokle >= 0) && (sesto_skaiciuokle_papildoma==0)){
  speeed_dsnes = 80;
  speeed_kaires = 80;
vaziavimo_kryptys_suktis_i_kaire();
  }
/////////////////////////////
pirmo_flegas = 0;
antro_flegas = 0;
trecio_flegas = 0;
ketvirto_flegas = 0;
penkto_flegas = 0;
sesto_flegas = 1;
/////////////////////////////
pirmo_skaiciuokle = 0;
antro_skaiciuokle = 0;
trecio_skaiciuokle = 0;
ketvirto_skaiciuokle = 0;
penkto_skaiciuokle = 0;
/////////////////////////////
pirmo_skaiciuokle_papildoma = 1;  // tam kad uzsisuktu uz desnio kampo
antro_skaiciuokle_papildoma  = 1;  // tam kad uzsisuktu uz desnio kampo
trecio_skaiciuokle_papildoma  = 0;
ketvirto_skaiciuokle_papildoma  = 0;
penkto_skaiciuokle_papildoma  = 1;  // pranesa 5, kad katik buvo 6
///////////////////////////// 
A = 0; 
B = 0;
BB = 0;
AA = 0;
sesto_skaiciuokle++;


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void esp8266_valdymas(){
  pirmyn1 = digitalRead(pirmyn); 
  kaire1 = digitalRead(kaire); 
  desne1 = digitalRead(desne); 
  atgal1 = digitalRead(atgal); 
  if ((pirmyn1 == HIGH) && (kaire1 == LOW) && (desne1 == LOW) && (atgal1 == LOW)){
    vaziavimo_kryptys_I_prieki();
  }
  else if ((pirmyn1 == LOW) && (kaire1 == HIGH) && (desne1 == LOW) && (atgal1 == LOW)){
    vaziavimo_kryptys_suktis_i_kaire();
  }
  else if ((pirmyn1 == LOW) && (kaire1 == LOW) && (desne1 == HIGH) && (atgal1 == LOW)){
    vaziavimo_kryptys_suktis_i_desne();
  }
  else if ((pirmyn1 == LOW) && (kaire1 == LOW) && (desne1 == LOW) && (atgal1 == HIGH)){
    vaziavimo_kryptys_atgal();
  }
    else
      Stovejimas();   
}
*/

void loop(){
  //esp8266_valdymas();
 // Pirmas_enkoderis();
  //Antras_enkoderis();
  IR_sensoriai();
  Vaziavimas();
  delay(200);
}