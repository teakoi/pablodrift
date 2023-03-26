//200 Proj 3 code:

//Passive Buzzer:
/*
  Melody
 */

//See you again chorus
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587


// notes in the melody:
int intro[] = {
  NOTE_F4, NOTE_C5, NOTE_AS4, NOTE_F4, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5
};

int melody[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4,0, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4,0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int introDurations[] = {
  4,4,4,2,8,8,8,8,8,8
};
int noteDurations[] = {
  4,4,4,1,2,4,4,4,4,4,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,4
};

int i = 3;
int n = 1;
int m = 3;

void setup() {
    while (i > 0) {
    	for (int thisNote = 0; thisNote < 10; thisNote++) {
      		int introDuration = 1000 / introDurations[thisNote];
      		tone(8, intro[thisNote], introDuration);
      
      		int pauseBtwnNotes = introDuration * 1.40;
      		delay(pauseBtwnNotes);
      
      		noTone(10);
    		}
    	i--;
    	}
  
  	while (n >0){
   		for (int thisNote=0; thisNote < 4; thisNote++) {
    
    		int introDuration = 1000 / introDurations[thisNote];
    		tone(8, intro[thisNote], introDuration);
    
    		int pauseBtwnNotes = introDuration * 1.40;
    		delay(pauseBtwnNotes);
    
    		noTone(4);
  			}
    	n--;
    	}
    
    
  // iterate over the notes of the melody:
  while (m > 0) {
  	for (int thisNote = 0; thisNote < 26; thisNote++) {

    	// to calculate the note duration, take one second
    	// divided by the note type.
    	//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    	int noteDuration = 1000 / noteDurations[thisNote];
    	tone(8, melody[thisNote], noteDuration);

    	// to distinguish the notes, set a minimum time between them.
    	// the note's duration + 40%:
    	int pauseBetweenNotes = noteDuration * 1.40;
    	delay(pauseBetweenNotes);
    	// stop the tone playing:
    	noTone(26);
  		}
    m--;
 	}
}

void loop() {
}