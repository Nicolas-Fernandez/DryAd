//PROJET DRYADE//
//PROTOTYPE SUR ARDUINO//
//AUTEUR FERNANDEZ NICOLAS//

////////////////////////////////////////////////////////////////////////////////////

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

char msgtop[16] = "";
char msgbot[16] = "";
char msgsun[16] = "";
char msgheure[16] = "";
char msgminute[16] = "";
char msgseconde[16] = "";
char msgjour[16] = "";
char msgmois[16] = "";

const int LED_RED = 5;
const int LED_GRE = 6;
const int LED_YEL = 7;
int seconde,minute,heure,jour,mois,decennie,annee;
long horloge;
long eco_screen;
long timer_capt;

const int Piezo = A2;
int noteFreqArr[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};

int NOTE_B0 = 31;
int NOTE_C1 = 33;
int NOTE_CS1 = 35;
int NOTE_D1 = 37;
int NOTE_DS1 = 39;
int NOTE_E1 = 41;
int NOTE_F1 = 44;
int NOTE_FS1 = 46;
int NOTE_G1 = 49;
int NOTE_GS1 = 52;
int NOTE_A1 = 55;
int NOTE_AS1 = 58;
int NOTE_B1 = 62;
int NOTE_C2 = 65;
int NOTE_CS2 = 69;
int NOTE_D2 = 73;
int NOTE_DS2 = 78;
int NOTE_E2 = 82;
int NOTE_F2 = 87;
int NOTE_FS2 = 93;
int NOTE_G2 = 98;
int NOTE_GS2 = 104;
int NOTE_A2 = 110;
int NOTE_AS2 = 117;
int NOTE_B2 = 123;
int NOTE_C3 = 131;
int NOTE_CS3 = 139;
int NOTE_D3 = 147;
int NOTE_DS3 = 156;
int NOTE_E3 = 165;
int NOTE_F3 = 175;
int NOTE_FS3 = 185;
int NOTE_G3 = 196;
int NOTE_GS3 = 208;
int NOTE_A3 = 220;
int NOTE_AS3 = 233;
int NOTE_B3 = 247;
int NOTE_C4 = 262;
int NOTE_CS4 = 277;
int NOTE_D4 = 294;
int NOTE_DS4 = 311;
int NOTE_E4 = 330;
int NOTE_F4 = 349;
int NOTE_FS4 = 370;
int NOTE_G4 = 392;
int NOTE_GS4 = 415;
int NOTE_A4 = 440;
int NOTE_AS4 = 466;
int NOTE_B4 = 494;
int NOTE_C5 = 523;
int NOTE_CS5 = 554;
int NOTE_D5 = 587;
int NOTE_DS5 = 622;
int NOTE_E5 = 659;
int NOTE_F5 = 698;
int NOTE_FS5 = 740;
int NOTE_G5 = 784;
int NOTE_GS5 = 831;
int NOTE_A5 = 880;
int NOTE_AS5 = 932;
int NOTE_B5 = 988;
int NOTE_C6 = 1047;
int NOTE_CS6 = 1109;
int NOTE_D6 = 1175;
int NOTE_DS6 = 1245;
int NOTE_E6 = 1319;
int NOTE_F6 = 1397;
int NOTE_FS6 = 1480;
int NOTE_G6 = 1568;
int NOTE_GS6 = 1661;
int NOTE_A6 = 1760;
int NOTE_AS6 = 1865;
int NOTE_B6 = 1976;
int NOTE_C7 = 2093;
int NOTE_CS7 = 2217;
int NOTE_D7 = 2349;
int NOTE_DS7 = 2489;
int NOTE_E7 = 2637;
int NOTE_F7 = 2794;
int NOTE_FS7 = 2960;
int NOTE_G7 = 3136;
int NOTE_GS7 = 3322;
int NOTE_A7 = 3520;
int NOTE_AS7 = 3729;
int NOTE_B7 = 3951;
int NOTE_C8 = 4186;
int NOTE_CS8 = 4435;
int NOTE_D8 = 4699;
int NOTE_DS8 = 4978;

int Melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int NoteDurations[] = {4, 8, 8, 4,4,4,4,4 };
int ThisNote = 0;
int NoteDuration = 1000/NoteDurations[ThisNote];
int PauseBetweenNotes = NoteDuration * 1.30;

const int CaptTemp = A3;
int CaptTempValue = 0;
int UCaptTempValue = 0;
int TempValue = 0;
int TempMemValue = 0;
int TempMax = 0;
int TempMin = 0;

const int CaptHydro = A4;
int CaptHydroValue = 0;
int UCaptHydroValue = 0;
int HydroValue = 0;
int HydroMemValue = 0;
int HydroMax = 0;
int HydroMin = 0;

const int CaptLumi = A5;
int CaptLumiValue = 0;
int UCaptLumiValue = 0;
int LumiValue = 0;
int LumiMemValue = 0;
int LumiMax = 0;
int LumiMin = 0;

const int BoutLeft = 0;
const int BoutRight = 2;
const int BoutUp = 1;
const int BoutDown = 3;
const int BoutOk = 4;
int EtBoutLeft;
int EtBoutRight;
int EtBoutUp;
int EtBoutDown;
int EtBoutOk;
int MemBoutLeft = HIGH;
int MemBoutRight = HIGH;
int MemBoutUp = HIGH;
int MemBoutDown = HIGH;
int MemBoutOk = HIGH;

int Menu = 0;

byte degre[8] ={
B01110,
B01010,
B01110,
B00000,
B00000,
B00000,
B00000,};

byte percent[8] ={
B11101,
B10101,
B11110,
B00100,
B01111,
B10101,
B10111,};

byte water[8] ={    
B00100,
B01010,
B01010,
B10001,
B10111,
B10111,
B10001,
B01110,};

byte smiley2[8] ={
B00000,
B11000,
B00100,
B00010,
B00001,
B01101,
B01101,
B00001,};

byte smiley3[8] ={
B10000,
B10100,
B10100,
B10011,
B01000,
B00100,
B00011,
B00000,};

byte smiley4[8] ={
B00001,
B00101,
B00101,
B11001,
B00010,
B00100,
B11000,
B00000,};

byte flower1[8] ={
B00011,
B00100,
B01010,
B10001,
B10001,
B01010,
B00100,
B00011,};

byte flower2[8] ={
B11000,
B00100,
B01010,
B10001,
B10001,
B01010,
B00100,
B11000,};

byte flower3[8] ={
B00001,
B00001,
B11101,
B11101,
B00011,
B00001,
B00001,
B11111,};

byte flower4[8] ={
B10000,
B10111,
B10111,
B11000,
B10000,
B10000,
B10000,
B11111,};

////////////////////////////---_SETUP_---//////////////////////////////////////////

void setup()
{
lcd.createChar(0,degre);
lcd.createChar(1,percent);
lcd.createChar(2,water);
lcd.createChar(3,smiley2);
lcd.createChar(4,flower1);
lcd.createChar(5,flower2);
lcd.createChar(6,flower3);
lcd.createChar(7,flower4);
lcd.begin(16,2);

pinMode(BoutLeft,INPUT);
pinMode(BoutRight,INPUT);
pinMode(BoutUp,INPUT);
pinMode(BoutDown,INPUT);
pinMode(BoutOk,INPUT);

pinMode(LED_GRE,OUTPUT);
pinMode(LED_RED,OUTPUT);
pinMode(LED_YEL,OUTPUT);
pinMode(Piezo,OUTPUT);

TempMax = 25;
TempMin = 15;
HydroMax = 5;
HydroMin = 1;
LumiMax = 5;
LumiMin = 1;

Menu = 10;

}
/////////////////////////////////---_LOOP_---///////////////////////////////////////

void loop()
{
  
//FORMULES--------------------------------------------------------------------------
annee = 2000 + decennie; 

//BORNES_LIMITTES-------------------------------------------------------------------
if(UCaptLumiValue < 350){LumiValue = 0;}
else{if(UCaptLumiValue <= 1000){LumiValue = 1;}
else{if(UCaptLumiValue <= 2000){LumiValue = 2;}
else{if(UCaptLumiValue <= 3000){LumiValue = 3;}
else{if(UCaptLumiValue <= 4000){LumiValue = 4;}
else{if(UCaptLumiValue <= 5000){LumiValue = 5;}}}}}}

if(TempMax > 60){TempMax = -20;}if(TempMax < -20){TempMax = 60;}
if(TempMin > 60){TempMin = -20;}if(TempMin < -20){TempMin = 60;}
if(HydroMax > 100){HydroMax = 0;}if(HydroMax < 0){HydroMax = 100;}
if(HydroMin > 100){HydroMin = 0;}if(HydroMin < 0){HydroMin = 100;}
if(LumiMax > 5){LumiMax = 1;}if(LumiMax < 1){LumiMax = 5;}
if(LumiMin > 5){LumiMin = 1;}if(LumiMin < 1){LumiMin = 5;}

if(heure > 23){heure = 00;}if(minute > 59){minute = 00;}
if(heure < 00){heure = 23;}if(minute < 00){minute = 59;}
if(jour > 31){jour = 01;}if(mois > 12){mois = 01;}if(decennie > 99){decennie = 00;}
if(jour < 01){jour = 31;}if(mois < 01){mois = 12;}if(decennie < 00){decennie = 99;}

//SON---------------------------------------------------------------------------
if(((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW))||((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW))||((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW))||((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW))||((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW))
  ){
    
 for (int ThisNote = 0; ThisNote < 8; ThisNote++) {
    tone(Piezo, ThisNote, NoteDuration);
    delay(PauseBetweenNotes);
    noTone(Piezo);}
    
    

}

//ALARMES---------------------------------------------------------------------------
digitalWrite(LED_RED, HIGH);
digitalWrite(LED_YEL, HIGH);
digitalWrite(LED_GRE, HIGH);
if(TempValue < TempMin || TempValue > TempMax){digitalWrite(LED_RED, LOW);}
if(HydroValue < HydroMin || HydroValue > HydroMax){digitalWrite(LED_GRE, LOW);}
if(LumiValue < LumiMin || LumiValue > LumiMax){digitalWrite(LED_YEL, LOW);}

//HORLOGE---------------------------------------------------------------------------
if((millis() - horloge) > 1000){horloge = millis();seconde++;}
if(seconde == 60){seconde = 00;minute++;}
if(minute == 60){minute = 00;heure++;}
if(heure == 24){heure = 00;jour++;}
if(jour == 32){jour = 01;mois++;}
if(mois == 13){mois = 01;annee++;}

//CAPTEURS--------------------------------------------------------------------------
//CAPT_TEMP
CaptTempValue = analogRead(CaptTemp);
UCaptTempValue = map (CaptTempValue, 0, 1023, 0, 5000);
TempValue = ((UCaptTempValue - 500) / 10) + 2;
//CAPT_HYDRO
CaptHydroValue = analogRead(CaptHydro);
HydroValue = map(CaptHydroValue, 0, 1023, 0, 100);
//CAPT_LUMI
CaptLumiValue = analogRead(CaptLumi);
UCaptLumiValue = map (CaptLumiValue, 0, 1023, 0, 5000);
if(UCaptLumiValue < 350){sprintf(msgsun,"                ");}
  else{if(UCaptLumiValue <= 1000){sprintf(msgsun,"       *        ");}
    else{if(UCaptLumiValue <= 2000){sprintf(msgsun,"      * *       ");}
      else{if(UCaptLumiValue <= 3000){sprintf(msgsun,"     * * *      ");}
        else{if(UCaptLumiValue <= 4000){sprintf(msgsun,"    * * * *     ");}
          else{if(UCaptLumiValue <= 5000){sprintf(msgsun,"   * * * * *    ");}}}}}}



////////////////////////////////////////---_ACTION_BOUTONS_---///////////////////////////////////////////////////////////
//ECONOMIE_ECRAN---------------------------------------------------------------------------------------------------------
if(Menu == 00){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){Menu = 10;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){Menu = 10 ;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 10;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 10;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 10;eco_screen = millis();}MemBoutOk = EtBoutOk;
//BIENVENUE--------------------------------------------------------------------------------------------------------------
}else{if(Menu == 10){
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 20;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 50;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 00;eco_screen = millis();}MemBoutOk = EtBoutOk;
//TEMPERATURE------------------------------------------------------------------------------------------------------------
}else{if(Menu == 20){
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 30;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 10;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 21;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_TEMP_MAX-------------------------------------------------------------------------------------------------------
}else{if(Menu == 21){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){TempMax--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){TempMax++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 22;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 22;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 20;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_TEMP_MIN-------------------------------------------------------------------------------------------------------
}else{if(Menu == 22){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){TempMin--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){TempMin++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 21;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 21;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 20;eco_screen = millis();}MemBoutOk = EtBoutOk;

//HYDROMETRIE-------------------------------------------------------------------------------------------------------------
}else{if(Menu == 30){
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 40;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 20;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 31;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_HYDRO_MAX-------------------------------------------------------------------------------------------------------
}else{if(Menu == 31){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){HydroMax--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){HydroMax++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 32;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 32;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 30;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_HYDRO_MIN------------------------------------------------------------------------------------------------------
}else{if(Menu == 32){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){HydroMin--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){HydroMin++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 31;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 31;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 30;eco_screen = millis();}MemBoutOk = EtBoutOk;

//LUMINOSITE-------------------------------------------------------------------------------------------------------------
}else{if(Menu == 40){
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 50;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 30;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 41;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_LUMI_MAX-------------------------------------------------------------------------------------------------------
}else{if(Menu == 41){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){LumiMax--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){LumiMax++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 42;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 42;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 40;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_LUMI_MIN-------------------------------------------------------------------------------------------------------
}else{if(Menu == 42){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){LumiMin--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){LumiMin++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 41;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 41;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 40;eco_screen = millis();}MemBoutOk = EtBoutOk;

//HORLOGE---------------------------------------------------------------------------------------------------------------
}else{if(Menu == 50){
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 10;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 40;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 51;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_HEURE----------------------------------------------------------------------------------------------------------
}else{if(Menu == 51){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){heure--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){heure++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 52;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 55;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 50;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_MINUTE----------------------------------------------------------------------------------------------------------
}else{if(Menu == 52){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){minute--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){minute++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 53;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 51;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 50;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_JOUR----------------------------------------------------------------------------------------------------------
}else{if(Menu == 53){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){jour--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){jour++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 54;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 52;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 50;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_MOIS----------------------------------------------------------------------------------------------------------
}else{if(Menu == 54){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){mois--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){mois++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 55;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 53;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 50;eco_screen = millis();}MemBoutOk = EtBoutOk;
//REGLAGE_ANNEE----------------------------------------------------------------------------------------------------------
}else{if(Menu == 55){
EtBoutDown = digitalRead(BoutDown);
if((EtBoutDown != MemBoutDown) && (EtBoutDown == LOW)){decennie--;eco_screen = millis();}MemBoutDown = EtBoutDown;
EtBoutUp = digitalRead(BoutUp);
if((EtBoutUp != MemBoutUp) && (EtBoutUp == LOW)){decennie++;eco_screen = millis();}MemBoutUp = EtBoutUp;
EtBoutRight = digitalRead(BoutRight);
if((EtBoutRight != MemBoutRight) && (EtBoutRight == LOW)){Menu = 51;eco_screen = millis();}MemBoutRight = EtBoutRight;
EtBoutLeft = digitalRead(BoutLeft);
if((EtBoutLeft != MemBoutLeft) && (EtBoutLeft == LOW)){Menu = 54;eco_screen = millis();}MemBoutLeft = EtBoutLeft;
EtBoutOk = digitalRead(BoutOk);
if((EtBoutOk != MemBoutOk) && (EtBoutOk == LOW)){Menu = 50;eco_screen = millis();}MemBoutOk = EtBoutOk;

}}}}}}}}}}}}}}}}}

//AFFICHAGE_MENU--------------------------------------------------------------
//if((millis() - eco_screen) > 10000){eco_screen = millis();Menu = 00;}
switch (Menu){

//ECONOMIE_ECRAN
case 00:
lcd.clear();
break;

//BIENVENUE
case 10:
lcd.setCursor(0,0);
lcd.write((uint8_t) 4);
lcd.write((uint8_t) 5);
lcd.print("ProjetDryade");
lcd.write((uint8_t) 4);
lcd.write((uint8_t) 5);
lcd.setCursor(0,1);
lcd.write((uint8_t) 6);
lcd.write((uint8_t) 7);
lcd.print(" Bienvenue  ");
lcd.write((uint8_t) 6);
lcd.write((uint8_t) 7);
break;

//TEMPERATURE--------------------------------------------------------------
case 20:
lcd.setCursor(0,0);
lcd.print("  Temperature   ");
lcd.setCursor(0,1);
sprintf(msgbot,"     %3d",TempValue);
lcd.write(msgbot);
lcd.write((uint8_t) 0);
lcd.print("C      ");
break;
//TEMPERATURE_MAX
case 21:
lcd.setCursor(0,0); 
lcd.print("  Temperature   ");
lcd.setCursor(0,1);
sprintf(msgbot,"Temp max = %2d",TempMax);
lcd.write(msgbot);
lcd.write((uint8_t) 0);
lcd.print("C  ");
break;
//TEMPERATURE_MIN
case 22:
lcd.setCursor(0,0); 
lcd.print("  Temperature   ");
lcd.setCursor(0,1);
sprintf(msgbot,"Temp min = %2d",TempMin);
lcd.write(msgbot);
lcd.write((uint8_t) 0);
lcd.print("C  ");
break;

//HYDROMETRIE--------------------------------------------------------------
case 30:
lcd.setCursor(0,0);
lcd.print("  Hydrometrie   ");
lcd.setCursor(0,1);
if(HydroValue <= 30){lcd.write("                ");}
else{if(HydroValue <= 40){lcd.write("       ");lcd.write((uint8_t) 2);lcd.write("        ");}
else{if(HydroValue <= 50){lcd.write("      ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write("       ");}
else{if(HydroValue <= 60){lcd.write("     ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write("      ");}
else{if(HydroValue <= 70){lcd.write("    ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write("     ");}
else{if(HydroValue <= 100){lcd.write("   ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write(" ");lcd.write((uint8_t) 2);lcd.write("    ");}}}}}}
break;
//HYDROMETRIE_MAX
case 31:
lcd.setCursor(0,0); 
lcd.print("  Hydrometrie   ");
lcd.setCursor(0,1);
sprintf(msgbot,"Hydro max = %3d",HydroMax);
lcd.write(msgbot);
lcd.write((uint8_t) 1);
break;
//HYDROMETRIE_MIN
case 32:
lcd.setCursor(0,0); 
lcd.print("  Hydrometrie   ");
lcd.setCursor(0,1);
sprintf(msgbot,"Hydro min = %3d",HydroMin);
lcd.write(msgbot);
lcd.write((uint8_t) 1);
break;

//LUMINOSITE--------------------------------------------------------------
case 40:
lcd.setCursor(0,0); 
lcd.print("  Luminosite    ");
lcd.setCursor(0,1);
lcd.write(msgsun);
break;
//LUMINOSITE_MAX
case 41:
lcd.setCursor(0,0); 
lcd.print("    Lumi Max    ");
lcd.setCursor(0,1);
if(LumiMax == 1){sprintf(msgsun,"       *        ");}
else{if(LumiMax == 2){sprintf(msgsun,"      * *       ");}
else{if(LumiMax == 3){sprintf(msgsun,"     * * *      ");}
else{if(LumiMax == 4){sprintf(msgsun,"    * * * *     ");}
else{if(LumiMax == 5){sprintf(msgsun,"   * * * * *    ");}}}}}
lcd.write(msgsun);
break;
//LUMINOSITE_MIN
case 42:
lcd.setCursor(0,0); 
lcd.print("    Lumi Min    ");
lcd.setCursor(0,1);
if(LumiMin == 1){sprintf(msgsun,"       *        ");}
else{if(LumiMin == 2){sprintf(msgsun,"      * *       ");}
else{if(LumiMin == 3){sprintf(msgsun,"     * * *      ");}
else{if(LumiMin == 4){sprintf(msgsun,"    * * * *     ");}
else{if(LumiMin == 5){sprintf(msgsun,"   * * * * *    ");}}}}}
lcd.write(msgsun);
break;

//HORLOGE--------------------------------------------------------------
case 50:
lcd.setCursor(0,0);
if(heure<10){sprintf(msgheure,"    0%d:",heure);}
else{sprintf(msgheure,"    %2d:",heure);}
lcd.write(msgheure);
if(minute<10){sprintf(msgminute,"0%d:",minute);}
else{sprintf(msgminute,"%2d:",minute);}
lcd.write(msgminute);
if(seconde<10){sprintf(msgseconde,"0%d    ",seconde);}
else{sprintf(msgseconde,"%2d    ",seconde);}
lcd.write(msgseconde);
lcd.setCursor(0,1);
if(jour<10){sprintf(msgjour,"   0%d/",jour);}
else{sprintf(msgjour,"   %2d/",jour);}
lcd.write(msgjour);
if(mois<10){sprintf(msgmois,"0%d/",mois);}
else{sprintf(msgmois,"%2d/",mois);}
lcd.write(msgmois);
lcd.print(annee);
lcd.print("   ");
break;

//HUEURE_SETUP
case 51:
lcd.setCursor(0,0);
lcd.print("  Setup Heure   ");
lcd.setCursor(0,1);
if(heure<10){sprintf(msgheure,"    0%d:",heure);}
else{sprintf(msgheure,"    %d:",heure);}
lcd.write(msgheure);
if(minute<10){sprintf(msgminute,"0%d:",minute);}
else{sprintf(msgminute,"%d:",minute);}
lcd.write(msgminute);
if(seconde<10){sprintf(msgseconde,"0%d    ",seconde);}
else{sprintf(msgseconde,"%d    ",seconde);}
lcd.write(msgseconde);
break;

case 52:
lcd.setCursor(0,0);
lcd.print("  Setup Minute  ");
lcd.setCursor(0,1);
if(heure<10){sprintf(msgheure,"    0%d:",heure);}
else{sprintf(msgheure,"    %2d:",heure);}
lcd.write(msgheure);
if(minute<10){sprintf(msgminute,"0%d:",minute);}
else{sprintf(msgminute,"%2d:",minute);}
lcd.write(msgminute);
if(seconde<10){sprintf(msgseconde,"0%d    ",seconde);}
else{sprintf(msgseconde,"%2d    ",seconde);}
lcd.write(msgseconde);
break;

//DATE_SETUP
case 53:
lcd.setCursor(0,0);
lcd.print("  Setup Jour    ");
lcd.setCursor(0,1); 
if(jour<10){sprintf(msgjour,"   0%d/",jour);}
else{sprintf(msgjour,"   %2d/",jour);}
lcd.write(msgjour);
if(mois<10){sprintf(msgmois,"0%d/",mois);}
else{sprintf(msgmois,"%2d/",mois);}
lcd.write(msgmois);
lcd.print(annee);
lcd.print("   ");
break;

case 54:///////////////////////////////////////////////////////
lcd.setCursor(0,0);
lcd.print("  Setup Mois    ");
lcd.setCursor(0,1); 
if(jour<10){sprintf(msgjour,"   0%d/",jour);}
else{sprintf(msgjour,"   %2d/",jour);}
lcd.write(msgjour);
if(mois<10){sprintf(msgmois,"0%d/",mois);}
else{sprintf(msgmois,"%2d/",mois);}
lcd.write(msgmois);
lcd.print(annee);
lcd.print("   ");
break;

case 55:
lcd.setCursor(0,0);
lcd.print("  Setup Annee   ");
lcd.setCursor(0,1); 
if(jour<10){sprintf(msgjour,"   0%d/",jour);}
else{sprintf(msgjour,"   %2d/",jour);}
lcd.write(msgjour);
if(mois<10){sprintf(msgmois,"0%d/",mois);}
else{sprintf(msgmois,"%2d/",mois);}
lcd.write(msgmois);
lcd.print(annee);
lcd.print("   ");
break;
}}

/*COMMENTAIRE ET SAUVEGARDE

int pin = 4;  
int freq = 0;  

void setup()  
{  
}  
  
void loop()  
{  
  tone(pin, freq, 50);  
  delay(250);  
  freq = random(20,400);  
} 

*/

  

