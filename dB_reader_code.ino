const int MIC = 0; //This is the variable for the grove Arduino microphone input. Connected to pin A0 on the board
int i = 0; //The i variable will count the number of entries, crucial to end the programme correctly  
int adc; //This variable will hold the analog data recieved from the microphone
int dB; //This variable will hold the printable decibel level
int mic_sens = 3.16; //This variable is crucial in the regression conversion method for calculating the dB levels, as this sensitivity is specific to this microphone, I found through experimentation.   

void setup() {
  Serial.begin(9600); //The serial connection for the arduino board was set to 9600
  Serial.println("CLEARDATA"); //This clears the existing data to start a new set
  Serial.println("LABEL,Time,Date,dB Level"); //This sets the names of the columns in row 1 in Excel
  Serial.println("CUSTOMBOX1,LABEL,8 Hour Recording [Per Min]"); //This sets the name of checkbox 1 to be "8 Hour Recording [Per Min]".
  Serial.println("CUSTOMBOX2,LABEL,N/A"); //This sets the name of checkbox 1 to be "N/A".
  Serial.println("CUSTOMBOX3,LABEL,N/A"); //This sets the name of checkbox 1 to be "N/A".
  Serial.println("CUSTOMBOX1,SET,1"); //This sets checkbox 1 to be checked
  Serial.println("CUSTOMBOX2,SET,0"); //This sets checkbox 2 to be un-checked
  Serial.println("CUSTOMBOX3,SET,0"); //This sets checkbox 3 to be un-checked
}

void loop() {

  adc = analogRead(MIC); //Sets the variable "adc" to equal the raw analogue data from the microphone.
  dB = adc/ mic_sens; //This sets the dB variable to be the raw analogue data divided by the sensitivity of the microphone, inspired by regression conversion and tailored by personal experimentation for this microphone.
  
  Serial.print("DATA,TIME,DATE,"); //Data, here, is simply referring to the remainder of the outputs being labeled as such. The following specifications simply print the Time of the entry and the Date of the entry respectfully.
  Serial.println (dB); //The value of the calculated dB level is printed
  Serial.print(i++); //The integer i is incremented by 1, keeping track of the amount of entries
  Serial.println("SCROLLDATA_1"); //This line confirms that an entry has been made and allows the process to continue
  delay(60000); //A delay of 60000 means that an entry will be inputted every minuet

  if(i==480) //When 480 entries have been inputted
      {
        Serial.println("CUSTOMBOX1,GET"); //check the state of the checkbox1
        Serial.println("PAUSELOGGING"); //Pause the logging indefinitely for review from the user
      }
}
