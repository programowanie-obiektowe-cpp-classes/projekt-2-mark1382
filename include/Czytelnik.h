#pragma once
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <chrono>
#include "ZasobyBiblioteczne.h"
#include "baza_zasobow_biblio.h"

class Biblioteka;  // Forward declaration

class Czytelnik
{
private:
    std::string nazwisko;
    const int nr_id;
    double suma_kar;
    std::list<std::shared_ptr<ZasobyBiblioteczne>> lista_wypozyczen;

public:
    std::string getNazwisko() const;
    int getID() const;
    double GetSumaKar() const;
    std::list<std::shared_ptr<ZasobyBiblioteczne>>& getLista();

    Czytelnik(std::string nazwisko_, int nr_id_)
        : nazwisko{ nazwisko_ }, nr_id{ nr_id_ }, suma_kar{ 0.0 } {}

    Czytelnik() : nazwisko{ "Jan Kowalski" }, nr_id{ 1 }, suma_kar{ 0.0 } {}

    ~Czytelnik() {}

    void wypozyczenie(std::shared_ptr<ZasobyBiblioteczne> zasob, std::chrono::system_clock::time_point data_zwrotu, Biblioteka& biblioteka);
    void zwrot(std::shared_ptr<ZasobyBiblioteczne> zasob, Biblioteka& biblioteka, std::chrono::system_clock::time_point data_zwrotu);
};
