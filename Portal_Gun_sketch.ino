#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

int LED_PIN = 12;
int ENCODER_LEFT = 17;
int ENCODER_RIGHT = 16;
int ENCODER_PUSH = 15;

int primes[168] = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
  211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331,
  337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457,
  461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
  601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
  739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877,
  881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};
 uint8_t letters[25] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
 };
 uint8_t digits[10] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
 };

int letter_index = 10;
int prime_index = 32;
bool is_on = true;

void update_screen(){
  alpha4.writeDigitAscii(0, letters[letter_index % 25]);
  alpha4.writeDigitAscii(1, digits[primes[prime_index % 168] / 100]);
  alpha4.writeDigitAscii(2, digits[primes[prime_index % 168] / 10 % 10]);
  alpha4.writeDigitAscii(3, digits[primes[prime_index % 168] % 10]);
  alpha4.writeDisplay();
}

void setup() {
  // put your setup code here, to run once:
  alpha4.begin(0x70);  // pass in the address

  pinMode(LED_PIN, OUTPUT);
  pinMode(ENCODER_LEFT, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT, INPUT_PULLUP);
  pinMode(ENCODER_PUSH, INPUT_PULLUP);

  update_screen();
}

void change_screen_value(int v){
  prime_index += v;
  if(prime_index >= 168){
    prime_index = 0;
    letter_index += 1;
  }
  if(prime_index < 0){
    prime_index = 167;
    letter_index -= 1;
  }
  if(letter_index < 0){
    letter_index = 24;
  }
  update_screen();
}



void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(ENCODER_RIGHT) == 0){
    delay(0.2);
    while(digitalRead(ENCODER_RIGHT) == 0){
      
    }
    if(is_on){
      change_screen_value(1);
    }
  }
  if(digitalRead(ENCODER_LEFT) == 0){
    delay(0.2);
    while(digitalRead(ENCODER_LEFT) == 0){
      
    }
    if(is_on){
      change_screen_value(-1);
    }
  }
  if(digitalRead(ENCODER_PUSH) == 0){
    if(is_on){
      while(digitalRead(ENCODER_PUSH) == 0){
        digitalWrite(LED_PIN, HIGH);
      }
      digitalWrite(LED_PIN, LOW);
      is_on = false;
      alpha4.clear();
      alpha4.writeDisplay();
    }
    else{
      while(digitalRead(ENCODER_PUSH) == 0){
        
      }
      is_on = true;
      update_screen();
    }
  }
}
