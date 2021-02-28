int i=0;                                            //Global counter varible

void setup() {
  Serial.begin(9600);                               //Make sure to use same Buad rate as in MATLAB
  pinMode(A0,INPUT);                                //A0 will be our analog input

}

void loop() {
  i++;                                              //Here I used "i" to keep track of the loop time
  Serial.print(String(analogRead(A0)) + " ");       //Sending the current reading without a line ending 
  if(i==9){i=0;Serial.println(analogRead(A0));}     //Each tenth reading (0 to 9) send with a line ending, this way data is sent in packets of 10 readings each
  delay(1);                                         //The delay is necessary to give MATLAB time to process the data
  
}
