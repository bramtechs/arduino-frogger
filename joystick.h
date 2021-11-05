//https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0
int VRx = A0;
int VRy = A1;
int SW = 4;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

const int DEAD_ZONE = 50;
const int VERTRAGING = 4; // maakt de kikker makkelijker te besturen
int vorigKwadrant;
int draaiFrame;

void joy_setup() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

// joystick in een richting vasthouden: matige snelheid
// joystick keer op keer "aanduwen": extra snelheid
int joy_get_richting()
{

    float x = map(analogRead(VRx), 0, 1023, -512, 512);
    float y = map(analogRead(VRy), 0, 1023, -512, 512);
  
    //vrkwrtl(x^2+y^2)
    float afstand = sqrt(x*x+y*y);
    if (afstand > DEAD_ZONE)
    {
      //double rad_to_deg = 180.0 / PI;

      
      int joy_hoek = (int)(atan2(x,y)*RAD_TO_DEG)-45;
      int hoek = (360+joy_hoek)%360;
            
      int kwadrant = hoek / (360/4)+1;
      
      // voorkomt dat de kikker even snel als het beeld loopt bij eenzelfde joystick houding (te snel)
      // het spel wacht een paar frames tussen bewegingen
      // zorgt voor een trage kikker die ook "responsief" aanvoelt
      if (vorigKwadrant == kwadrant)
      {
        // de speler houdt dezelfde richting aan, voorkom dat de kikker "wegschiet"
        // we verlagen de FPS niet, anders krijgen we trage obstakels
        // het verkeer is veel sneller dan de kikker, niet dezelfde snelheid!
        if (huidigeFrame > draaiFrame + VERTRAGING){
          draaiFrame = huidigeFrame;
          return kwadrant;
        }
      }
      else
      {
        // de joystick beweegt in een nieuwe richting!
        vorigKwadrant = kwadrant;
        draaiFrame = huidigeFrame;
        return kwadrant;
      }
    }
    else{
      // de joystick staat weer in het midden, cooldown valt weg
      draaiFrame = 0;
    }
  return 0;
}

void joy_print() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -90, 90);
  mapY = map(yPosition, 0, 1023, -90, 90);
  float x = mapX/512.0;
  float y = mapY/512.0;
  
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" | Y: ");
  Serial.print(y);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(100);
}
