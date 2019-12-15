// DC Motor product link http://bit.ly/34lLurI
#define ENCODEROUTPUT 2096

#define enA 9
#define in1 6
#define in2 7

#define HALLSEN_A  3

//The sample code for driving one way motor encoder
volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;

void setup() {

  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Set initial rotation direction
  analogWrite(enA, 100); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  encoderValue = 0;
  previousMillis = millis();
   
}

void loop() {

 // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

   

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
    if ( rpm > 0) {
      

      Serial.print(encoderValue);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }
    
    encoderValue = 0;
  }
}

void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);
}


void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}
