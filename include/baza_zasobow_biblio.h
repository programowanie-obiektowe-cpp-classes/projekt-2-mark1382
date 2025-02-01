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
    // Dostêp do wektorów
    std::vector<std::shared_ptr<Ksiazka>>& getKsiazki() { return ksiazki; }
    std::vector<std::shared_ptr<Czasopismo>>& getCzasopisma() { return czasopisma; }
    std::vector<std::shared_ptr<Leksykon>>& getLeksykony() { return leksykony; }

    //Konstruktor:
    Biblioteka();
    //Destruktor
    ~Biblioteka() {};

    // Metoda do sortowania zasobów
    void sortujZasoby() {
        // Sortowanie ksi¹¿ek po nazwisku autora
        std::sort(ksiazki.begin(), ksiazki.end(), [](const auto& a, const auto& b) {
            return a->getAutor() < b->getAutor();
            });

        // Sortowanie czasopism po tytule
        std::sort(czasopisma.begin(), czasopisma.end(), [](const auto& a, const auto& b) {
            return a->getTytul() < b->getTytul();
            });

        // Sortowanie leksykonów po tytule
        std::sort(leksykony.begin(), leksykony.end(), [](const auto& a, const auto& b) {
            return a->getTytul() < b->getTytul();
            });
    }

    // Usuwanie zasobu
    void usunZasob(std::shared_ptr<ZasobyBiblioteczne> zasob) {
        if (!zasob) {
            std::cout << "Niepoprawny zasób (nullptr)." << std::endl;
            return;
        }

        if (auto ksiazka = std::dynamic_pointer_cast<Ksiazka>(zasob)) {
            // Szukamy ksi¹¿ki w wektorze ksi¹¿ek
            auto it = std::find_if(ksiazki.begin(), ksiazki.end(),
                [&zasob](const std::shared_ptr<Ksiazka>& elem) {
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Porównanie zawartoœci
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
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Porównanie zawartoœci
                });
            if (it != czasopisma.end()) {
                czasopisma.erase(it);  // Usuwamy element
                std::cout << "Zasób usuniêty (Czasopismo)." << std::endl;
            }
            else {
                std::cout << "Zasób (Czasopismo) nie znaleziony." << std::endl;
            }
        }
        else if (auto leksykon = std::dynamic_pointer_cast<Leksykon>(zasob)) {
            // Szukamy leksykonu
            auto it = std::find_if(leksykony.begin(), leksykony.end(),
                [&zasob](const std::shared_ptr<Leksykon>& elem) {
                    return elem->getTytul() == zasob->getTytul() && elem->getWydawnictwo() == zasob->getWydawnictwo();  // Porównanie zawartoœci
                });
            if (it != leksykony.end()) {
                leksykony.erase(it);  // Usuwamy element
                std::cout << "Zasób usuniêty (Leksykon)." << std::endl;
            }
            else {
                std::cout << "Zasób (Leksykon) nie znaleziony." << std::endl;
            }
        }
        else {
            std::cout << "Nieznany typ zasobu." << std::endl;
        }
    }

    // Dodawanie zasobów
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
