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
  int inputTime = 5000;     //amount of time the player has to answer Simon

   

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(inputTime);
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

   int answerSheet[Rounds];               //sets up the answer sheet so that it has the right number 
                                          //of slots (Rounds)
//    for(int k =0; k <= Rounds; k++)       //and sets all of the values in answerSheet to 0
//   {
//    answerSheet[k] = 0;
//   }


/* PRINTS ALL THE ANSWERS FROM THE LAST ROUND */
/*--------------------------------------------*/
   memset(answerSheet, 0, sizeof(answerSheet));     
   Serial.print("The Answer Sheet is... ");            
      for( int j=0; j < 5; j++)
      {
      Serial.print(answerSheet[j]);
      Serial.print(" , ");
      }
      Serial.println();
      Serial.println();
   
  


  if(Rounds < RoundLength)                              //beginning of a new round
  {
    for(Rounds=1; Rounds<=RoundLength; Rounds++)
    {
      Serial.print("-------------| ROUND ");  
      Serial.print(Rounds);
      Serial.println(" |-------------");
      
         for(int i=0; i< Rounds; i++)                    //beginning of a new quadrant to be picked
         {
              
             randomNumber = random(1,5);                //pick a random number (between 1-4)
             Serial.print("randomNumber = ");           
             Serial.print(randomNumber);
            
              
                                    
             switch (randomNumber)                        //use the random number to pick a quadrant to flash
             {
              case 1:
                    flashQuad1();                         //light up the quadrant
                    answerSheet[i] = 1;                   //log this quadrant on the answer sheet
                    break;                                //get the hell out of dodge
            
               case 2:
                    flashQuad2();                        //...same thing, just for quad2...
                    answerSheet[i] = 2;
                    break;
            
                case 3:
                    flashQuad3();                       //...and quad3...
                    answerSheet[i] = 3;
                    break;
            
                case 4:
                   flashQuad4();                        //this one is totally different in that it's not
                   answerSheet[i] =4;
                   break;
            
                default:
                  Serial.print("Nothing happened???");  //I think technically 5 is a valid random number. 
                  break;                                //this is a 'just in case' measure
             }
            
                FastLED.show();                         //usually to let all the LEDs go dark
                delay(pauseLength);                     //give it a moment so the player knows there's a new entry
        
          
         
  
      }
      
      /*This is me checking to see what the answer key is.
        It's messy and not in a function because I'm not 
        super comfortable with passing stuff in functions/Return*/
      Serial.print("The Answer Sheet is... ");            
      for( int j=0; j < Rounds; j++)
      {
      Serial.print(answerSheet[j]);
      Serial.print(" , ");
      }
      Serial.println();
      Serial.println();


      /*This is to read the player's response.  
        I really should get on the whole Returns thing.
        This all should be a function*/
        
      Serial.println("What was the pattern?");
      
      while(!Serial.available())
      {
        //hang out and no nothing until the user starts booping stuff
      }
      while(Serial.available())
      {
          int playerAnswer = Serial.read(); 
                         
        //delay(inputTime);                     //gives the user some time to answer the question
        
        Serial.print("playerAnswer = ");
        Serial.println(playerAnswer);
        Serial.println();
        Serial.println();
      } 
    }



    
  }
  else
  {
     leds(0,NUM_LEDS-1).fill_rainbow(hue++); 
     FastLED.show();
     delay(50);                            //no delay is pretty lit, but maybe too lit?
  }
}


