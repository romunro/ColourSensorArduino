#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define distanceSens 9


int frequencyRED = 0;
int frequencyBLUE = 0;
int frequencyGREEN = 0;
int RGB[] = {0, 0, 0};
bool debugMode1 = false;
bool debugMode2 = false;
int delayTime =10;
int samples = 50;

//Set sensor range values
int RLow = 25;
int GLow = 25;
int BLow = 25;
int RHigh = 150;
int GHigh = 150;
int BHigh = 150;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(distanceSens, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  if (debugMode2 == true){
    Serial.println("Debug mode is on");
    }
    else {
      Serial.println("Debug mode is off");
      }
}

void loop() {
  Serial.println("  ");
  Serial.println("  ");
  bool state = digitalRead(distanceSens);
  if (state == 0){
    
    //Sensing colours
    int frequencyREDsum = 0;
    int frequencyBLUEsum = 0;
    int frequencyGREENsum = 0;
    int count = samples;
    while (count > 0){
      GetColors();
      frequencyREDsum = frequencyREDsum + frequencyRED;
      frequencyBLUEsum = frequencyBLUEsum + frequencyBLUE;
      frequencyGREENsum = frequencyGREENsum + frequencyGREEN;
//      Debug print colours
      if (debugMode2 == true){
        Serial.print("R= ");//printing name
        Serial.print(frequencyRED);//printing RED color frequency
        Serial.print("  ");
        Serial.print("G= ");//printing name
        Serial.print(frequencyBLUE);//printing RED color frequency
        Serial.print("  ");
        Serial.print("B= ");//printing name
        Serial.print(frequencyGREEN);//printing RED color frequency
        Serial.println("  ");
      }
      
      count = count -1;
      digitalWrite(S2,HIGH);
      digitalWrite(S3,LOW);
      }
    
    RGB[0] = frequencyREDsum / samples;
    RGB[1] = frequencyBLUEsum / samples;
    RGB[2] = frequencyGREENsum / samples;
    delay(1000);
    Serial.println("Measurement averages:  ");
    Serial.print("R= ");//printing name
    Serial.print(RGB[0]);//printing RED color frequency
    Serial.print("G= ");//printing name
    Serial.print(RGB[1]);//printing RED color frequency
    Serial.print("B= ");//printing name
    Serial.println(RGB[2]);//printing RED color frequency
    
    ////Detecting Colours
    //Red
    if (((RGB[0]>= 192 && RGB[0]<=256) && (RGB[1]>= 0 && RGB[1]<=128) && (RGB[2]>=0 && RGB[2]<=128)) || (RGB[0]>= RGB[1]+RGB[2]+10)){
      Serial.println("  Colour is red");
      Serial.println("  ");
      tone(12,300,50);
      delay(50);
      tone(12,300,50);
      return;
    }
    //Green
    if (((RGB[0]>= 0 && RGB[0]<=128) && (RGB[1]>= 96 && RGB[1]<=256) && (RGB[2]>=0 && RGB[2]<=128)) || (RGB[1]>= RGB[0]+RGB[2]+10)){
      Serial.println("  Colour is green");
      Serial.println("  ");
      tone(12,1200,50);
      delay(50);
      tone(12,1200,50);
      return;
    }
    //Blue
    if (((RGB[0]>= 0 && RGB[0]<=128) && (RGB[1]>= 0 && RGB[1]<=128) && (RGB[2]>=192 && RGB[2]<=256)) || (RGB[2]>= RGB[0]+RGB[1]+10)){
      Serial.println("  Colour is blue");
      Serial.println("  ");
      tone(12,800,50);
      delay(50);
      tone(12,800,50);
      return;
    }
    //Yellow
    if ((RGB[0]>= 192 && RGB[0]<=256) && (RGB[1]>= 128 && RGB[1]<=256) && (RGB[2]>=0 && RGB[2]<=192)){
      Serial.println("  Colour is yellow");
      Serial.println("  ");
      tone(12,200,50);
      delay(50);
      tone(12,500,50);
      return;
    }
    //Black
    if ((RGB[0]>= 0 && RGB[0]<=128) && (RGB[1]>=0 && RGB[1]<=128) && (RGB[2]>=0 && RGB[2]<=128)){
      Serial.println("  Colour is black");
      Serial.println("  ");
      tone(12,300,200);
      return;
    }
    //White
    if ((RGB[0]>=192 && RGB[0]<=256) && (RGB[1]>=192 && RGB[1]<=256) && (RGB[2]>=192 && RGB[2]<=256)){
      Serial.println("  Colour is white");
      Serial.println("  ");
      tone(12,700,50);
      return;
    }
    else{
      Serial.println("  Colour is unkown!");
      Serial.println("  ");
      tone(12,100,100);
      delay(100);
      tone(12,100,100);
    }
  }
  else{
    Serial.println("object far");
//    digitalWrite(S0,LOW);
//    digitalWrite(S1,LOW);
    digitalWrite(S2,HIGH);
    digitalWrite(S3,LOW);
    tone(12,500,100);
    delay(1000);   
  }
}
int GetColors(){
    // Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    frequencyRED = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    if (frequencyRED >= RHigh) {
      frequencyRED = RHigh;
      }
    if (frequencyRED <= RLow) {
      frequencyRED = RLow;
    }
    frequencyRED = map(frequencyRED,RHigh,RLow,0,255);
  
//    RGB[0] = {frequencyRED};
    // Printing the value on the serial monitor
    if (debugMode1 == true){
    Serial.print("R= ");//printing name
    Serial.print(RGB[0]);//printing RED color frequency
    Serial.print("  ");
    delay(delayTime);
    }
    
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequencyGREEN = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    if (frequencyGREEN >= GHigh) {
      frequencyGREEN = GHigh;
      }
    if (frequencyGREEN <= GLow) {
      frequencyGREEN = GLow;
    }
    frequencyGREEN = map(frequencyGREEN, GHigh,GLow,0,255);
  
//    RGB[1] = {frequencyGREEN};
    // Printing the value on the serial monitor
    if (debugMode1 == true){
    Serial.print("G= ");//printing name
    Serial.print(RGB[1]);//printing RED color frequency
    Serial.print("  ");
    delay(delayTime);
    }
    
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequencyBLUE = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    if (frequencyBLUE >= BHigh) {
      frequencyBLUE = BHigh;
      }
    if (frequencyBLUE <= BLow) {
      frequencyBLUE = BLow;
    }
    frequencyBLUE = map(frequencyBLUE, BHigh,BLow,0,255);
  
//    RGB[2] = {frequencyBLUE};
    // Printing the value on the serial monitor
    if (debugMode1 == true){
    Serial.print("B= ");//printing name
    Serial.print(RGB[2]);//printing RED color frequency
    Serial.println("  ");
    delay(delayTime);
    }
  }
