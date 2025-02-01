#include "ZasobyBiblioteczne.h"

ZasobyBiblioteczne::ZasobyBiblioteczne(std::string tytul_, std::string wydawnictwo_, const int dat_wyd) : tytul{ tytul_ }, wydawnictwo{ wydawnictwo_ }, data_wydania{ dat_wyd }, data_oddania{ std::chrono::system_clock::now() } {}

std::string ZasobyBiblioteczne::getTytul() const
{
	return tytul;
}

std::string ZasobyBiblioteczne::getWydawnictwo() const
{
	return wydawnictwo;
}

int ZasobyBiblioteczne::getDataWydania() const
{
	return data_wydania;
}

std::chrono::system_clock::time_point ZasobyBiblioteczne::getDataOddania() const
{
	return data_oddania;
}


std::string Ksiazka::getAutor() const
{
	return autor;
}



void Ksiazka::setDataOddania(std::chrono::system_clock::time_point data_oddania_)
{
	data_oddania = data_oddania_;
}

std::string Leksykon::getAutor() const
{
	return autor;
}

void Leksykon::setDataOddania(std::chrono::system_clock::time_point data_oddania_)
{
	data_oddania = data_oddania_;
}


void Czasopismo::setDataOddania(std::chrono::system_clock::time_point data_oddania_)
{
	data_oddania = data_oddania_;
}
