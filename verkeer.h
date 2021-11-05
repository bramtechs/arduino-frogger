struct Auto{
  int x;
  int y;
  int richting;
};

Auto autos[] = {
  
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
int marge = 1;

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
