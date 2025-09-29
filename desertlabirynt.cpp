#include <iostream>
#include <ctime>
#include <string>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 20;

char labirynty[5][HEIGHT][WIDTH + 1] = {
{
"####################",
"# # # #",
"# ### # ##^## # ## #",
"# # # # # # #",
"# # ^#### # # # # ##",
"# # # # # #",
"##### # # ^#### # #",
"# # # # # #",
"# # e#",
"####################"
},
{
"###########^########",
"# # #",
"# ####### ###### # #",
"# # # #",
"### ### ####### ### ",
"# # # #",
"# ### ####^## #### #",
"# # # # #",
"# # #####^# #### e#",
"####################"
},
{
"############^#######",
"# #",
"# ## # #^# # ##### #",
"# # # # # #",
"###### # ### # ### #",
"# # # # #",
"# #### ####### ### #",
"# #",
"# e #",
"###########^########"
},
{
"############^#######",
"# # # ##",
"### # #### # #### #",
"# # # # # # #",
"# ### # #^## # ## ##",
"# # # #",
"##### ####### #### #",
"# # # ^",
"# e# ##",
"####################"
},
{
"##########^#########",
"# # # #",
"# ##### # #### # # #",
"# # # # # #",
"### # # #^## #### e",
"# # # # #",
"# ### ###### # #####",
"# # # #",
"# # #",
"########^###########"
}
};

int startX = 1, startY = 1;

string wycentrujTekst(const string& tekst, int szerokosc = SCREEN_WIDTH) {
int padding = (szerokosc - (int)tekst.length()) / 2;
if (padding < 0) padding = 0;
return string(padding, ' ') + tekst;
}

void pokazMenu() {
system("clear");
int pusteWiersze = (SCREEN_HEIGHT - 9) / 2;
for (int i = 0; i < pusteWiersze; i++);
cout << "\033[33m" << (" DESERT LABIRYNT") << "\033[0m" << "\n\n";
cout << wycentrujTekst(" wersja v1,0") << "\n";
cout << "\033[34m" << (" oryginalna gra firmy NEITOX") << "\033[0m" << endl;
cout << wycentrujTekst(" === MENU GRY ===") << "\n\n";  
cout << wycentrujTekst(" K – Zagraj konkretny poziom") << "\n";  
cout << wycentrujTekst(" Enter – Normalna gra (5 poziomów)") << "\n";  
cout << wycentrujTekst(" Spacja – Gra na czas") << "\n";  
cout << wycentrujTekst(" ESC – Wyjście") << "\n\n";  


}

void pokazLabirynt(char mapa[HEIGHT][WIDTH + 1], int x, int y, double czas = -1) {
cout << "\033[2J\033[1;1H";;
int pusteWiersze = (SCREEN_HEIGHT - HEIGHT - 3) / 2;
for (int i = 0; i < pusteWiersze; i++) cout << "\n";

for (int i = 0; i < HEIGHT; ++i) {  
    cout << wycentrujTekst("", SCREEN_WIDTH - WIDTH);  
    for (int j = 0; j < WIDTH; ++j) {  
        if (i == y && j == x)  
            cout << '@';  
        else  
            cout << mapa[i][j];  
    }  
    cout << "\n";  
}  
cout << "\n" << wycentrujTekst("Sterowanie: WASD, ESC - wyjście z poziomu") << "\n";  

if (czas >= 0) {  
    cout << wycentrujTekst("Czas: " + to_string(czas) + " s") << "\n";  
}

}

bool grajPoziom(char mapa[HEIGHT][WIDTH + 1], bool pokazCzas = false, double* czasWynik = nullptr) {
int x = startX, y = startY;
clock_t start = clock();

while (true) {  
    double aktualnyCzas = (double)(clock() - start) / CLOCKS_PER_SEC;  
    pokazLabirynt(mapa, x, y, pokazCzas ? aktualnyCzas : -1);  
 
        char ruch = getchar();  
        if (ruch == 27) return false; // ESC wyjście z poziomu  

        int nx = x, ny = y;  
        if (ruch == 'w') ny--;  
        else if (ruch == 's') ny++;  
        else if (ruch == 'a') nx--;  
        else if (ruch == 'd') nx++;  

        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && mapa[ny][nx] != '#') {  
            x = nx;  
            y = ny;  
        }  
    }  

    if (mapa[y][x] == 'e') {  
        if (pokazCzas && czasWynik) {  
            *czasWynik = (double)(clock() - start) / CLOCKS_PER_SEC;  
        }  
        return true;  
    }  
}



void trybKonkretny() {
pokazMenu();
cout << "\n" << wycentrujTekst("Wybierz poziom (1-5): ");
char c = getchar();
if (c >= '1' && c <= '5') {
int nr = c - '1';
grajPoziom(labirynty[nr]);
}
}

void trybNormalny() {
for (int i = 0; i < 5; ++i) {
if (!grajPoziom(labirynty[i])) break;
}
}

void trybNaCzas() {
double najlepszy = 9999;
while (true) {
clock_t startCzas = clock();
bool przerwano = false;
for (int i = 0; i < 5; ++i) {
if (!grajPoziom(labirynty[i], true)) {
przerwano = true;
break;
}
}
if (przerwano) break;

double czas = (double)(clock() - startCzas) / CLOCKS_PER_SEC;  
    if (czas < najlepszy) najlepszy = czas;  

    system("clear");  
    int pusteWiersze = (SCREEN_HEIGHT - 6) / 2;  
    for (int i = 0; i < pusteWiersze; i++) cout << "\n";  

    cout << wycentrujTekst("Koniec gry na czas!") << "\n";  
    cout << wycentrujTekst("Czas: " + to_string(czas) + " s") << "\n";  
    cout << wycentrujTekst("Rekord: " + to_string(najlepszy) + " s") << "\n";  
    cout << wycentrujTekst("Spacja - zagraj ponownie | ESC - menu") << "\n";  

    char c;  
    do {  
        c = getchar();  
        if (c == 27) return;  
    } while (c != ' ' && c != 27);  
}

}

int main() {
while (true) {
pokazMenu();
char wybor = getchar();
if (wybor == 'k' || wybor == 'K') trybKonkretny();
else if (wybor == '\r' || wybor == 10) trybNormalny();
else if (wybor == ' ') trybNaCzas();
else if (wybor == 27) break;
}

return 0;

}
