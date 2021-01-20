#define LED  PC13
#define BUZZER  PB9
#define DRV1_ENABLE  PA12
#define DRV1_USM0  PA11
#define DRV1_USM1  PA8
#define DRV1_USM2  PB15
#define DRV1_DIRECTION  PB12
#define DRV1_STEP  PB13

#define DRV2_ENABLE  PA5
#define DRV2_USM0  PA4
#define DRV2_USM1  PA3
#define DRV2_USM2  PA2
#define DRV2_DIRECTION  PC15
#define DRV2_STEP  PA0
#define DELAYDURATION 1500u

String CmdStr;
char Axis, Direction;
unsigned int NumSteps, i;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(DRV1_ENABLE, OUTPUT);
  pinMode(DRV1_USM0, OUTPUT);
  pinMode(DRV1_USM1, OUTPUT);
  pinMode(DRV1_USM2, OUTPUT);
  pinMode(DRV1_DIRECTION, OUTPUT);
  pinMode(DRV1_STEP, OUTPUT);

  pinMode(DRV2_ENABLE, OUTPUT);
  pinMode(DRV2_USM0, OUTPUT);
  pinMode(DRV2_USM1, OUTPUT);
  pinMode(DRV2_USM2, OUTPUT);
  pinMode(DRV2_DIRECTION, OUTPUT);
  pinMode(DRV2_STEP, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(DRV1_ENABLE, LOW); //Logic LOW enables the driver 
  digitalWrite(DRV2_ENABLE, LOW); //Logic LOW enables the driver 
  // M2 M1 M0
  //  0  0  0: Full step
  //  1  0  0: 1/16
  //  1  0  1: 1/32
  
  digitalWrite(DRV1_USM0, LOW);
  digitalWrite(DRV1_USM1, LOW);
  digitalWrite(DRV1_USM2, LOW);

  digitalWrite(DRV2_USM0, LOW);
  digitalWrite(DRV2_USM1, LOW);
  digitalWrite(DRV2_USM2, LOW);

  digitalWrite(DRV1_DIRECTION, HIGH);
  digitalWrite(DRV1_STEP, LOW);

  digitalWrite(DRV2_DIRECTION, HIGH);
  digitalWrite(DRV2_STEP, LOW);

  digitalWrite(BUZZER, LOW);

}

void loop() {
  Serial.print(">> ");
  while( 1 ) {
    Serial.print(">> ");
    while( !Serial.available() );
    CmdStr = Serial.readString();
    Serial.println( CmdStr );

    if( (CmdStr.length() < 3) || (CmdStr.length() > 7)  ) {
      Serial.println("Invalid input");
      continue;
    }
    
    Axis = CmdStr.charAt( 0 );
    Direction = CmdStr.charAt( 1 );

    if( (Axis != 'a') && (Axis != 'A') && (Axis != 'z')&&(Axis != 'Z') ) {
      Serial.println("Invalid input");
      continue;
    }
    
    if( (Direction != '+') && (Direction != '-') ) {
      Serial.println("Invalid input");
      continue;
    }
    
    NumSteps = CmdStr.substring(2).toInt();

    while( Serial.available() ) Serial.read();

    switch( Axis ) {
      case 'z':
      case 'Z':
        if( Direction == '+' )
          digitalWrite(DRV1_DIRECTION, LOW);
        else
          digitalWrite(DRV1_DIRECTION, HIGH);
        
        for(i=0; i<NumSteps; i++) {
          //Serial.print( Direction );
      
          digitalWrite(DRV1_STEP, HIGH);
          delayMicroseconds(DELAYDURATION);

          digitalWrite(DRV1_STEP, LOW);
          delayMicroseconds(DELAYDURATION);
        }  
        break;

      case 'a':
      case 'A':
        if( Direction == '+' )
          digitalWrite(DRV2_DIRECTION, HIGH);
        else
          digitalWrite(DRV2_DIRECTION, LOW);
        
        for(i=0; i<NumSteps; i++) {
          //Serial.print( Direction );
      
          digitalWrite(DRV2_STEP, HIGH);
          delayMicroseconds(DELAYDURATION);

          digitalWrite(DRV2_STEP, LOW);
          delayMicroseconds(DELAYDURATION);
        }
        break;
    }
    Serial.println("");
    Serial.println("OK");
    
  digitalWrite(BUZZER, HIGH);
  delayMicroseconds(20000UL);
  digitalWrite(BUZZER, LOW);
    
  }
}
