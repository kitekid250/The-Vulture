int data = 0;

void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

}

void loop(){
  if(Serial.available()){
    if(Serial.peek() != 10){
      data = Serial.parseInt();

      if (data > 1000){
        analogWrite(3, (data - 1000));
        digitalWrite(2, HIGH);
      }
      else {
        analogWrite(3, data);
        digitalWrite(2, LOW);
      }
    } 
    else {
      while(Serial.read() != -1); 
    }
  }
}
