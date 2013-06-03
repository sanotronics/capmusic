#include <CapacitiveSensor.h>

/****************************/
/******** CapMusic **********/
/****************************/

CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 2 & 3, pin 3 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10M resistor between pins 4 & 5, pin 5 is sensor pin, add a wire and or foil

const int numMuestras = 6;    // Number of averaging samples
int contador_buf = 0;         // Counter for averaging
long suma1 = 0;               // Storage for sums 1 & 2
long suma2 = 0;
long valores1[numMuestras];   // Values sampled
long valores2[numMuestras];
float prom1 = 0;              // Averages
float prom2 = 0;

void setup(){
   cs_2_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_4_5.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop(){
    // Reset variables for new loop
    suma1 = 0;
    suma2 = 0;    
    prom1 = 0;
    prom2 = 0;

    // Read inputs
    valores1[contador_buf] =  cs_2_3.capacitiveSensor(10);
    valores2[contador_buf] =  cs_4_5.capacitiveSensor(10);
    
    // Increase counter and if arrived to the end of the buffer, reset counter to zero
    contador_buf++;
    if (contador_buf > (numMuestras-1)) contador_buf = 0;
    
    // Sum all values in buffer
    for(int i = 0; i <= numMuestras; i++){    
      suma1 += valores1[i];
      suma2 += valores2[i];      
    }
    
    // Average samples
    prom1 = suma1/numMuestras;
    prom2 = suma2/numMuestras;    
    
    // Send to processing
      Serial.print("a");
      Serial.print(prom1);                  // print sensor output 1
      Serial.print("\n");
  
      Serial.print("b");    
      Serial.print(prom2);                  // print sensor output 2
      Serial.print("\n");
  
    delay(30);  // delay to give some time to receiver

}
