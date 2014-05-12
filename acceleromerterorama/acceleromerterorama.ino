    #include <Wire.h>
    #include <Adafruit_LSM303.h>
    #include <Adafruit_NeoPixel.h>
    #include "musical_notes.h"
    
    int speakerPin = 9; // speaker connected to digital pin 9 
    // Parameter 1 = number of pixels in strip
    // Parameter 2 = pin number (most are valid)
    // Parameter 3 = pixel type flags, add together as needed:
    //   NEO_RGB     Pixels are wired for RGB bitstream
    //   NEO_GRB     Pixels are wired for GRB bitstream
    //   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
    //   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);
    Adafruit_LSM303 lsm;
   

    // mess with this number to adjust TWINklitude :)
    // lower number = more sensitive
    #define MOVE_THRESHOLD 800
    
    void setup() 
    {
      Serial.begin(9600);
      
       // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
    strip.begin();
   // strip.show(); // Initialize all pixels to 'off'
      
      pinMode(speakerPin, OUTPUT); // sets the speakerPin to be an output 
    }
    
    void loop() 
    {
    
    
      armUp();
      armForward();
      armSide();
//      theaterChase(strip.Color(127, 127, 127), 50); // White
    // colorWipe(strip.Color(127, 127, 127), 200);
    }
    
    void armUp(){
      
          // Take a reading of accellerometer data
      lsm.read();
      Serial.print("Accel X: "); Serial.print(lsm.accelData.x); Serial.print(" ");
      //Serial.print("Y: "); Serial.print(lsm.accelData.y);       Serial.print(" ");
      Serial.print("Z: "); Serial.print(lsm.accelData.z);     Serial.print(" ");
  
      double storedVector = lsm.accelData.x*lsm.accelData.x;
    //storedVector += lsm.accelData.y*lsm.accelData.y;
    storedVector += lsm.accelData.z*lsm.accelData.z;
    storedVector = sqrt(storedVector);
    Serial.print("Len X Z: "); Serial.println(storedVector);
      
      // wait a bit
      delay(100);
      
      // get new data!
      lsm.read();
    double newVector = lsm.accelData.x*lsm.accelData.x;
    //newVector += lsm.accelData.y*lsm.accelData.y;
    newVector += lsm.accelData.z*lsm.accelData.z;
    newVector = sqrt(newVector);
      Serial.print("New Other Len X Z: "); Serial.println(newVector);
      
        if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
        Serial.println("Twinkle!Twinkle!Twinkle!Twinkle!Twinkle!");
       
     catcall(); 
      colorWipe(strip.Color(255, 255, 0), 1000); // Yellow
        } else if (abs(newVector - storedVector) > MOVE_THRESHOLD){
      strip.Color(127, 127, 127);
    }
    }  

    void armForward(){
           // Take a reading of accellerometer data
      lsm.read();
    Serial.print("Accel X: "); Serial.print(lsm.accelData.x); Serial.print(" ");
   Serial.print("Y: "); Serial.print(lsm.accelData.y);       Serial.print(" ");
     // Serial.print("Z: "); Serial.print(lsm.accelData.z);     Serial.print(" ");
    
      // Get the magnitude (length) of the 3 axis vector
      // http://en.wikipedia.org/wiki/Euclidean_vector#Length
    double storedVector = lsm.accelData.x*lsm.accelData.x;
    storedVector += lsm.accelData.y*lsm.accelData.y;
    //newVector += lsm.accelData.z*lsm.accelData.z;
    storedVector = sqrt(storedVector);
      Serial.print("Len X Z: "); Serial.println(storedVector);
      
      // wait a bit
      delay(100);
      
      // get new data!
      lsm.read();
    double newVector = lsm.accelData.x*lsm.accelData.x;
     newVector += lsm.accelData.y*lsm.accelData.y;
    //newVector += lsm.accelData.z*lsm.accelData.z;
    newVector = sqrt(newVector);
      Serial.print("New Len X Z: "); Serial.println(newVector);
      
        if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
        Serial.println("Swing!Swing!Swing!Swing!");
  
       ohhh();
        colorWipe(strip.Color(0, 0, 255), 200); // Blue
     } else if (abs(newVector - storedVector) > MOVE_THRESHOLD){
      strip.Color(127, 127, 127);
    }
      
    }
  
  void armSide(){
      
          // Take a reading of accellerometer data
      lsm.read();
      //Serial.print("Accel X: "); Serial.print(lsm.accelData.x); Serial.print(" ");
      Serial.print("Y: "); Serial.print(lsm.accelData.y);       Serial.print(" ");
      Serial.print("Z: "); Serial.print(lsm.accelData.z);     Serial.print(" ");
  
      double storedVector = lsm.accelData.y*lsm.accelData.y;
    storedVector += lsm.accelData.z*lsm.accelData.z;
    storedVector = sqrt(storedVector);
    Serial.print("Len Y Z: "); Serial.println(storedVector);
      
      // wait a bit
      delay(100);
      
      // get new data!
      lsm.read();
    double newVector = lsm.accelData.y*lsm.accelData.y;
    newVector += lsm.accelData.z*lsm.accelData.z;
    newVector = sqrt(newVector);
      Serial.print("New Other Len Y Z: "); Serial.println(newVector);
      
        if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
        Serial.println("Stars!Stars!Stars!Stars!Stars!Stars!");
       
     squeak(); 
     colorWipe(strip.Color(175,75,148), 250); // Pink
    } else if (abs(newVector - storedVector) > MOVE_THRESHOLD){
      strip.Color(127, 127, 127);
    }
      
      
    }
    
    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i, c);
          strip.show();
          delay(wait);
      }
    }

    void beep (int speakerPin, float noteFrequency, long noteDuration)
    {    
      int x;
      // Convert the frequency to microseconds
      float microsecondsPerWave = 1000000/noteFrequency;
      // Calculate how many HIGH/LOW cycles there are per millisecond
      float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
      // Multiply noteDuration * number or cycles per millisecond
      float loopTime = noteDuration * millisecondsPerCycle;
      // Play the note for the calculated loopTime.
      for (x=0;x<loopTime;x++)   
              {   
                  digitalWrite(speakerPin,HIGH); 
                  delayMicroseconds(microsecondsPerWave); 
                  digitalWrite(speakerPin,LOW); 
                  delayMicroseconds(microsecondsPerWave); 
              } 
    }      
    
      
    void squeak() {
      for (int i=100; i<5000; i=i*1.45) {
        beep(speakerPin,i,60);
      }
      delay(10);
      for (int i=100; i<6000; i=i*1.5) {
        beep(speakerPin,i,20);
      }
    }
    
    void catcall() {
      for (int i=1000; i<5000; i=i*1.05) {
        beep(speakerPin,i,10);
      }
     delay(100);
     
      for (int i=1000; i<3000; i=i*1.03) {
        beep(speakerPin,i,10);
      }
      for (int i=3000; i>1000; i=i*.97) {
        beep(speakerPin,i,10);
      }
    }
    
    void ohhh() {
      for (int i=1000; i<2000; i=i*1.02) {
        beep(speakerPin,i,10);
      }
      for (int i=2000; i>1000; i=i*.98) {
        beep(speakerPin,i,10);
      }
    }
    
    void uhoh() {
      for (int i=1000; i<1244; i=i*1.01) {
        beep(speakerPin,i,30);
      }
      delay(200);
      for (int i=1244; i>1108; i=i*.99) {
        beep(speakerPin,i,30);
      }
    }
    

