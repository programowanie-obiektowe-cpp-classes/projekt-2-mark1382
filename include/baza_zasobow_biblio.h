#pragma once
#include "ZasobyBiblioteczne.h"
#include <vector>
#include <algorithm>


class Biblioteka {
private:
    std::vector<std::shared_ptr<Ksiazka>> ksiazki;
    std::vector<std::shared_ptr<Czasopismo>> czasopisma;
    std::vector<std::shared_ptr<Leksykon>> leksykony;

public:
    // Dost�p do wektor�w
    std::vector<std::shared_ptr<Ksiazka>>& getKsiazki() { return ksiazki; }
    std::vector<std::shared_ptr<Czasopismo>>& getCzasopisma() { return czasopisma; }
    std::vector<std::shared_ptr<Leksykon>>& getLeksykony() { return leksykony; }

    //Konstruktor:
    Biblioteka();
    //Destruktor
    ~Biblioteka() {};

    // Metoda do sortowania zasob�w
    void sortujZasoby() {
        // Sortowanie ksi��ek po nazwisku autora
        std::sort(ksiazki.begin(), ksiazki.end(), [](const auto& a, const auto& b) {
            return a->getAutor() < b->getAutor();
            });

        // Sortowanie czasopism po tytule
        std::sort(czasopisma.begin(), czasopisma.end(), [](const auto& a, const auto& b) {
            return a->getTytul() < b->getTytul();
            });

        // Sortowanie leksykon�w po tytule
        std::sort(leksykony.begin(), leksykony.end(), [](const auto& a, const auto& b) {
            return a->getTytul() < b->getTytul();
            });
    }

    // Usuwanie zasobu
    void usunZasob(std::shared_ptr<ZasobyBiblioteczne> zasob) {
        if (!zasob) {
            std::cout << "Niepoprawny zas�b (nullptr)." << std::endl;
            return;
        }

        if (auto ksiazka = std::dynamic_pointer_cast<Ksiazka>(zasob)) {
            // Szukamy ksi��ki w wektorze ksi��ek
            auto it = std::find_if(ksiazki.begin(), ksiazki.end(),
                [&zasob](const std::shared_ptr<Ksiazka>& elem) {
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Por�wnanie zawarto�ci
                });
            if (it != ksiazki.end()) {
                ksiazki.erase(it);  // Usuwamy element
                std::cout << "Zasob usuniety (Ksiazka)." << std::endl;
            }
            else {
                std::cout << "Zasob (Ksiazka) nie znaleziony." << std::endl;
            }
        }
        else if (auto czasopismo = std::dynamic_pointer_cast<Czasopismo>(zasob)) {
            // Szukamy czasopisma
            auto it = std::find_if(czasopisma.begin(), czasopisma.end(),
                [&zasob](const std::shared_ptr<Czasopismo>& elem) {
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Por�wnanie zawarto�ci
                });
            if (it != czasopisma.end()) {
                czasopisma.erase(it);  // Usuwamy element
                std::cout << "Zas�b usuni�ty (Czasopismo)." << std::endl;
            }
            else {
                std::cout << "Zas�b (Czasopismo) nie znaleziony." << std::endl;
            }
        }
        else if (auto leksykon = std::dynamic_pointer_cast<Leksykon>(zasob)) {
            // Szukamy leksykonu
            auto it = std::find_if(leksykony.begin(), leksykony.end(),
                [&zasob](const std::shared_ptr<Leksykon>& elem) {
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Por�wnanie zawarto�ci
                });
            if (it != leksykony.end()) {
                leksykony.erase(it);  // Usuwamy element
                std::cout << "Zas�b usuni�ty (Leksykon)." << std::endl;
            }
            else {
                std::cout << "Zas�b (Leksykon) nie znaleziony." << std::endl;
            }
        }
        else {
            std::cout << "Nieznany typ zasobu." << std::endl;
        }
    }

    // Dodawanie zasob�w
    void dodajZasob(std::shared_ptr<ZasobyBiblioteczne> zasob) {
        if (auto ksiazka = std::dynamic_pointer_cast<Ksiazka>(zasob)) {
            ksiazki.emplace_back(ksiazka);
        }
        else if (auto czasopismo = std::dynamic_pointer_cast<Czasopismo>(zasob)) {
            czasopisma.emplace_back(czasopismo);
        }
        else if (auto leksykon = std::dynamic_pointer_cast<Leksykon>(zasob)) {
            leksykony.emplace_back(leksykon);
        }
        else {
            std::cout << "Nieznany typ zasobu!" << std::endl;
        }
        // Po dodaniu nowego zasobu sortujemy wektory
        sortujZasoby();
    }

};
