/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 */


/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */


void setup() {
  //Initializes the module.
  
}

void loop() {
  //Plays synchronously an audio file. Busy pin is used for this method.
//  wtv020sd16p.playVoice(1);
  //Plays asynchronously an audio file.
wtv020sd16p.asyncPlayVoice(0);
delay(20000);
//  //Plays audio file number 1 during 2 seconds.
//  delay(5000);
//  //Pauses audio file number 1 during 2 seconds.  
//  wtv020sd16p.pauseVoice();
//  delay(5000);
//  //Resumes audio file number 1 during 2 seconds.
//  wtv020sd16p.pauseVoice();
//  delay(5000);  
//  //Stops current audio file playing.
//  wtv020sd16p.stopVoice();
//  //Plays synchronously an audio file. Busy pin is used for this method.  
//  wtv020sd16p.asyncPlayVoice(2);
//  delay(2000);   
//  //Mutes audio file number 2 during 2 seconds.
//  wtv020sd16p.mute();
//  delay(2000);
//  //Unmutes audio file number 2 during 2 seconds.
//  wtv020sd16p.unmute();
//  delay(2000);    
//  //Stops current audio file playing.
//  wtv020sd16p.stopVoice();
}


