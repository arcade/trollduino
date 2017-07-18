/*
Arno Prank - Mouse Edition 1
K. Warner
Olympia Circuits
3/2013
olympiacircuits.com
*/
#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>
#include <./main.h>

#define KEY_BACKSPACE 0x08
#define KEY_LEFT_ARROW 0x25
#define KEY_RIGHT_ARROW 0x27
#define KEY_TAB 0x09
#define KEY_CAPS 0x14
#define KEY_WIN 0x5D
#define KEY_HOME 0x24

// Keys to press
int keys[7] = {KEY_WIN, KEY_TAB, KEY_CAPS, KEY_HOME, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_BACKSPACE};


void setup() {
  Serial.begin(19200);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  randomSeed(analogRead(0));

  int action = rand();
  int key = keys[rand() % 7];

  if (action % 3 == 0) {
    Serial.println("Jitter mouse for 50 ms");
    jitter (50);
  }

  if (action % 4 == 0) {
    Serial.println("Jump mouse across screen");
    jump (-100);
  }

  if (action % 5 == 0) {
    char output[17];
    sprintf(output, "Press %i 10 times", key);
    Serial.println(output);
    pressKey(key);
  }
  Serial.println("Sleeping for 20 seconds");
  delay (20000);
}




//===============subs=============

void jump(int howFar){

  Mouse.move (howFar/2, howFar); // modify with math for different results
  delay(50);
  Mouse.move (howFar, howFar/2); // modify with math for different results
  delay(50);
  Mouse.move (-howFar/4, howFar); // modify with math for different results
  delay(50);
  Mouse.move (howFar, -howFar/4); // modify with math for different results
  delay (2);
}

void jitter (int duration){
  int i = 0;
  while (i < duration){
    Mouse.move(15,15);
    delay (15);
    Mouse.move(-16, 0);
    delay (20);
    Mouse.move(15,-15);
    delay(25);
    Mouse.move (-16,0);
    delay (20);
    i++;
  }
}

void pressKey (int key) {
  for (int i = 0; i < 10; i++) {
    Keyboard.press(key);
    Keyboard.releaseAll();
    delay(100);
  }
}
