

// ==== HUISJES ===
struct Huis {
  int x;
  bool voltooid;
};

Huis huisjes[] = {
  { 0, false },
  { 2, false },
  { 4, false },
  { 6, false },
};
int aantal_huisjes = sizeof(huisjes) / sizeof(huisjes[0]);

bool is_huisje(int x) {
  for (int i = 0; i < aantal_huisjes; i++) {
    if (huisjes[i].x == x) {
      return true;
    }
  }
  return false;
}

void huisjes_update() {
  int y = 15;
  // teken muren rond de huisjes
  for (int x = 0; x < 8; x++) {
    if (!is_huisje(x)) {
      teken_pixel(x, y);

      // duw de kikker weg wanneer deze in een muur zit
      if (x % 2 == 1) {
        if (x == kikkerX && kikkerY == y) {
          kikkerY--;
        }
      }
    }
  }

  for (int i = 0; i < aantal_huisjes; i++) {
    //teken de huisjes
    if (huisjes[i].voltooid) {
      if (huidigeFrame % 5 == 0) {
        teken_pixel(huisjes[i].x, y);
      }
    } else {
      // vul het huisje op met de kikker
      if (huisjes[i].x == kikkerX && kikkerY == y) {
        huisjes[i].voltooid = true;
        kikker_win();
      }
    }
  }
}
