#include <iostream>
#include <string>

bool czyLiczby( std::string pesel )
{
    return pesel.find_first_not_of("0123456789") == std::string::npos; //only digits allowed, if any other character occurs, return false
}

bool czyPrawidlowy( int miesiac, int dzien )
{
    if( miesiac % 20 == 0 || miesiac % 20 > 12 ) //checks if decoded month is valid
        return false;

    if( dzien < 1 || dzien > 31 ) //checks if day is valid
        return false;

    return true;
}

bool liczbaKontrolna( int liczby[] ) //checks the validity digit
{
    int prawidlowa = 0; //for real validity digit
    int j = 9;

    for( int i = 0; i <= 9; i++ ) //multiply every digit from array liczby by 9, then 7, then 3, then 1 (loop)
    {
        prawidlowa += liczby[ i ] * j;
        j -= 2;
        if( j < 0 )
            j = 9;
        if( j == 5 )
            j-= 2;
    }
    prawidlowa %= 10; //final value

    if( prawidlowa == liczby[ 10 ] ) //should be on last position
        return true;
    else
        return false;
}

bool czyMezczyzna( int plec ) //checks if a holder is male
{
    if( plec % 2 == 0 )
        return false; //is female
    else
        return true; //is male
}

void wprowadzPesel( std::string & pesel )
{
    std::cout << "Wprowadz numer PESEL: ";
    while( pesel.size() != 11 || !czyLiczby( pesel ) ) //pesel must have 11 digits
    {
        std::cin.clear();
        std::cin.sync();
        std::cin >> pesel;
        if( pesel.size() != 11 ) //checks if lenght is 11
            std::cout << "Numer PESEL musi miec 11 cyfr" << std::endl;
        if( !czyLiczby ) //checks if there are no illegal characters
            std::cout << "Numer PESEL sklada sie tylko i wylacznie z cyfr" << std::endl;
    }
}

int main()
{
    std::string pesel;
    wprowadzPesel( pesel );

    int liczby[ 11 ];

    for( int i = 0; i <= 10; i++ ) //converts chars from pesel string into int liczby array
        liczby[ i ] = pesel[ i ] - '0';

    int miesiac = liczby[ 2 ] * 10 + liczby[ 3 ]; //extracts month, encoded
    int dzien = liczby[ 4 ] * 10 + liczby[ 5 ]; //extracts day, not-encoded

    if( !czyPrawidlowy( miesiac, dzien ) )
    {
        std::cout << "Numer jest nieprawidlowy ze wzgledu na blad w dacie urodzenia (pozycje 3-6)";
        return 0;
    }

    char decyzja = '0'; //default value, allows to continue
    if( !liczbaKontrolna( liczby ) ) //checks control digit
    {
        /*due to some deficiencies, old PESEL numbers assigned in 80's may have incorrect control digit,
          this fault was detected in 90's while migrating the system to the newer environment,
          due to large number of wrong numbers, incorrect numbers were left unchanged,
          for detailed information about the reasons of this issue, please refer to validation_issue.md,
          the purpose of this code is to inform a user about potential issue with his number, ask him to make sure if it's correct,
          then ask if he wants to continue with wrong number or terminate the process*/

        std::cout << "Niepoprawna liczba kontrolna. Czy chcesz kontynuowac? (T/N)" << std::endl;

        while( decyzja != 'T' && decyzja != 't' && decyzja != 'N' && decyzja != 'n' ) //user's input must be yes or not
        {
            std::cin.clear();
            std::cin.sync();
            std::cin >> decyzja;
        }
        if( decyzja == 'n' || decyzja == 'N' )
            return 0; //terminates the program
    }

    int mnoznik = miesiac / 20; //calculates multiplier
    int stulecie; //is century (-1) of birth

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

    int rok = stulecie * 100 + liczby[ 0 ] * 10 + liczby[ 1 ]; //a year in YYYY format
    miesiac -= ( mnoznik * 20 ); //month MM

    if( miesiac > 9 )
        std::cout << "Data urodzenia (RRRR-MM-DD): " << rok << "-" << miesiac << "-" << dzien << std::endl;
    else if( miesiac <= 9 ) //adds 0 before month, if it's one digit
        std::cout << "Data urodzenia (RRRR-MM-DD): " << rok << "-0" << miesiac << "-" << dzien << std::endl;

    std::cout << "Plec: "; //gender
    if( czyMezczyzna( liczby[ 9 ] ) )
        std::cout << "mezczyzna" << std::endl; //male
    else
        std::cout << "kobieta" << std::endl; //female

    std::cout << "Numer serii: " << liczby [ 6 ] << liczby[ 7 ] << liczby[ 8 ] << liczby[ 9 ]; //serial number

    return 0;
}
