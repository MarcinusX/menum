#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
int liczbaRownan, liczbaIteracji;
double dokladnosc;
bool czyDokladnosc = false, czyMacierzWynikowa = false;
double** A;
double** M;
double* b;
double* N;
double* poprzedniaMacierzX;
double* macierzX;

void inicjalizacjaMacierzy ();
void wyborWarunkuZakonczeniaAlgorytmu ();
void pobierzDaneZPlikuDoMacierzyAOrazB ();
double* wyliczWartosciMacierzyN ();
double** wyliczWartosciMacierzyM ();
bool czyMacierzAZbieznaWiersze ();
bool czyMacierzAZbieznaKolumny ();
bool czyMacierzAZbiezna();
bool czyMacierzAZbieznaDlaKolumn();
bool czyMacierzAZbieznaDlaWierszy();
bool czyMacierzAZbieznaPierwiastek();
bool czySpelnionaDokladnosc (double* poprzedniaMacierzX, double* macierzX);
void liczWgLiczbyIteracji ();
void liczWgDokladnosci();
void wyliczWartosciMacierzyWynikowej ();
void wyswietlMacierze();
void wyswietlMacierzDwuwymiarowa (double** macierz);
void wyswietlMacierz (double* macierz);

int main() {
    cout<<"Podaj liczbe rownan: ";
    cin>>liczbaRownan;
    inicjalizacjaMacierzy();
    wyborWarunkuZakonczeniaAlgorytmu();
    pobierzDaneZPlikuDoMacierzyAOrazB();

    if(czyMacierzAZbiezna()) {
        N = wyliczWartosciMacierzyN();
        M = wyliczWartosciMacierzyM();
        wyliczWartosciMacierzyWynikowej();
        wyswietlMacierze();
    } else {
        cout<<"Macierz A nie spelnia warunku zbieznosci! :( "<<endl;
    }

    return 0;
}
bool czyMacierzAZbiezna()
{
    return czyMacierzAZbieznaDlaKolumn() || czyMacierzAZbieznaDlaWierszy() || czyMacierzAZbieznaPierwiastek();
}
void inicjalizacjaMacierzy () {

    A = new double* [liczbaRownan];
    M = new double* [liczbaRownan];
    b = new double [liczbaRownan];
    N = new double [liczbaRownan];
    poprzedniaMacierzX = new double [liczbaRownan];
    macierzX = new double [liczbaRownan];

    for(int i = 0; i < liczbaRownan; i++)
    {
        A[i] = new double [liczbaRownan];
        M[i] = new double [liczbaRownan];
    }
}

void wyborWarunkuZakonczeniaAlgorytmu () {

    cout<<endl<<"Podaj warunek zakonczenia wykonywania algorytmu: "<<endl;
    cout<<"[1] Dokladnosc"<<endl;
    cout<<"[2] Liczba iteracji"<<endl;
    int wyborWarunkuStopu;
    cin>>wyborWarunkuStopu;
    if(wyborWarunkuStopu == 1) {
        czyDokladnosc = true;
        cout<<endl<<"Podaj dokladnosc: ";
        cin>>dokladnosc;
    } else if(wyborWarunkuStopu == 2) {
        cout<<"Podaj liczbe iteracji: ";
        cin>>liczbaIteracji;
    }
}

void pobierzDaneZPlikuDoMacierzyAOrazB () {

    ifstream plik;
    plik.open("wspolczynnikiDoMacierzy.txt");

    if(plik.good()) {
        for(int i = 0; i<liczbaRownan; i++) {

            for(int j = 0; j<liczbaRownan; j++) {
                plik>>A[i][j];
            }

            plik>>b[i];
        }
        plik.close();
    } else {
        cout<<"Nie mozna otworzyc pliku!";
    }
}

bool czyMacierzAZbieznaDlaWierszy()
{
    for(int i = 0; i < liczbaRownan; i++)
    {
        double sumaDlaWiersza = 0;
        for(int j = 0; j < liczbaRownan; j++)
        {
            if(i!=j)
                sumaDlaWiersza += abs(A[i][j]) / abs(A[i][i]);
        }
        if(sumaDlaWiersza >= 1)
            return false;
    }
    return true;
}

bool czyMacierzAZbieznaDlaKolumn()
{
    for(int j = 0; j < liczbaRownan; j++)
    {
        double sumaDlaKolumny = 0;
        for(int i = 0; i < liczbaRownan; i++)
        {
            if(j!=i)
                sumaDlaKolumny += abs(A[i][j]) / abs(A[j][j]);
        }
        if (sumaDlaKolumny >= 1)
            return false;
    }
    return true;
}

bool czyMacierzAZbieznaPierwiastek()
{
    double suma = 0;
    for(int i = 0; i < liczbaRownan; i++)
    {
        for(int j = 0; j < liczbaRownan; j++)
        {
            if(i!=j)
            {
                double c =  (abs(A[i][j]) / abs(A[j][j]));
                suma += c*c;
            }
        }
    }
    return sqrt(suma) < 1;
}
bool czyMacierzAZbieznaWiersze () {

    double* macierzPomocnicza = new double [liczbaRownan];
    double* macierzDiagonalna = new double [liczbaRownan];
    for(int i = 0; i < liczbaRownan; i++) {
        for(int j = 0; j < liczbaRownan; j++) {
            if(i!=j)
                macierzPomocnicza[i] += abs(A[i][j]);
            else
                macierzDiagonalna[i] = abs(A[i][j]);
        }
    }

    for (int i = 0; i < liczbaRownan; i++) {
        if(macierzDiagonalna[i] < macierzPomocnicza[i])
            return false;
    }
    return true;
}

bool czyMacierzAZbieznaKolumny () {

    double* macierzPomocnicza = new double [liczbaRownan];
    double* macierzDiagonalna = new double [liczbaRownan];
    for(int j = 0; j < liczbaRownan; j++) {
        for(int i = 0; i < liczbaRownan; i++) {
            if(j!=i)
                macierzPomocnicza[j] += abs(A[i][j]);
            else
                macierzDiagonalna[j] = abs(A[i][j]);
        }
    }

    for (int i = 0; i < liczbaRownan; i++) {
        if(macierzDiagonalna[i] < macierzPomocnicza[i])
            return false;
    }
    return true;
}
double* wyliczWartosciMacierzyN () {

    double* macierzN = new double [liczbaRownan];
    for(int i = 0; i < liczbaRownan; i++)
    {
        //N[i] = D[i]^-1 gdzie D to macierz diagonalna (wartosci z glownej przekatnej macierzy A)
        macierzN[i] = (1/A[i][i]);
    }
    return macierzN;
}

double** wyliczWartosciMacierzyM () {
    //  M = -N * (L + U) , gdzie L + U sa to wartosci z macierzy A nad i pod glowna przekatna
    double** macierzM = new double* [liczbaRownan];
    for(int i = 0; i < liczbaRownan; i++)
    {
        macierzM[i] = new double[liczbaRownan];
    }

    for (int i = 0; i < liczbaRownan; i++)
    {
        for (int j = 0; j < liczbaRownan; j++)
        {
            double wartosc;
            if (i == j)
                wartosc = 0;           //dlatego, ze w powyzszym wzorze mamy L + U wiec wartosci na glownej przekatnej maja wynosic 0
            else
                wartosc = - (N[i] * A[i][j]);
            macierzM[i][j] = wartosc;
        }
    }
    return macierzM;
}

void wyliczWartosciMacierzyWynikowej() {

    if (czyDokladnosc)
        liczWgDokladnosci();
    else
        liczWgLiczbyIteracji();
}

void metodaJacobiego() {

    for (int i=0; i < liczbaRownan; i++)
    {
        macierzX[i] = N[i]*b[i];
        for(int j = 0; j < liczbaRownan; j++)
        {
            macierzX[i] += M[i][j]*poprzedniaMacierzX[j];
        }
    }
}
void liczWgDokladnosci () {

    int liczbaPrzeprowadzonychIteracji = 1;
    metodaJacobiego();

    do {
            for (int i=0; i<liczbaRownan; i++)
            {
                poprzedniaMacierzX[i] = macierzX[i];
            }
            metodaJacobiego();
            liczbaPrzeprowadzonychIteracji++;

    } while (!czySpelnionaDokladnosc(poprzedniaMacierzX, macierzX));

    cout<<"Przeprowadzonych iteracji: "<<liczbaPrzeprowadzonychIteracji<<endl;
}

bool czySpelnionaDokladnosc (double* poprzedniaMacierzX, double* macierzX) {

    for(int i = 0; i < liczbaRownan; i++) {
        if(abs (poprzedniaMacierzX[i] - macierzX[i]) > dokladnosc) {
            cout<<abs(poprzedniaMacierzX[i] - macierzX[i])<<endl;
            return false;
        }
    }
    return true;
}
void liczWgLiczbyIteracji () {

    for (int i=0; i<liczbaIteracji; i++) {
        metodaJacobiego();
        for (int i=0; i<liczbaRownan; i++)
            poprzedniaMacierzX[i] = macierzX[i];
    }
}
void wyswietlMacierze() {

    cout<<endl<<"MACIERZ A: "<<endl<<endl;
    wyswietlMacierzDwuwymiarowa(A);
    cout<<endl<<"MACIERZ B: "<<endl<<endl;
    wyswietlMacierz(b);
    cout<<endl<<"MACIERZ N: "<<endl<<endl;
    wyswietlMacierz(N);
    cout<<endl<<"MACIERZ M: "<<endl<<endl;
    wyswietlMacierzDwuwymiarowa(M);
    cout<<endl<<"Wynik: "<<endl<<endl;
    czyMacierzWynikowa = true;
    wyswietlMacierz(macierzX);
}

void wyswietlMacierzDwuwymiarowa (double** macierz) {

    for(int i=0; i < liczbaRownan; i++) {
        for(int j = 0; j < liczbaRownan; j++)
            cout<<setw(8)<<macierz[i][j]<<" ";

        cout<<endl;
    }
}

void wyswietlMacierz (double* macierz) {

    for(int i=0; i<liczbaRownan; i++){
        if(czyMacierzWynikowa)
            cout<<"x"<<i+1<<" = ";
        cout<<setprecision(5)<<setw(8)<<macierz[i]<<endl;
    }
}
