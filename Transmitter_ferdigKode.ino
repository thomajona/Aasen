#include <VirtualWire.h>


//melding som sendes
char message;

//Fysiske utfordringer knapp
int buttonpinF = 9;
int buttonstateF = 0;


//mentale utfordringer knapp
int buttonpinM = 10;
int buttonstateM = 0;

//Lister med øvelser
char *myStringsF[] = {" Ring en venn", " Lese en ny bok", " Hor ny musikk", " Hor ny podcast", " Mindfulness"};
char *myStringsM[] = {" Gaa tur", " Se i fotoalbum", " Ring en venn", " 10 Repetisjoner", " Godt maaltid"};

//Høyttaler
const int buzzer = 3;

//Av og PÅ knapp
const int buttonpinO = 8;

//LED
const int ledpin = 13;
int ledstate = LOW;
int ledflag = 0;

unsigned long previousMillis = 0;
const long interval = 10000;


void setup()
{
  
  pinMode(buttonpinO, INPUT); // Av og PÅ knapp

  // led lys til av og på knapp
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  pinMode(buzzer, OUTPUT); //Hoyttaler

  //Knapper til utfordringer
  pinMode(buttonpinF, INPUT);
  pinMode(buttonpinM, INPUT);

  
  // Initialize the IO and ISR
  Serial.begin(9600);
  vw_setup(2000); // Bits per sec
  Serial.print("Tester setup");
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if(ledstate == LOW){
      ledstate = HIGH;
      tone(buzzer, 1000);
      tone(buzzer, 1200);
      tone(buzzer, 1000);
        if(digitalRead(buttonpinO) == HIGH) {
    if(ledflag ==0){
      ledflag =1;
      digitalWrite(ledpin, HIGH);
    }
    else{
      ledflag = 0;
      digitalWrite(ledpin, LOW);
      noTone(buzzer);
    }
  delay(1000);
  }
    }
    else{
      ledstate = LOW;
      noTone(buzzer);
    }
    digitalWrite(ledpin, ledstate);
  }

  
  buttonstateF = digitalRead(buttonpinF);
  buttonstateM = digitalRead(buttonpinM);



  
  int iF = random(5);
  int iM = random(5);


  
  if(buttonstateF == HIGH){
    noTone(buzzer);
    send(myStringsF[iF]);
    delay(5000);
    Serial.print("Sender fysisk melding"); //debugging
}
  else if(buttonstateM == HIGH){
    noTone(buzzer);
    send(myStringsM[iM]);
    delay(10000);
    Serial.print("Sender mental melding"); //debugging
  }
else{
  send(" Trykk for ovelse");
  delay(1000);
  Serial.print("Ingen melding"); //debugging
}
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
