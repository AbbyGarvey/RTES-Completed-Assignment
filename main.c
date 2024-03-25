/*
  AUTHOR: K00286554 Abby Garvey
  DATE: 25/03/24
*/


#define GREEN1 2
#define YELLOW1 3
#define RED1 4

#define GREEN2 13
#define YELLOW2 12
#define RED2 11

#define BUTTON1 7
#define BUTTON2 8


#define LDR A0

struct Lights
{
  int red;
  int yellow;
  int green;
};

/*SET UP P1 STRUCT*/
int state1[6] = {3, 2, 1, 1, 1, 1};
int state2[6] = {1, 1, 1, 3, 2, 1};

int dayTime[6] = {10, 2, 2, 10, 2, 2};
int nightTime[6] = {30, 2, 2, 20, 2, 2};

Lights l1;
Lights l2;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LDR, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

  pinMode(GREEN1, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(RED1, OUTPUT);

  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(RED2, OUTPUT);
  Serial.begin(9600);

  /*SET UP L1 STRUCT*/
  l1.red = RED1;
  l1.yellow = YELLOW1;
  l1.green = GREEN1;

  /*SET UP L2 STRUCT*/
  l2.red = RED2;
  l2.yellow = YELLOW2;
  l2.green = GREEN2;
}

void lightsState(bool red, bool yellow, bool green, Lights l)
{
  digitalWrite(l.red, red);
  digitalWrite(l.yellow, yellow);
  digitalWrite(l.green, green);
}

// 1, 2, 3   red. yellow, green
void lightsSwitch(int state, Lights l)
{
  switch(state)
  {
    case 1:
      lightsState(true, false, false, l);
      break;
    case 2:
      lightsState(false, true, false, l);
      break;
    case 3:
      lightsState(false, false, true, l);
      break;

  }
}
// the loop function runs over and over again forever

bool day()
{
  //Serial.println(analogRead(LDR));
  return analogRead(LDR) > 50;
}

unsigned long prevTimestamp = 0;
int i = 0;
int timeOn = 0;

void loop() {

  unsigned long m = millis();

  lightsSwitch(state1[i], l1);
  lightsSwitch(state2[i], l2);

  if(digitalRead(BUTTON1) != digitalRead(BUTTON2) && timeOn > 2000)
  {
    // if there is traffic at light 1 and light 2 is green or if there is traffic at light 2 and light 1 is green
    if( (digitalRead(BUTTON1) && state2[i] == 3) || (digitalRead(BUTTON2) && state1[i] == 3))
    {
      timeOn = 2000;
    }
  }

  if(m - prevTimestamp >= timeOn)
  {
    i++;
    i = i%6;
    if(day())
    {
      timeOn = dayTime[i]*1000;
      Serial.println("It is daytime");
    }
    else
    {
      timeOn = nightTime[i]*1000;
      Serial.println("It is nighttime");

    }
    
    prevTimestamp = m;
  }
  
               
}
