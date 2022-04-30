#pragma once
struct Obstakel{
  int x;
  int y;
  int richting;
};
int marge = 2;

// === VOERTUIGEN === //
Obstakel autos[] = {

  {1,6,1},
  {2,6,1},
  
  {5,6,1},
  {6,6,1},

  {2,5,-1},
  {3,5,-1},
  
  {5,5,-1},
  {6,5,-1},
  {7,5,-1},
  
  {2,4,1},
  
  {3,4,1},
  
  {4,2,-1},
  {5,2,-1},
  
  {2,1,1},
  {3,1,1},
  {7,1,1},
  {6,1,1},
};
int aantal_autos = sizeof(autos)/sizeof(autos[0]);

// === BOOMSTAMMEN === //
Obstakel stammen[] = {
  
  {1,12,1},
  {2,12,1},
  {3,12,1},
  
  {5,12,1},
  {6,12,1},
  {7,12,1},

  {2,11,-1},
  {3,11,-1},
  {4,11,-1},

  {1,10,1},
  {2,10,1},
  {3,10,1},
  
  {4,9,1},
  {3,9,1},
  {2,9,1},

  {5,9,1},
  {6,9,1},
  {7,9,1},

};
int aantal_stammen = sizeof(stammen)/sizeof(stammen[0]);

bool obstakel_raakt(int x, int y){
  // kijk voor aanrijding
  for (int i = 0; i < aantal_autos; i++)
  {
    int yy = autos[i].y;
    int xx = autos[i].x;
      if (x == xx && y == yy){
        return true;
      }
    }
  return false;
}

boolean kikkerMeegevoerd = false;

void stammen_update(){
  if (huidigeFrame % 10 == 0)
  {
    for (int i = 0; i < aantal_stammen; i++){
      int x = stammen[i].x;
      x += stammen[i].richting;

      if (x > 7+marge){
        x = -marge;
      }else if (x < -marge){
        x = 7+marge;
      }
      stammen[i].x = x;
    }
    kikkerMeegevoerd = false;
  }

  // teken de rivier
  for (int y = 9; y <= 12; y++){
    int rij = 0b11111111; // alle ledjes opgelicht
     // vul de rij op
    for (int x = 0; x < 8; x++){
      boolean isStam = false;
      for (int i = 0; i < aantal_stammen; i++){
        // is op deze pixel een boomstam?
        if (stammen[i].x == x && stammen[i].y == y){
          // boomstam hier, pixel leeg maken
          rij &= ~(1 << x); // zet de bit op positie x 0
          
          //voer de kikker mee, als deze op een stam staat
          if (!kikkerMeegevoerd && huidigeFrame % 10 == 0 && kikkerX == x && kikkerY == y){
              int richting = stammen[i].richting;
              kikker_beweeg(richting,0);
              kikkerMeegevoerd = true; //voorkomt dat de kikker meermaals verplaatst wordt, als x opgeteld wordt.
          }
          isStam = true;
          break;
        }
      }
      // geen enkele stam is hier, deze pixel is water!
      if (!isStam && kikkerX == x && kikkerY == y && !TEST_MODE){
         // verdrink de kikker
         kikker_sterf();
      }
    }
    lc.setRow(1,y%8,rij); //geef de rij door
  }
}

void autos_update(){
  if (huidigeFrame % 4 == 0)
  {
    for (int i = 0; i < aantal_autos; i++){
      int x = autos[i].x;
      x += autos[i].richting;

      if (x > 7+marge){
        x = -marge;
      }else if (x < -marge){
        x = 7+marge;
      }
      autos[i].x = x;
    }
  }
  
  // teken de voertuigen
  for (int i = 0; i < aantal_autos; i++){
    // is het voertuig-onderdeel binnen het speelveld?
      int x = autos[i].x;
      int y = autos[i].y;
      if (x <= 7 and x >= 0){
        // voertuig in beeld tekenen
        teken_pixel(x,y);

        // is de kikker hier?, rijdt deze omver
        if (kikkerX == x && kikkerY == y && !TEST_MODE){
          kikker_sterf();
        }
      }
  }
}