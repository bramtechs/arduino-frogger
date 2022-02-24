//https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0
#ifndef JOYSTICK_H
#define JOYSTICK

const int VRx = A2;
const int VRy = A3;
const int SW = 5;

const int DEAD_ZONE = 50;

int vorigKwadrant;
int cooldownFrames;

void joy_setup()
{
  pinMode(VRx, INPUT);       // VRx
  pinMode(VRy, INPUT);       // VRy
  pinMode(SW, INPUT_PULLUP); //SW
}

// joystick in een richting vasthouden: matige snelheid
// joystick keer op keer "aanduwen": extra snelheid
int joy_get_kwadrant()
{
  float x = map(analogRead(VRx), 0, 1023, -512, 512);
  float y = map(analogRead(VRy), 0, 1023, -512, 512);

  //vrkwrtl(x^2+y^2)
  int joy_hoek = (int)(atan2(x, y) * RAD_TO_DEG) - 45;
  int hoek = (360 + joy_hoek) % 360;

  int kwadrant = hoek / (360 / 4) + 1;

  return kwadrant;
}

bool joy_is_deadzone(){
    float x = map(analogRead(VRx), 0, 1023, -512, 512);
    float y = map(analogRead(VRy), 0, 1023, -512, 512);
  
    //vrkwrtl(x^2+y^2)
    float afstand = sqrt(x*x+y*y);
    return afstand < DEAD_ZONE;
}

void joy_print()
{
  int xPosition = analogRead(VRx);
  int yPosition = analogRead(VRy);
  int mapX = map(xPosition, 0, 1023, -90, 90);
  int mapY = map(yPosition, 0, 1023, -90, 90);
  int kwadrant = joy_get_kwadrant();
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  if (joy_is_deadzone()){
    Serial.print(" DEADZONE ");
  }
  Serial.print(" | Richting: ");
  Serial.println(kwadrant);

  delay(100);
}
#endif
