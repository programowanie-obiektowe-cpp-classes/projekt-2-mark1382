#pragma once
#include <iostream>
#include <string.h>
#include <chrono>

class ZasobyBiblioteczne
{
protected:
	//Uniwersalne pola poszczególnych zasobów bibliotecznych - informacje biblioteczne
	std::string tytul, wydawnictwo;
	const int data_wydania;
    std::chrono::system_clock::time_point data_oddania; //data oddania 
    const static double kara; //zl/dzien przetrzymania

public:
    const double getKara() const { return kara; }
    //Konstruktor:
    ZasobyBiblioteczne(std::string tytul_, std::string wydawnictwo_, const int dat_wyd);
    //Domyœlny destruktor
    virtual ~ZasobyBiblioteczne() = default;
    virtual void setDataOddania(std::chrono::system_clock::time_point data_oddania_) = 0; //czysto abstrakcyjna funkcja do ustawiania daty oddania
    // Uniwersalne gettery dla klasy bazowej
    std::string getTytul() const;
    std::string getWydawnictwo() const;
    int getDataWydania() const;
    std::chrono::system_clock::time_point getDataOddania() const;
};


class Ksiazka : public ZasobyBiblioteczne
{
    std::string autor;
public:
    //Gettery:
    std::string getAutor () const;

    //Setter dla daty oddania:
    void setDataOddania(std::chrono::system_clock::time_point data_oddania_) override;

    //konstruktor:
    Ksiazka(std::string tytul_, std::string autor_, std::string wydawnictwo_, int dat_wyd)
        : ZasobyBiblioteczne(tytul_, wydawnictwo_, dat_wyd), autor(autor_) {}

    //destruktor:
    ~Ksiazka() override = default;
   
};

// Klasa Czasopismo
class Czasopismo : public ZasobyBiblioteczne
{
    int numer_wydania;


public:
    Czasopismo(std::string tytul_, std::string wydawnictwo_, int dat_wyd, int numer_wydania_)
        : ZasobyBiblioteczne(tytul_, wydawnictwo_, dat_wyd), numer_wydania(numer_wydania_) {}

    ~Czasopismo() override = default;

    // Getter dla numeru wydania
    int getNumerWydania() const { return numer_wydania; }

    // Setter dla daty oddania
    void setDataOddania(std::chrono::system_clock::time_point data_oddania_) override;

};

// Klasa Leksykon
class Leksykon : public ZasobyBiblioteczne
{
    std::string autor;


public:
    Leksykon(std::string tytul_, std::string autor_, std::string wydawnictwo_, int dat_wyd)
        : ZasobyBiblioteczne(tytul_, wydawnictwo_, dat_wyd), autor(autor_) {}

    ~Leksykon() override = default;

    // Getter dla tematu
    std::string getTemat() const { return autor; }
    std::string getAutor() const;
    // Setter dla daty oddania
    void setDataOddania(std::chrono::system_clock::time_point data_oddania_) override;
};


