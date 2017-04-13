#include <iostream>
#include <string>

bool areDigits( std::string pesel )
{
    return pesel.find_first_not_of("0123456789") == std::string::npos; //only digits allowed, if any other character occurs, return false
}

bool isLeapYear( int year ) //used for determining whether date is ok or not
{
    if( year % 4 == 0 )
    {
        if( year % 100 == 0 )
        {
            if( year % 400 == 0 )
                return true;
            else
                return false;
        }
        else
            return true;
    } else
        return false;
}

bool isDateCorrect( int day, int month, int year )
{
    if( month >= 0 && month <= 12 && day >= 1 ) //initial boolean, month have to belong to <0; 12>, day must not be negative
    {
        switch( month )
        {
        //checks if day is ok for 31-days long months
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            {
                if( day <= 31 )
                {
                    return true;
                    break;
                }
            }
        //checks if day is ok for 30-days long months
        case 4:
        case 6:
        case 9:
        case 11:
            {
                if( day <= 30 )
                    return true;
                    break;
            }
        //checks if day is ok for February
        case 2:
            {
                if( isLeapYear( year ) )
                {
                    if( day <= 29 )
                    {
                        return true;
                        break;
                    }
                }
                else if( !isLeapYear( year ) )
                {
                    if( day <= 28 )
                    {
                        return true;
                        break;
                    }
                }
            }
        }
    }

    return false;
}

bool validityDigit( int digits[] ) //checks the validity digit
{
    int correctDigit = 0; //for real validity digit
    int j = 9;

    for( int i = 0; i <= 9; i++ ) //multiply every digit from array liczby by 9, then 7, then 3, then 1 (loop)
    {
        correctDigit += digits[ i ] * j;
        j -= 2;
        if( j < 0 )
            j = 9;
        if( j == 5 )
            j-= 2;
    }
    correctDigit %= 10; //final value

    if( correctDigit == digits[ 10 ] ) //should be on last position
        return true;
    else
        return false;
}

bool isMale( int sex ) //checks if a holder is male
{
    if( sex % 2 == 0 )
        return false; //is female
    else
        return true; //is male
}

void peselInput( std::string & pesel )
{
    std::cout << "Wprowadz numer PESEL: ";
    while( pesel.size() != 11 || !areDigits( pesel ) ) //pesel must have 11 digits
    {
        std::cin.clear();
        std::cin.sync();
        std::cin >> pesel;
        if( pesel.size() != 11 ) //checks if lenght is 11
            std::cout << "Numer PESEL musi miec 11 cyfr" << std::endl;
        if( !areDigits( pesel ) ) //checks if there are no illegal characters
            std::cout << "Numer PESEL sklada sie tylko i wylacznie z cyfr" << std::endl;
    }
}

int main()
{
    std::string pesel;
    peselInput( pesel );

    int digits[ 11 ];

    for( int i = 0; i <= 10; i++ ) //converts chars from pesel string into int liczby array
        digits[ i ] = pesel[ i ] - '0';

    int month = digits[ 2 ] * 10 + digits[ 3 ]; //extracts month, encoded
    int day = digits[ 4 ] * 10 + digits[ 5 ]; //extracts day, not-encoded

    int multiplier = month / 20; //calculates multiplier
    int century; //is century (-1) of birth

    switch( multiplier )
    {
    case 0:
        {
            century = 19;
            break;
        }
    case 1:
        {
            century = 20;
            break;
        }
    case 2:
        {
            century = 21;
            break;
        }
    case 3:
        {
            century = 22;
            break;
        }
    case 4:
        {
            century = 18;
            break;
        }
    }

    int year = century * 100 + digits[ 0 ] * 10 + digits[ 1 ]; //a year in YYYY format

    if( !isDateCorrect( day, month, year ) )
    {
        std::cout << "Numer jest nieprawidlowy ze wzgledu na blad w dacie urodzenia (pozycje 3-6)";
        return 0;
    }

    char resolve = '0'; //default value, allows to continue
    if( !validityDigit( digits ) ) //checks control digit
    {
        /*due to some deficiencies, old PESEL numbers assigned in 80's may have incorrect control digit,
          this fault was detected in 90's while migrating the system to the newer environment,
          due to large number of wrong numbers, incorrect numbers were left unchanged,
          for detailed information about the reasons of this issue, please refer to wiki page on github,
          the purpose of this code is to inform a user about potential issue with his number, ask him to make sure if it's correct,
          then ask if he wants to continue with wrong number or terminate the process*/

        std::cout << "Niepoprawna liczba kontrolna. Czy chcesz kontynuowac? (T/N)" << std::endl;

        while( resolve != 'T' && resolve != 't' && resolve != 'N' && resolve != 'n' ) //user's input must be yes or not
        {
            std::cin.clear();
            std::cin.sync();
            std::cin >> resolve;
        }
        if( resolve == 'n' || resolve == 'N' )
            return 0; //terminates the program
    }

    month -= ( multiplier * 20 ); //calculates month, decoded

    if( month > 9 )
        std::cout << "Data urodzenia (RRRR-MM-DD): " << year << "-" << month << "-" << day << std::endl;
    else if( month <= 9 ) //adds 0 before month, if it's one digit
        std::cout << "Data urodzenia (RRRR-MM-DD): " << year << "-0" << month << "-" << day << std::endl;

    std::cout << "Plec: "; //gender
    if( isMale( digits[ 9 ] ) )
        std::cout << "mezczyzna" << std::endl; //male
    else
        std::cout << "kobieta" << std::endl; //female

    std::cout << "Numer serii: " << digits[ 6 ] << digits[ 7 ] << digits[ 8 ] << digits[ 9 ]; //serial number

    return 0;
}
