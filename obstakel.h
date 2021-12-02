struct Obstakel{
  int x;
  int y;
  int richting;
};
int marge = 1;

// === BOOMSTAMMEN === //
Obstakel stammen[] = {
  
  // achterste rij
  
  {5,7,1},
  {6,7,1},
  {7,7,1},
  
  {1,7,1},
  {2,7,1},
  
  // middelste rij
  
  {4,6,1},
  {5,6,1},

  // voorste rij
  
  {2,5,1},
  {3,5,1},

  {7,5,1},
  {8,5,1},

};
int aantal_stammen = sizeof(stammen)/sizeof(stammen[0]);

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
  // maak heel de rivier opgelicht
  for (int y = 5; y <= 7; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      scherm[x][y] = true;
    }
  }
  
  for (int p = 0; p < 8; p++){
    scherm[stammen[p].x][stammen[p].y] = false;
  }
  
  // teken de voertuigen
  for (int i = 0; i < aantal_stammen; i++){
    // is het stam-onderdeel binnen het speelveld?
    int x = stammen[i].x;
    if (x <= 7 and x >= 0){
      // stam is in beeld teken laat een holte vrij
      scherm[stammen[i].x][stammen[i].y] = false;
    }
  }
}

// === VOERTUIGEN === //
Obstakel autos[] = {
  
  // achterste rij
  
  {5,3,1},
  {6,3,1},
  {7,3,1},
  
  {1,3,1},
  {2,3,1},
  
  // middelste rij
  
  {4,2,-1},
  {5,2,-1},

  // voorste rij
  
  {2,1,1},
  {3,1,1},

  {7,1,1},
  {8,1,1},

};
int aantal_autos = sizeof(autos)/sizeof(autos[0]);


void autos_beweeg(){
  if (huidigeFrame % 10 == 0)
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
    int x = autos[i].x;
    if (x <= 7 and x >= 0){
      // voertuig in beeld teken het
      scherm[autos[i].x][autos[i].y] = true;
    }
  }
}
