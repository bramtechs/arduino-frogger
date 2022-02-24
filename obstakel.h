#ifndef OBSTAKEL_H
#define OBSTAKEL_H

struct Obstakel{
  int x;
  int y;
  int lengte;
  int richting;
};
int marge = 2;

// === VOERTUIGEN === //
Obstakel autos[] = {
  
  // achterste rij
  
  {5,3,3,1},
  
  {1,3,2,1},
  
  // middelste rij
  
  {4,2,2,-1},

  // voorste rij
  
  {2,1,2,1},

  {7,1,2,1},
};
int aantal_autos = sizeof(autos)/sizeof(autos[0]);

// === BOOMSTAMMEN === //
Obstakel stammen[] = {
  
  // achterste rij
  
  {5,7,3,1},
  
  {1,7,2,1},
  
  // middelste rij
  
  {4,6,2,1},

  // voorste rij
  
  {2,5,2,1},

  {7,5,2,1},

};
int aantal_stammen = sizeof(stammen)/sizeof(stammen[0]);

bool obstakel_raakt(int x, int y){
  // kijk voor aanrijding
  for (int i = 0; i < aantal_autos; i++)
  {
    int yy = autos[i].y;
    for (int j = 0; j < autos[i].lengte; j++) // rekening houden met lengte auto
    {
        int xx = autos[i].x+j;
        if (x == xx && y == yy){
          return true;
        }
    }
  }
  return false;
}

void stammen_beweeg(){
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
  }
}

void stammen_teken(){

}

void autos_beweeg(){
  if (huidigeFrame % 2 == 0)
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
}

void autos_teken(){
  // teken de voertuigen
  for (int i = 0; i < aantal_autos; i++){
    // is het voertuig-onderdeel binnen het speelveld?
    for (int j = 0; j < autos[i].lengte; j++){
      int x = autos[i].x+j;
      if (x <= 7 and x >= 0){
        // voertuig in beeld tekenen
        teken_pixel(x,i,RED);
      }
    }
  }
}
#endif
