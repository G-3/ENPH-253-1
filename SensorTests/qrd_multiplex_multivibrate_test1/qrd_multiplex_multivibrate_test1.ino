#include <phys253.h>          
#include <LiquidCrystal.h>    

int outA = 8;
int outB = 9;
int outC = 10;
int multivibrator = 11;
int readSensor = 0;
double val1 = 0;
double val2 = 0;

void doStuff();

void setup() {
  // put your setup code here, to run once:
  #include <phys253setup.txt>
  Serial.begin(9600) ;
  pinMode(outA, OUTPUT);
  pinMode(multivibrator, OUTPUT);
  pinMode(outB, OUTPUT);
  pinMode(outC, OUTPUT);

  digitalWrite(outB, LOW);
  digitalWrite(outC, LOW);
  digitalWrite(multivibrator, HIGH);
}

int count = 0;
void loop() {
  while(true){
    digitalWrite(multivibrator, LOW);
    digitalWrite(outA, HIGH);
    digitalWrite(multivibrator, HIGH);
    doStuff();
    val1 = analogRead(readSensor);
  
    delay(5);
  
    digitalWrite(multivibrator, LOW);
    digitalWrite(outA, LOW);
    digitalWrite(multivibrator, HIGH);
    doStuff();
    val2 = analogRead(readSensor);
  
    delay(5);
    
    if(count % 100 == 0){
      Serial.println();
      Serial.println("~~~~~~~~~~~");
      Serial.println();
    
      Serial.println("A is High:");
      Serial.println(val1);
      
      Serial.println("A is Low:");
      Serial.println(val1);
      count = 0;
    }
    count +=1;
  }
}

void doStuff(){
  delayMicroseconds(2);
}
