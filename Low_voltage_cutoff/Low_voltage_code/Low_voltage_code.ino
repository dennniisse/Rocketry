#include <avr/sleep.h>
/*
 * Notes: MOSFET OFF: current will flow
 * MOSFET ON: current will not flow
 * Pin A3: read voltage input
 * Pin 6: connected to MOSFET, toggle it on and off to control current flow
 * Battery pack rated approx 9.2V  
 * 7.4V nominal voltage, not 3.2V, its not per cell but battery as a whole
*/
#define VINPIN A3
#define MOSFET 6
#define LED 13

/////////////////////////////////////////////////////////////////
const double systemVoltage = 7.6; 
double limit = 7.2;
/////////////////////////////////////////////////////////////////

double val = 0;
double voltageIn = 0;
bool flag = false;

void setup() {
  pinMode(MOSFET,OUTPUT); 
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(VINPIN);
  voltageIn = (val * systemVoltage) / 1023; //
  delay(50);
  
  if(voltageIn <= limit){
    flag = true;
    delay(50);
  }
  
  mosfet_control(flag); 
  delay(100);
  Serial.println(voltageIn);
  delay(100);

  if(flag == true){
    Sleep();
  }
}

void mosfet_control(bool flag){
    if(flag == true){
      digitalWrite(MOSFET, HIGH); 
      delay(50);
    }
    else if (flag == false){
      digitalWrite(MOSFET, LOW);
      delay(50);
    }
}

void Sleep(){
  digitalWrite(LED,LOW);  //indicates sleep mode has been entered
  delay(1000);
  sleep_enable();  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  //sets the sleep mode, which is full sleep
  sleep_cpu();  //activates sleep mode
}
