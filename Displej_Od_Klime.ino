//to understand this code, first you must understand how shift registers work. There are great tutorials on youtube
//but i reccomend this one : https://www.youtube.com/watch?v=NykONuPWycc&t=77s

int serialData = 6;
int shiftClock = 7;
int latchClock = 8;

void setup() {
pinMode(shiftClock, OUTPUT);
pinMode(latchClock, OUTPUT);
pinMode(serialData, OUTPUT);
}

void loop() {
  int shiftCount1 = 255;
  int shiftCount2 = 255;
  int shiftCount3 = 255;
  for(int i = 0; i<100; i++)
  {
    digit(i, &shiftCount1, &shiftCount2); // controls 7 segment display 
    shiftCount2 = shiftCount2 - 64; // comment this line, if you dont want to use celsius symbol
    bar(i/20, &shiftCount3); // controls lower led bar, and some other leds, but i coded if only for bar
    digitalWrite(latchClock, LOW);
    shiftOut(serialData, shiftClock, MSBFIRST, shiftCount1);
    shiftOut(serialData, shiftClock, MSBFIRST, shiftCount2);
    shiftOut(serialData, shiftClock, MSBFIRST, shiftCount3);
    // 3 of this function calls are needed because we have 3 shift registers.
    digitalWrite(latchClock, HIGH);
    delay(200);
    }
}

void bar(int lvl, int* shiftCount3)
{
  if(lvl > 4 || lvl < 1)
  {
    *shiftCount3 = 255;
    }
  switch (lvl)
  {
    case 1:
    *shiftCount3 = 247;
    break;
    
    case 2:
    *shiftCount3 = 243;
    break;

    case 3:
    *shiftCount3 = 241;
    break;

    case 4:
    *shiftCount3 = 240;
    break;
    }
  }

void digit(int p, int* shiftCount1, int* shiftCount2)
{
  // insert int i, -1<i<100, and it will set the value of shiftCount1 and ShiftCount2. shiftCount1 represents
  // tentsts number and shiftCount2 represents ones number. That int number, is actually useful only in binary,
  // because every digit in binary is responsible for one led in 7 segment display. For example 01101011 will light
  // 3 led diodes, in some positin (0 activates the leds).
  if (p % 99 > 0)
  {
    // letter E for error, never coded it
    }
    int tens = p/10;
    int ones = p - 10*tens;

    switch(ones)
    {
      case 0:
      *shiftCount2 = 66;
      break;

      case 1:
      *shiftCount2 = 250;
      break;

      case 2:
      *shiftCount2 = 84;
      break;

      case 3:
      *shiftCount2 = 112;
      break;

      case 4:
      *shiftCount2 = 232;
      break;

      case 5:
      *shiftCount2 = 97;
      break;

      case 6:
      *shiftCount2 = 65;
      break;

      case 7:
      *shiftCount2 = 242;
      break;

      case 8:
      *shiftCount2 = 64;
      break;

      case 9:
      *shiftCount2 = 96;
      break;
      }

      switch(tens)
    {
      case 0:
      *shiftCount1 = 255;
      break;

      case 1:
      *shiftCount1 = 95;
      break;

      case 2:
      *shiftCount1 = 37;
      break;

      case 3:
      *shiftCount1 = 13;
      break;

      case 4:
      *shiftCount1 = 27;
      break;

      case 5:
      *shiftCount1 = 137;
      break;

      case 6:
      *shiftCount1 = 128;
      break;

      case 7:
      *shiftCount1 = 93;
      break;

      case 8:
      *shiftCount1 = 0;
      break;

      case 9:
      *shiftCount1 = 8;
      break;
      }
  }

  // If you notice that some leds in 7 segment display are brighter than others, thats brobably because of the extended
  // use of that display in the past. For example in my case, this display was used in AC, and in my house, temperature
  // was always set to 20-24 degrees, so first numbeer in 7 segment display was always 2. Thats why two leds that were not
  // used in number 2 glow brighter now.
