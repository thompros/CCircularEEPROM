#include <CCircularEEPROM.h>
/*
We use this sketch to initialize the CCircularEEPROM.
FIRST OF ALL make sure to set your desired number & values of starting - ending points into header file. The number of these pairs defines the number
of CCircularEEPROM object instances. An instance's starting point must be always bigger (+1 or more) than the previous instance's ending point to avoid 
coverage between their data.
*/
void setup() {
  Serial.begin(9600);
  CCircularEEPROM A(CC_START_POINT_1,CC_END_POINT_1,true);   // First instance of CCircularEEPROM object           
  A.CC_Scan();



  //  CCircularEEPROM B(CC_START_POINT_2,CC_END_POINT_2,true);     // Second instance of CCircularEEPROM object     
  //  B.CC_Scan();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
