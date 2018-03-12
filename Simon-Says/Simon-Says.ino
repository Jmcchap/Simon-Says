#include <FastLED.h>
#define NUM_LEDS  12
#define DATA_PIN  D6

  CRGBArray<NUM_LEDS> leds;
  int Quad1 = 2;
  int Quad2 = 5;
  int Quad3 = 8;
  int Quad4 = 11;

  int randomNumber = 0;    //to decide which quad gets lit
  int flashlength = 1500;  //number of seconds for the quadrant to stay lit
  int pauseLength = 4000; //the number of milliseconds to wait between flashes
  int RoundLength = 5;    //number of rounds before you win the game
  int Rounds = 1;          //the Round you are on 

  static uint8_t hue=0;   //for the rainbow fill effect

   

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  

}


void flashQuad1(){
      leds(0,Quad1) = CRGB::Red;
      FastLED.show();
      Serial.print("...lit!");
      delay(flashlength);
      leds(0, Quad1) = CRGB::Black;
      Serial.println("....and off! Zzzz");
}

void flashQuad2(){
     leds(Quad1+1, Quad2)= CRGB::Blue; 
     FastLED.show();
     Serial.print("...lit!");
     delay(flashlength);
     leds(Quad1+1, Quad2)= CRGB::Black; 
     Serial.println("....and off! Zzzz");
}

void flashQuad3(){
     leds(Quad2+1,Quad3) = CRGB::Yellow;
     FastLED.show();
     Serial.print("...lit!");
     delay(flashlength);
     leds(Quad2+1,Quad3) = CRGB::Black;
     Serial.println("....and off! Zzzz");
}

void flashQuad4(){
     leds(Quad3+1, Quad4) = CRGB::Green;
     FastLED.show();
     Serial.print("...lit!");
     delay(flashlength);
     leds(Quad3+1, Quad4) = CRGB::Black;
     delay(3000);
     Serial.println("....and off! Zzzz");
}



void loop() {
  
    //Setup the answerSheet so that it has the right number of slots (Rounds)
     // and sets all the values to 0*/
   int answerSheet[Rounds];

   for(int k =0; k <= Rounds; k++)
   {
    answerSheet[k] = 0;
   }


  if(Rounds < RoundLength)
  {
    for(Rounds=1; Rounds<=RoundLength; Rounds++)
    {
      Serial.print("-------------| ROUND ");  
      Serial.print(Rounds);
      Serial.println(" |-------------");
      
         for(int i=0; i< Rounds; i++)
         {
              
             randomNumber = random(1,5);                //pick a random number (between 1-4)
             Serial.print("randomNumber = ");           
             Serial.print(randomNumber);
            
              
            
             switch (randomNumber)
             {
              case 1:
                    flashQuad1();
                    answerSheet[i] = 1;       
                    break;
            
               case 2:
                    flashQuad2();
                    answerSheet[i] = 2;
                    break;
            
                case 3:
                    flashQuad3();
                    answerSheet[i] = 3;
                    break;
            
                case 4:
                   flashQuad4();
                   answerSheet[i] =4;
                   break;
            
                default:
                  Serial.print("Nothing happened???");
                  break;      
             }
            
                FastLED.show();       //usually to let all the LEDs go dark
                delay(pauseLength);          
        
          
         
  
      }
      Serial.print("The Answer Sheet is... ");
      for( int j=0; j < Rounds; j++)
      {
      Serial.print(answerSheet[j]);
      Serial.print(" , ");
      }
      Serial.println();
    }
  }
  else
  {
     leds(0,NUM_LEDS-1).fill_rainbow(hue++); 
     FastLED.show();
     delay(50);                            //no delay is pretty lit, but maybe too lit?
  }
}


