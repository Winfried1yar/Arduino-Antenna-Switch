/*
Arduino Nano Steuerprogramm für Antennenumschalter
drei Antennen an einem Kabel
Stromversorgung via Koaxkabel
DL1YAR Januar 2026
Version   2026-01-20
Ant_Switch_Shack.kicad_pro
---Script zur Umschaltung----------------
stty -F /dev/ttyUSB0 9600 -parenb -parodd -cmspar cs8 -hupcl -cstopb cread clocal -crtscts -ignbrk brkint ignpar -parmrk -inpck -istrip -inlcr -igncr -icrnl ixon -ixoff -iuclc -ixany -imaxbel -iutf8 -opost -olcuc -ocrnl -onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0 -isig -icanon iexten -echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke -flusho -extproc
echo -e Ant3 > /dev/Arduino
-------------------------
Komandozeile zum Auslesen----------
stty -a < /dev/Arduino
------------------------

*/
uint16_t baud =9600;
//Pinbelegung
const int  Rl1 = 8; // Relay
const int  Rl2 = 7; // Relais

const int led1 = 14;//2;
const int led2 = 15;//3;
const int led3 = 16;//4;

const int tast1 = 19;//6;
const int tast2 = 18;//7;
const int tast3 = 17;//8;

void LED_aus(){
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
}     
void LED_ein(){
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
}  

void relais_aus(){
  digitalWrite(Rl1,LOW );
  digitalWrite(Rl2,LOW );
  digitalWrite(led3,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led1,LOW);

  delay(100);
}
void antenne1(){
  relais_aus();
  digitalWrite(led1,HIGH);
  do{
  delay(100);
    }while(digitalRead(tast1) == LOW);
}
void antenne2(){
  relais_aus();
  digitalWrite(Rl1,HIGH );
  digitalWrite(led2,HIGH);
   do{
  delay(100);
    }while(digitalRead(tast2) == LOW);
}
void antenne3(){
  relais_aus();
  digitalWrite(Rl2,HIGH );
   digitalWrite(Rl1,HIGH );
  digitalWrite(led3,HIGH);
   do{
  delay(100);
    }while(digitalRead(tast3) == LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Rl1,OUTPUT);
  pinMode(Rl2,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(tast1,INPUT_PULLUP);
  pinMode(tast2,INPUT_PULLUP);
  pinMode(tast3,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  relais_aus();
  antenne1();
  Serial.begin(baud);
  LED_aus();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(tast1) == LOW) {antenne1();}
  if(digitalRead(tast2) == LOW) {antenne2();}
  if(digitalRead(tast3) == LOW) {antenne3();}


 if (Serial.available()) {
    delay(100); // Delay um das Steuerkomando vollständig zu emfangen
     LED_ein();
    digitalWrite(led3,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led1,HIGH);
   String my = Serial.readStringUntil('\n');
  if(my.length() ==4){
    if (my =="Ant1") {
       antenne1(); 
      };
    if (my =="Ant2") {
      antenne2();
      }; 
     if (my =="Ant3") {
          antenne3();
      }; 
      delay(20);
      LED_aus();//serielle Eingabe
 }
  } else{ //falsches Komando
    delay(100);
    //Platzhalter
  }
}

}

