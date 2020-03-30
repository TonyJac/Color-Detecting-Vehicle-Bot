//Demo for Pyserial
char serialdata;
int pin=13;
void setup(){
  Serial.begin(9600);
  pinMode(pin,OUTPUT);
}
 
void loop() {
  while(Serial.available()>0)
  serialdata = Serial.read();
  Serial.print(serialdata);

  if(serialdata == '1'){
    digitalWrite(pin,HIGH);
    }
 
  else if(serialdata=='0'){
    digitalWrite(pin,LOW);
    }
}
