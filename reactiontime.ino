int pushb1 = 3;
int pushb2 = 2;

int blue = 13;
int yellow = 8;
int green1 = 10;
int red1 = 9;
int green2 = 6;
int red2 = 7;
int draw = 4;

//button detecting sliding window to account for debounce.
int buttondetect(int pin){
  int avg = 0;
  bool static last10[10] = {0,0,0,0,0,0,0,0,0,0};
  unsigned long timenow=millis();
  while (millis()-timenow<10UL){
    for (int i =0; i<9; i++){
      last10[i] = last10[i+1];
    }
    last10[9] = digitalRead(pin);
    delay(1);
    
    for(int i=0;i<10;i++){
      avg =avg+last10[i];
    }
    avg = avg/10;
  }/*
  if (avg){
    Serial.print(pin);
    Serial.print(" ");
    Serial.println(millis());
  }debugging*/
  return(avg);
}

void setup() {
  pinMode(pushb1,INPUT);
  pinMode(pushb2,INPUT);
  pinMode(blue,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));/* without this, the random fxn generates
   the same sequence everytime (although very long). analogRead of an
    unconnected pin is a fairly random seed.*/
}
//this fxn is for 1 run of the game.
int gamerun(int time){
  bool bt1reg=0;
  bool bt2reg=0;
  unsigned long timenow = millis();
  while (millis()-timenow<time){
    digitalWrite(red1,buttondetect(pushb1));
    digitalWrite(red2,buttondetect(pushb2));
    digitalWrite(blue,0);
  }
  digitalWrite(blue,1);
  while(!bt1reg && !bt2reg){
    //Serial.print("start: ");
    //Serial.println(millis()); sprinkled around are debugging codes.

    if (buttondetect(pushb1) && !buttondetect(pushb2)){
      //millisteller();
      bt1reg=1;
      digitalWrite(green1,1);
      digitalWrite(green2,0);
      digitalWrite(blue,0);
      return 1;
    }
    else if (!buttondetect(pushb1) && buttondetect(pushb2)){
      //millisteller();
      bt2reg=1;
      digitalWrite(green2,1);
      digitalWrite(green1,0);
      digitalWrite(blue,0);
      return 2;
    }
    else if(digitalRead(pushb1) && digitalRead(pushb2)){
      //millisteller();
      bt1reg=1;
      bt2reg=1;
      digitalWrite(green2,1);
      digitalWrite(green1,1);
      digitalWrite(blue,0);
      return 3;
    }
    //Serial.print("end: ");
    //Serial.println(millis());
  }
  digitalWrite(blue,0);
  return 0;
}

void loop() {
  int result = gamerun(random(2000,8000));//run one run of game, with random time from 2 to 8 seconds
  int static score1=0;
  int static score2=0;

  //scoring system
  if (result == 1){
    score1 = score1 + 2;
  }
  else if (result == 2){
    score2 = score2 + 2;
  }
  else if (result == 3){
    score1 = score1 + 1;
    score2 = score2 + 1;
  }

  //score displayed in serial monitor
  Serial.print("Score --> P1: ");
  Serial.print(score1);
  Serial.print(" , ");
  Serial.print("P2: ");
  Serial.println(score2);

  //score display using leds
  if (score1>score2){
    digitalWrite(yellow,1);
    digitalWrite(draw,0);
  }
  else if (score1<score2){
    digitalWrite(yellow,0);
    digitalWrite(draw,0);
  }
  else{
    digitalWrite(draw,1);
    digitalWrite(yellow,0);
  }
}