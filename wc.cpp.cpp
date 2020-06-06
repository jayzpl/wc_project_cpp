//POP_2020_01_10_projekt_2_Zasada_Jakub_EIT_7_181176.cpp 
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

fstream plik;
string nazwa_pliku;
char znak;
int ilosc_litery[1000];
int ilosc_slow[100];
char glowny_zakreschar[80];
char glowny_zakresint[80];
char glowny_zakreswielkie[80];
int licznik, licznikdwa,wlicznik;
char zakresik[240];

void poczatek() {
	plik.clear();
	plik.seekg(0, ios::beg);
}

void zakres(string wzakres) {
	int dlugosc;
	int from = 0;
	int to = 0;
	int liczba_one=0;
	int liczba_two = 0;
	int wielka_one = 0;
	int wielka_two = 0;
	dlugosc = wzakres.length();

	for (int i = 0; i < dlugosc; i++) {  //'parser' mojego pomyslu 
		if (wzakres[i] == ' ' || wzakres[i]=='-') { continue; }
		else {
			if (from == 0) { from = wzakres[i]; continue; }
			if (to == 0) { to = wzakres[i]; continue; }
			if (liczba_one == 0) { liczba_one = wzakres[i]; continue; }
			if (liczba_two == 0) { liczba_two = wzakres[i]; continue; }
			if (wielka_one == 0) { wielka_one = wzakres[i]; continue; }
			if (wielka_two == 0) { wielka_two = wzakres[i]; continue; }
		}
	}
	licznik = 0;	//licznik malych znakow
	licznikdwa = 0;	//licznik cyfr
	wlicznik = 0;	//licznik duzych znakow

	for(int i=from; i<=to; i++){
		glowny_zakreschar[licznik] = char(i);
		licznik++;
	}
	for (int i = liczba_one; i <= liczba_two; i++) {
		glowny_zakresint[licznikdwa] = char(i);
		licznikdwa++;
	}
	for (int i = wielka_one; i <= wielka_two; i++) {
		glowny_zakreswielkie[wlicznik] = char(i);
		wlicznik++;
	}
	for (int i = 0; i < licznik; i++) {
		zakresik[i] = glowny_zakreschar[i];
	}
	for (int i = 0; i < licznikdwa; i++) {
		zakresik[licznik] = glowny_zakresint[i];
		licznik++;
	}
	for (int i = 0; i < wlicznik; i++) {
		zakresik[licznik] = glowny_zakreswielkie[i];
		licznik++;
	}
	cout << endl << "Twoj zakres znakow: ";
	for (int i = 0; i < licznik; i++) {
		cout << zakresik[i] << " ";
	}
	cout << endl;
}

void wypisz_zawartosc() {
	poczatek();
	cout << endl;
	cout << "Tekst z pliku dla wybranego zakresu:" << endl<<endl;
	while (plik.get(znak)) {
		for (int i = 0; i < licznik; i++) {
			if (znak == ' ' || znak == '\n') { cout << znak; break; }
			else if (zakresik[i] == znak) {
				cout << znak;
			}
		}
	}
	cout << endl;
}

void statystyka_znakow() {
	char litera[1000];
	int liczba_spacji = 0;
	int liczba_efl = 0;
	int liczba_liter = 0;
	poczatek();
	int licznik_dwa = 0;
	char znaczek;
	while (plik.get(znak)) {
		if (znak == ' ') { liczba_spacji++; }
		if (znak == '\n') { liczba_efl++; }
		for (int i = 0; i < licznik; i++) {
			if (znak != ' ' && znak != '\n' && znak==zakresik[i]) {
				liczba_liter++; 
				litera[licznik_dwa] = znak; //wlozenie sprawdzonego znaku do wektora liter
				licznik_dwa++;
			}
		}
	}
	cout << "liczba spacji: " << liczba_spacji << endl;
	cout << "liczba enterow: " << liczba_efl << endl;
	cout << "liczba liter: " << liczba_liter << endl;

	for (int i = 0; i < licznik_dwa; i++) {
		znaczek = litera[i];
		for (int j = 0; j < licznik_dwa; j++) {
			if (litera[j] == znaczek) {
				ilosc_litery[i] = ilosc_litery[i] + 1;
			}
		}
	}
	for (int i = 0; i < licznik_dwa; i++) {
		cout << litera[i] << " : " << ilosc_litery[i] << endl;
	}
}

void liczba_bajtow() {
	ifstream bajt(nazwa_pliku, ios::binary | ios::ate);
	int liczba;
	liczba = bajt.tellg();
	cout <<endl<< "Liczba bajtow pliku: " << liczba <<" B";
	bajt.close();
}

void liczba_lini() {
	poczatek();
	int ilosc_lini = 0;
	string linia;
	while (getline(plik,linia)) {
		++ilosc_lini;
	}
	cout << endl << "Ilosc linii: " << ilosc_lini<<endl;
}

void dlugosc_lini() {
	poczatek();
	string linia;
	int licznik = 0;
	int dlugosc[1000];
	while (getline(plik, linia)) {
		dlugosc[licznik] = linia.length();
		licznik++;
	}
	int max = dlugosc[0];
	for (int i = 1; i < licznik; i++) {
		if (dlugosc[i] > max) {
			max = dlugosc[i];
		}
	}
	cout << "Max linia: "<<max<< endl;
}

void statystyka_slow() {
	poczatek();
	string slowo;
	string slowko;
	string slowa[100];
	int licznik = 0;
	while (plik >> slowo) {
		slowa[licznik] = slowo;
		licznik++;
	}
	for (int i = 0; i < licznik; i++) {
		slowko = slowa[i];
		for (int j = 0; j < licznik; j++) {
			if (slowa[j]==slowko) {
				ilosc_slow[i] = ilosc_slow[i] + 1;
			}
		}
		cout << slowa[i] << " : " << ilosc_slow[i] << endl;
	}
}

int main() {  
	string wzakres;
	char wybor_one, wybor_two, wybor_three, wybor_four, wybor_five;

	cout << "Podaj nazwe pliku (razem z .txt): ";
	cin >> nazwa_pliku;
	plik.open(nazwa_pliku, ios::_Nocreate);

	if (plik.good() == false) {
		cout << "Cos poszlo nie tak !" << endl;
		cout << "Plik musi byc w tym samym folderze co program." << endl;
		cout << "Plik musi miec rozszerzenie .txt ." << endl;
	}
	else {
		cout << "statystyka znakow? : ";
		cin >> wybor_one;
		cout << "liczba bajtow? : ";
		cin >> wybor_two;
		cout << "liczyc linie? : ";
		cin >> wybor_three;
		cout << "maksymalna dlugos linii? : ";
		cin >> wybor_four;
		cout << "statystyka slow ? : ";
		cin >> wybor_five;
		cout << "podaj zakresy (np a-z A-Z 1-9): ";
		cin.clear();
		cin.ignore(INT_MAX, '\n'); //czyszczenie buffora cin
		getline(cin, wzakres);
		cout << endl;
		zakres(wzakres);
		wypisz_zawartosc();

		if (wybor_two == 't') { liczba_bajtow(); }
		if (wybor_three == 't') { liczba_lini(); }
		if (wybor_four == 't') { dlugosc_lini(); }
		if (wybor_one == 't') { statystyka_znakow(); }
		if (wybor_five == 't') { statystyka_slow(); }
		cout << endl;
	}
	plik.close();
}
