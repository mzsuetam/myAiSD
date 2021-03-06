#ifndef TABLES_H
#define TABLES_H

// INSERT RANDOM
// wypełnia wskazaną tablicę o długości n losowymi wartościami typu double
// (1 miesce po przecinku) z zakresu -range/2 do range/2 
void insertRandom(int table[], int n, int range, bool only_natural=false);
void insertRandom(double table[], int n, int range, bool only_natural=false);

// PRINT TABLE
// wypisuje zawartość danej tabeli o długości n na ekranie,
// jeżeli parametr print jest równy true
void printTable(int table[], int n, bool print);
void printTable(double table[], int n, bool print);

// CHECK TABLE
// sprawdza posortowanie tablicy (niemalejąco)
// i wypisuje wynik sprawdzenia
void checkTable(int table[], int n);
void checkTable(double table[], int n);

#endif