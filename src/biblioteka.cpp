#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <optional>
#include "Czytelnik.h"
#include "ZasobyBiblioteczne.h"
#include "baza_zasobow_biblio.h"



//Szablon funkcji do wyszukiwania zasobów w wektorze
//Szukamy danego typu zasobu
//Szukać można po tytule i ewentualnie jednym dodatkowym parametrze

template <typename T>
void sprawdzDostep(const std::vector<std::shared_ptr<T>>& zasoby, const std::string& tytul, const std::string& dodatkowyParametr = "") {
    bool znaleziono = false;

    std::cout << "Wyniki wyszukiwania dla tytulu: \"" << tytul << "\"";
    if (!dodatkowyParametr.empty()) std::cout << " i parametru: \"" << dodatkowyParametr << "\"";
    std::cout << ":\n";

    for (const auto& zasob : zasoby) {
        if (zasob->getTytul() == tytul) {
            // Jeśli dodatkowyParametr jest pusty, szukamy tylko po tytule
            if (dodatkowyParametr.empty()) {
                std::cout << "- " << zasob->getTytul();

                // Jeśli to książka lub leksykon, wyświetlamy również autora  i wydawnictwo
                if (auto* ksiazka = dynamic_cast<Ksiazka*>(zasob.get())) {
                    std::cout << " (Autor: " << ksiazka->getAutor() << ")" << std::endl;
                    std::cout << " (Wydawnictwo: " << ksiazka->getWydawnictwo() << ")" << std::endl;
                }
                // Jeśli to czasopismo to wyslwietlamy nr wydania
                else if (auto* czasopismo = dynamic_cast<Czasopismo*>(zasob.get())) {
                    std::cout << " (Nr wydania: " << czasopismo->getNumerWydania() <<")";
                }
                else if (auto* leksykon = dynamic_cast<Leksykon*>(zasob.get())) {
                    std::cout << " (Autor: " << leksykon->getAutor() << ")" << std::endl;
                    std::cout << " (Wydawnictwo: " << leksykon->getWydawnictwo() << ")" << std::endl;
                }
                std::cout << "\n";
                znaleziono = true;
            }
            // Jeśli dodatkowyParametr nie jest pusty (np. autor książki), sprawdzamy dla książek
            else if (auto* ksiazka = dynamic_cast<Ksiazka*>(zasob.get())) {
                if (ksiazka->getAutor() == dodatkowyParametr) {
                    std::cout << "- " << zasob->getTytul() << " (Autor: " << ksiazka->getAutor() << ")\n";
                    znaleziono = true;
                }
            }
            else if (auto* czasopismo = dynamic_cast<Czasopismo*>(zasob.get())) {
                if (czasopismo->getWydawnictwo() == dodatkowyParametr) {
                    std::cout << "- " << zasob->getTytul() << " (Wydawnictwo: " << czasopismo->getWydawnictwo() << ")\n";
                    znaleziono = true;
                }
            }
            else if (auto* leksykon = dynamic_cast<Leksykon*>(zasob.get())) {
                if (leksykon->getAutor() == dodatkowyParametr) {
                    std::cout << "- " << zasob->getTytul() << " (Autor: " << leksykon->getAutor() << ")\n";
                    znaleziono = true;
                }
            }
        }
    }

    if (!znaleziono) {
        std::cout << "Brak wynikow spelniajacych podane kryteria.\n";
    }
}


//Przeciążenie operatora >> dla typu czaowego
std::istream& operator>>(std::istream& is, std::chrono::system_clock::time_point& tp) {
    std::tm tm = {};

    // Wczytanie formatu: YYYY-MM-DD HH:MM:SS
    if (is >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S")) {
        tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }
    else {
        is.setstate(std::ios::failbit);  // Jeśli parsowanie się nie powiedzie, ustaw błąd
    }

    return is;
}

//Inicjalizajca zmiennej statycznej - kara
const double ZasobyBiblioteczne::kara = 1.5;

//Wektor do przetrzymywnaia czytelnikow
std::vector<Czytelnik> vec_czytelnicy;


int main()
{
    Biblioteka biblioteka;

    // INTERFEJS UŻYTKOWNIKA//

//Zmienne do menu

    int opcja_menu_gl;
    int opcja_zasob;
    int opcja_zasob_2;
    int opcja_akcja_czyt;
    std::string tytul_k;
    std::string tytul_cz;
    std::string tytul_lek;
    std::string tytul_zas;
    std::string autor_k;
    std::string autor_lek;
    std::string wydaw_zas;
    std::string wydawnictwo_k;
    int rok_wyd_k;
    std::string wydawnictwo_cz;
    std::string wydawnictwo_lek;
    int rok_wyd_lek;
    int rok_wyd_zas;
    int nr_wydania_cz;
    std::string nazwisko_czytelnik;
    int ID_czytlenik;
    std::chrono::system_clock::time_point data_odd;







    // ---------------------------MENU---------------------------------//
   
    while (true) {
        std::cout << "MENU biblioteki: " << std::endl << "Opcje:" << std::endl << "1. Utworz czytelnika." << std::endl
            << "2. Sprawdz dostep." << std::endl << "3. Wybierz czytelnika." << std::endl << "4. Wyjdz" << std::endl;
        std::cin >> opcja_menu_gl;
        std::cin.ignore();
        switch (opcja_menu_gl) {
        case 1:
            // Tworzenie czytelnika
            std::cout << "Podaj nazwisko nowego czytelnika: " << std::endl;
            std::cin >> nazwisko_czytelnik;
            std::cout << "Podaj ID czytelnika" << std::endl;
            std::cin >> ID_czytlenik;
            vec_czytelnicy.emplace_back(nazwisko_czytelnik, ID_czytlenik);
            break;

        case 2:
            // Sprawdzanie dostępności zasobów
            std::cout << "Podaj typ zasobu: " << std::endl << "Opcje:" << std::endl << "1. Ksiazka" << std::endl
                << "2. Czasopismo" << std::endl << "3. Leksykon" << std::endl;
            std::cin >> opcja_zasob;
            std::cin.ignore();
            switch (opcja_zasob) {
            case 1: // Ksiazka
                std::cout << "Podaj tytul: " << std::endl;
                std::getline(std::cin, tytul_k);
                std::cout << "Podaj autora: " << std::endl;
                std::getline(std::cin, autor_k);
                sprawdzDostep(biblioteka.getKsiazki(), tytul_k, autor_k);
                break;
            case 2: // Czasopismo
                std::cout << "Podaj tytul: " << std::endl;
                std::getline(std::cin, tytul_cz);
                std::cout << "Podaj nr wydania: " << std::endl;
                std::cin >> nr_wydania_cz;
                std::cin.ignore();
                sprawdzDostep(biblioteka.getCzasopisma(), tytul_cz);
                break;
            case 3: // Leksykon
                std::cout << "Podaj tytul: " << std::endl;
                std::getline(std::cin, tytul_lek);
                std::cout << "Podaj autora: " << std::endl;
                std::getline(std::cin, autor_lek);
                sprawdzDostep(biblioteka.getLeksykony(), tytul_lek);
                break;
            }
            break;

        case 3:
            // Wybór czytelnika
            std::cout << "Podaj id czytelnika: " << std::endl;
            std::cin >> ID_czytlenik;
            std::cin.ignore();
            for (auto it = vec_czytelnicy.begin(); it != vec_czytelnicy.end(); ++it) {
                if (ID_czytlenik == it->getID()) {
                    std::cout << "Wypozyczenia i zwroty." << std::endl << "1. Wypozycz." << std::endl << "2. Zwroc" << std::endl
                        << "3. Sprawdz zadluzenie" << std::endl;
                    std::cin >> opcja_akcja_czyt;
                    std::cin.ignore();
                    switch (opcja_akcja_czyt) {
                    case 1: // Wypozyczenie zasobu
                        std::cout << "Typ zasobu do wypozyczenia: " << std::endl << "1. Ksiazka." << std::endl
                            << "2. Czasopismo" << std::endl << "3. Leksykon" << std::endl;
                        std::cin >> opcja_zasob_2;
                        std::cin.ignore();
                        switch (opcja_zasob_2) {
                        case 1: // Ksiazka
                            std::cout << "Tytul: " << std::endl;
                            std::getline(std::cin, tytul_k);
                            std::cout << "Autor: " << std::endl;
                            std::getline(std::cin, autor_k);
                            std::cout << "Wydawnictwo: " << std::endl;
                            std::getline(std::cin, wydawnictwo_k);
                            std::cout << "Rok wydania: " << std::endl;
                            std::cin >> rok_wyd_k;
                            std::cin.ignore();
                            std::cout << "Data oddania (YYYY-MM-DD HH:MM:SS): " << std::endl;
                            std::cin >> data_odd;
                            std::cin.ignore();
                            for (auto iter = biblioteka.getKsiazki().begin(); iter != biblioteka.getKsiazki().end(); ++iter) {
                                std::cout << iter->get()->getTytul() << std::endl;
                                if ((tytul_k == iter->get()->getTytul()) && (autor_k == iter->get()->getAutor()) &&
                                    (wydawnictwo_k == iter->get()->getWydawnictwo()) && (rok_wyd_k == iter->get()->getDataWydania())) {
                                    it->wypozyczenie(*iter, data_odd, biblioteka);
                                    break;
                                }
                            }
                            std::cout << "Wyjscie z wpozyczenia ksiazki" << std::endl;
                            break;

                        case 2: // Czasopismo
                            std::cout << "Tytul: ";
                            std::getline(std::cin, tytul_cz);
                            std::cout << "Nr wydania: ";
                            std::cin >> nr_wydania_cz;
                            std::cin.ignore();
                            std::cout << "Data oddania (YYYY-MM-DD HH:MM:SS): ";
                            std::cin >> data_odd;
                            std::cin.ignore();


                            for (auto iter1 = biblioteka.getCzasopisma().begin(); iter1 != biblioteka.getCzasopisma().end(); ++iter1) {
                                if (tytul_cz == iter1->get()->getTytul() && nr_wydania_cz == iter1->get()->getNumerWydania()) {
                                    it->wypozyczenie(*iter1, data_odd, biblioteka);
                                    break;
                                }
                            }
                            break;

                        case 3: // Leksykon
                            std::cout << "Tytul: ";
                            std::getline(std::cin, tytul_lek);
                            std::cout << "Autor: ";
                            std::getline(std::cin, autor_lek);
                            std::cout << "Wydawnictwo: ";
                            std::getline(std::cin, wydawnictwo_lek);
                            std::cout << "Rok wydania: ";
                            std::cin >> rok_wyd_lek;
                            std::cin.ignore();
                            std::cout << "Data oddania (YYYY-MM-DD HH:MM:SS): ";
                            std::cin >> data_odd;
                            std::cin.ignore();

                            for (auto iter2 = biblioteka.getLeksykony().begin(); iter2 != biblioteka.getLeksykony().end(); ++iter2) {
                                if (tytul_lek == iter2->get()->getTytul() && autor_lek == iter2->get()->getAutor() &&
                                    wydawnictwo_lek == iter2->get()->getWydawnictwo() && rok_wyd_lek == iter2->get()->getDataWydania()) {
                                    it->wypozyczenie(*iter2, data_odd, biblioteka);
                                    break;
                                }
                            }
                            break;
                        }
                        std::cout << "Wyjscie ze switcha - akcje czytelnika" << std::endl;
                        break;

                    case 2: // Zwrot zasobu
                        std::cout << "Podaj tytul zasobu do zwrotu: ";
                        std::getline(std::cin, tytul_zas);
                        std::cout << "Podaj wydawnictwo zasobu do zwrotu: ";
                        std::getline(std::cin, wydaw_zas);
                        std::cout << "Podaj rok wydania zasobu do zwrotu: ";
                        std::cin >> rok_wyd_zas;
                        std::cin.ignore();
                        for (auto iter = it->getLista().begin(); iter != it->getLista().end(); ++iter) {
                            if ((tytul_zas == (*iter)->getTytul()) && (wydaw_zas == (*iter)->getWydawnictwo())) {
                                it->zwrot(*iter, biblioteka, std::chrono::system_clock::now());
                                std::cout << "Zasob zwrocony!\n";
                                break;
                            }
                        }
                        break;

                    case 3: // Sprawdz zadluzenie
                        std::cout << "Sumaryczne zadluzenie: " << it->GetSumaKar() << std::endl;
                        break;
                    }
                }
            }
            std::cout << "Wyjscie z wybory czytelnika" << std::endl;
            break;

        case 4:
            std::cout << "Do widzenia!" << std::endl;
            return 0;

        default:
            std::cout << "Nieprawidlowy wybor." << std::endl;
            break;
        }
    }
    
   
}