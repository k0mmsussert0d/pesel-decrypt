#include <iostream>
#include <string>

bool czyLiczby( std::string pesel )
{
    return pesel.find_first_not_of("0123456789") == std::string::npos;
}

bool czyPrawidlowy( int miesiac, int dzien )
{
    if( miesiac % 20 == 0 || miesiac % 20 > 12 )
        return false;

    if( dzien < 1 || dzien > 31 )
        return false;

    return true;
}

bool liczbaKontrolna( int liczby[] )
{
    int prawidlowa = 0;
    int j = 9;

    for( int i = 0; i <= 9; i++ )
    {
        prawidlowa += liczby[ i ] * j;
        j -= 2;
        if( j < 0 )
            j = 9;
        if( j == 5 )
            j-= 2;
    }
    prawidlowa %= 10;

    if( prawidlowa == liczby[ 10 ] )
        return true;
    else
        return false;
}

bool czyMezczyzna( int plec )
{
    if( plec % 2 == 0 )
        return false;
    else
        return true;
}

void wprowadzPesel( std::string & pesel )
{
    std::cout << "Wprowadz numer PESEL: ";
    while( pesel.size() != 11 || !czyLiczby( pesel ) )
    {
        std::cin.clear();
        std::cin.sync();
        std::cin >> pesel;
        if( pesel.size() != 11 )
            std::cout << "Numer PESEL musi miec 11 cyfr" << std::endl;
        if( !czyLiczby )
            std::cout << "Numer PESEL sklada sie tylko i wylacznie z cyfr" << std::endl;
    }
}

int main()
{
    std::string pesel;
    wprowadzPesel( pesel );

    int liczby[ 11 ];

    for( int i = 0; i <= 10; i++ )
        liczby[ i ] = pesel[ i ] - '0';

    int miesiac = liczby[ 2 ] * 10 + liczby[ 3 ];
    int dzien = liczby[ 4 ] * 10 + liczby[ 5 ];

    if( !czyPrawidlowy( miesiac, dzien ) )
    {
        std::cout << "Numer jest nieprawidlowy ze wzgledu na blad w dacie urodzenia (pozycje 3-6)";
        return 0;
    }

    char decyzja = '0';
    if( !liczbaKontrolna( liczby ) )
    {
        std::cout << "Niepoprawna liczba kontrolna. Czy chcesz kontynuowac? (T/N)" << std::endl;

        while( decyzja != 'T' && decyzja != 't' && decyzja != 'N' && decyzja != 'n' )
        {
            std::cin.clear();
            std::cin.sync();
            std::cin >> decyzja;
        }
        if( decyzja == 'n' || decyzja == 'N' )
            return 0;
    }

    int mnoznik = miesiac / 20;
    int stulecie;

    switch( mnoznik )
    {
    case 0:
        {
            stulecie = 19;
            break;
        }
    case 1:
        {
            stulecie = 20;
            break;
        }
    case 2:
        {
            stulecie = 21;
            break;
        }
    case 3:
        {
            stulecie = 22;
            break;
        }
    case 4:
        {
            stulecie = 18;
            break;
        }
    }

    int rok = stulecie * 100 + liczby[ 0 ] * 10 + liczby[ 1 ];
    miesiac -= ( mnoznik * 20 );

    if( miesiac > 9 )
        std::cout << "Data urodzenia (RRRR-MM-DD): " << rok << "-" << miesiac << "-" << dzien << std::endl;
    else if( miesiac <= 9 )
        std::cout << "Data urodzenia (RRRR-MM-DD): " << rok << "-0" << miesiac << "-" << dzien << std::endl;

    std::cout << "Plec: ";
    if( czyMezczyzna( liczby[ 9 ] ) )
        std::cout << "mezczyzna" << std::endl;
    else
        std::cout << "kobieta" << std::endl;

    std::cout << "Numer serii: " << liczby [ 6 ] << liczby[ 7 ] << liczby[ 8 ] << liczby[ 9 ];

    return 0;
}
