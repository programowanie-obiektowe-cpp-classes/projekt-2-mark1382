#include "baza_zasobow_biblio.h"


Biblioteka::Biblioteka()
{
  
    // Inicjalizacja ksi¹¿ek
    ksiazki = {
        std::make_shared<Ksiazka>("Pan Tadeusz", "Mickiewicz", "PWN", 1834),
        std::make_shared<Ksiazka>("Lalka", "Prus", "PWN", 1890),
        std::make_shared<Ksiazka>("Krzy¿acy", "Sienkiewicz", "PWN", 1900),
        std::make_shared<Ksiazka>("Dziady", "Mickiewicz", "Ossolineum", 1823),
        std::make_shared<Ksiazka>("Potop", "Sienkiewicz", "PWN", 1886),
        std::make_shared<Ksiazka>("Quo Vadis", "Sienkiewicz", "PWN", 1896),
        std::make_shared<Ksiazka>("Ch³opi", "Reymont", "Czytelnik", 1904),
        std::make_shared<Ksiazka>("Ferdydurke", "Gombrowicz", "WL", 1937),
        std::make_shared<Ksiazka>("Solaris", "Lem", "Cybernetyka", 1961),
        std::make_shared<Ksiazka>("Inny œwiat", "Herling-Grudziñski", "PWN", 1951),
        std::make_shared<Ksiazka>("Zbrodnia i kara", "Dostojewski", "WL", 1866),
        std::make_shared<Ksiazka>("Mistrz i Ma³gorzata", "Bu³hakow", "WL", 1967),
        std::make_shared<Ksiazka>("Ojciec Goriot", "Balzac", "PWN", 1835),
        std::make_shared<Ksiazka>("W³adca Pierœcieni", "Tolkien", "Amber", 1954),
        std::make_shared<Ksiazka>("Hobbit", "Tolkien", "Amber", 1937),
        std::make_shared<Ksiazka>("Harry Potter i Kamieñ Filozoficzny", "Rowling", "Media Rodzina", 1997),
        std::make_shared<Ksiazka>("Gra o tron", "Martin", "Zysk i S-ka", 1996),
        std::make_shared<Ksiazka>("Sherlock Holmes", "Doyle", "PWN", 1887),
        std::make_shared<Ksiazka>("Duma i uprzedzenie", "Austen", "PWN", 1813),
        std::make_shared<Ksiazka>("1984", "Orwell", "PWN", 1949)
    };

    // Inicjalizacja czasopism
    czasopisma = {
        std::make_shared<Czasopismo>("National Geographic", "NG Media", 2023, 5),
        std::make_shared<Czasopismo>("Nature", "Springer", 2024, 2),
        std::make_shared<Czasopismo>("Science", "AAAS", 2024, 1),
        std::make_shared<Czasopismo>("Focus", "Ringier Axel Springer", 2023, 3),
        std::make_shared<Czasopismo>("Polityka", "Polityka Sp. z o.o.", 2023, 12),
        std::make_shared<Czasopismo>("Forbes", "Forbes Media", 2024, 13),
        std::make_shared<Czasopismo>("Time", "Time Inc.", 2024, 1),
        std::make_shared<Czasopismo>("Newsweek", "Axel Springer", 2024, 2),
        std::make_shared<Czasopismo>("Scientific American", "Springer", 2023, 56),
        std::make_shared<Czasopismo>("Œwiat Nauki", "PWN", 2024, 33),
        std::make_shared<Czasopismo>("Wprost", "AWR Wprost", 2023, 44),
        std::make_shared<Czasopismo>("Gazeta Wyborcza", "Agora", 2024, 12),
        std::make_shared<Czasopismo>("The Economist", "The Economist Group", 2024, 11),
        std::make_shared<Czasopismo>("Rzeczpospolita", "Gremi Media", 2024, 19),
        std::make_shared<Czasopismo>("Dziennik Gazeta Prawna", "Infor PL", 2023, 24),
        std::make_shared<Czasopismo>("National Review", "NR Inc.", 2024, 23),
        std::make_shared<Czasopismo>("The Atlantic", "Emerson Collective", 2023, 14),
        std::make_shared<Czasopismo>("MIT Technology Review", "MIT", 2024, 25),
        std::make_shared<Czasopismo>("Harvard Business Review", "Harvard University", 2024, 26),
        std::make_shared<Czasopismo>("New Scientist", "Reed Business", 2023, 48)
    };

    // Inicjalizacja leksykonów
    leksykony = {
        std::make_shared<Leksykon>("Leksykon Informatyki", "Nowak", "Helion", 2021),
        std::make_shared<Leksykon>("Encyklopedia Biologii", "Kowalski", "PWN", 2018),
        std::make_shared<Leksykon>("S³ownik Jêzyka Polskiego", "Doroszewski", "PWN", 1958),
        std::make_shared<Leksykon>("Leksykon Literatury", "Szymborska", "WL", 2000),
        std::make_shared<Leksykon>("Historia Œwiata", "Gates", "HarperCollins", 2019),
        std::make_shared<Leksykon>("Astronomia dla ka¿dego", "Hawking", "Springer", 2022),
        std::make_shared<Leksykon>("Chemia w pytaniach i odpowiedziach", "Curie", "PWN", 2015),
        std::make_shared<Leksykon>("Fizyka kwantowa", "Einstein", "Helion", 2017),
        std::make_shared<Leksykon>("Leksykon psychologii", "Freud", "PWN", 2016),
        std::make_shared<Leksykon>("Geografia Œwiata", "Kapuœciñski", "PWN", 2020),
        std::make_shared<Leksykon>("Ekonomia dla ka¿dego", "Smith", "Harvard Press", 2023),
        std::make_shared<Leksykon>("Prawo w pigu³ce", "Dworkin", "PWN", 2021),
        std::make_shared<Leksykon>("Historia Polski", "Jasienica", "WL", 2005),
        std::make_shared<Leksykon>("Leksykon Mitologii", "Graves", "PWN", 1998),
        std::make_shared<Leksykon>("Sztuka i estetyka", "Kant", "Helion", 2023),
        std::make_shared<Leksykon>("Filozofia XXI wieku", "Nietzsche", "WL", 2022),
        std::make_shared<Leksykon>("Antropologia Kulturowa", "Malinowski", "PWN", 2014),
        std::make_shared<Leksykon>("S³ownik Synonimów", "Bralczyk", "PWN", 2021),
        std::make_shared<Leksykon>("Leksykon Medycyny", "House", "Springer", 2019),
        std::make_shared<Leksykon>("Neurobiologia", "Kandel", "Harvard Press", 2020)
    };

    // Sortujemy zasoby po inicjalizacji
    sortujZasoby();

}
