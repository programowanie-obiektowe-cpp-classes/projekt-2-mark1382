#include "Czytelnik.h"

std::string Czytelnik::getNazwisko() const { return nazwisko; }

int Czytelnik::getID() const { return nr_id; }

double Czytelnik::GetSumaKar() const { return suma_kar; }

std::list<std::shared_ptr<ZasobyBiblioteczne>>& Czytelnik::getLista()  { return lista_wypozyczen; }

void Czytelnik::wypozyczenie(std::shared_ptr<ZasobyBiblioteczne> zasob, std::chrono::system_clock::time_point data_zwrotu, Biblioteka& biblioteka)
{
    if (!zasob) {
        std::cout << "Przekazano pusty wskaŸnik." << std::endl;
        return;
    }

    zasob->setDataOddania(data_zwrotu);
    lista_wypozyczen.emplace_back(zasob);

    biblioteka.usunZasob(zasob);
}

void Czytelnik::zwrot(std::shared_ptr<ZasobyBiblioteczne> zasob, Biblioteka& biblioteka, std::chrono::system_clock::time_point data_zwrotu)
{
    if (!zasob) {
        std::cout << "Przekazano pusty wskaŸnik." << std::endl;
        return;
    }

    auto diff = data_zwrotu - zasob->getDataOddania();
    auto diff_days = std::chrono::duration_cast<std::chrono::seconds>(diff).count() / 86400;

    if (diff_days > 0) {
        std::cout << "Kara za opóŸnienie: " << diff_days << " dni" << std::endl;
        suma_kar += zasob->getKara() * diff_days;
    }

    auto it = std::find_if(lista_wypozyczen.begin(), lista_wypozyczen.end(),
        [&](const std::shared_ptr<ZasobyBiblioteczne>& z) { return z == zasob; });

    if (it != lista_wypozyczen.end()) {
        lista_wypozyczen.erase(it);
        zasob->setDataOddania(std::chrono::system_clock::time_point::min());
        biblioteka.dodajZasob(zasob);
    }
}
