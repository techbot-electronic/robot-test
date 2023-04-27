#define LEFT_SENSOR 11
#define RIGHT_SENSOR 8
#define MIDDLE_LEFT_SENSOR 10
#define MIDDLE_RIGHT_SENSOR 9

#define SPEED 80
#define LINE_BLACK_VALUE 0
#define LINE_WHITE_VALUE 1
int ENA = 3; // PWM
int IN1 = 2; 
int IN2 = 4;

int ENB = 5; // PWM
int IN3 = 6;
int IN4 = 7;

void TURN_RIGHT() {
    digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void TURN_LEFT() {
    digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void TURN_AHEAD() {
    digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int right = digitalRead(RIGHT_SENSOR);
  int left = digitalRead(LEFT_SENSOR);
  int middle_right = digitalRead(MIDDLE_RIGHT_SENSOR);
  int middle_left = digitalRead(MIDDLE_LEFT_SENSOR);

  // Serial.print("SENSOR Val: ");
  // Serial.print("left: ");
  // Serial.print(left);
  // Serial.print(" - ");
  // Serial.print("right: ");
  // Serial.print(right);
  //  Serial.print(" - ");
  // Serial.print("middle right: ");
  // Serial.print(middle_right);

  //  Serial.print(" - ");
  // Serial.print("middle left: ");
  // Serial.print(middle_left);
  //    Serial.println("");


   int left_speed_front = 0;
   int right_speed_front = 0;

   
if ((middle_left == LINE_WHITE_VALUE   || middle_right == LINE_WHITE_VALUE) && left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE) {
    Serial.println("FORWARD");
    TURN_AHEAD();
    left_speed_front = SPEED;
    right_speed_front = SPEED;
  }
  else  if ( (middle_left == LINE_BLACK_VALUE && right == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE ) || (middle_left == LINE_BLACK_VALUE && left == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE) 
  || (right == LINE_WHITE_VALUE)  ||  (left == LINE_WHITE_VALUE)  )
    
     {
 
          if ((middle_left == LINE_BLACK_VALUE && left == LINE_BLACK_VALUE && middle_right == LINE_BLACK_VALUE) || (left == LINE_WHITE_VALUE))    {
            Serial.println("TURN RIGHT");
            TURN_RIGHT();
            left_speed_front = 100;
            right_speed_front = 180;
          } else {
            Serial.println("TURN LEFT");
            TURN_LEFT();
            left_speed_front = 180;
            right_speed_front = 100;
          }


    } 



   else if (middle_left == LINE_WHITE_VALUE && (middle_right == LINE_BLACK_VALUE || right == LINE_BLACK_VALUE) )  
    {
      
    Serial.println("TURN RIGHT");
      TURN_AHEAD();

    left_speed_front = 0;
    right_speed_front = SPEED;
  } else if ((middle_right == LINE_WHITE_VALUE && (middle_left == LINE_BLACK_VALUE || left == LINE_BLACK_VALUE) ) ) {
   Serial.println("TURN LEFT");
   TURN_AHEAD();
    left_speed_front = SPEED;
    right_speed_front = 0;
  } 

   analogWrite(ENB, left_speed_front);
   analogWrite(ENA, right_speed_front);

}
