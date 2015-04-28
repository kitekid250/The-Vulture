 /*
 P. R. Diefenderfer
 ADC ISR example program
 */

void setup(){
  pinMode(8, OUTPUT);   // Green LED
  pinMode(9, OUTPUT);   // Yellow LED
  pinMode(10, OUTPUT);  // Red LED
  pinMode(11, OUTPUT);  // o-scope
  pinMode(12, OUTPUT);  // o-scope
  pinMode(13, OUTPUT);  //On board LED

  pinMode(A0, INPUT); // Green Pot
  pinMode(A1, INPUT); // Yellow Pot
  pinMode(A2, INPUT); // Red Pot

  //  ADMUX |= (1 << 6); // AREF = AVCC
  //  ADMUX |= (1 << 5); // Left adjust ADC output, 
  //toss ADCL, 8 bit precision
  ADMUX |= 0x60;

  ADMUX &= 0xf0; // clear MUX channel
  // ADMUX |= 0;   // set MUX channel, 0 for now

  //  ADCSRA |= 0x7;       // ADC prescaler = 128
  //  ADCSRA |= (1 << 7);  // Enable ADC
  //  ADCSRA |= (1 << 6);  // Start ADC
  //  ADCSRA |= (1 << 5);  // Free Run Mode
  //  ADCSRA |= (1 << 3);  // Enable Interrupts
  ADCSRA |= 0xCF;

  sei();  // enable global interrupts
}

void loop(){
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

ISR(ADC_vect) {
  digitalWrite(12 , HIGH);
  byte channel = ADMUX & 0x0f;
  if (channel == 0){ 
    // green = ADCH;
    if(ADCH < 128) {
      digitalWrite(8, HIGH);
    } 
    else {
      digitalWrite(8, LOW);
    }
    ADMUX &= 0xf0; // clear MUX channel
    ADMUX |= 0x01;   // set MUX channel
  } 
  else if (channel == 1){  
    // digitalWrite(11,HIGH);
    // yellow = ADCH;
    if(ADCH < 128) {
      digitalWrite(9, HIGH);
    } 
    else {
      digitalWrite(9, LOW);
    }
    ADMUX &= 0xf0; // clear MUX channel
    ADMUX |= 0x02;   // set MUX channel
    // digitalWrite(11,LOW);
  }
  else if (channel == 2){
    if(ADCH < 128) {
      digitalWrite(10, HIGH);
    } 
    else {
      digitalWrite(10, LOW);
    }
    ADMUX &= 0xf0; // clear MUX channel
  }
  ADCSRA |= (1<<6);
  digitalWrite(12, LOW);
};


