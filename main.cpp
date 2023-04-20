/*
Монета має зберігати лише свій номінал, а Копилка - кількість монет кожного номіналу та загальну суму.
Навчіть копілку додавати до себе монети та інші копілки.
Створіть три копілки та масив з сотні (або декількох сотень) монет випадкового номіналу.
Розподіліть ці монети між копілками випадковим чином.
Виведіть на екран інформацію про всі три копілки окремо та загальну суму всіх трьох.
Коли цей функціонал програми запрацює, додайте можливість переміщати монетку обраного номіналу з однієї копілки в іншу.
Також виведіть, в якій з копілок найбільше грошей.
*/

// cd Documents/Колледж/Технологии/Семестр\ 2/currentTask/

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct CustomHashTableElement
{
    int nominalCoinKey = 0;
    int countOfCoinsValue = 0;
    CustomHashTableElement *next = 0;
};

class CustomHashTable
{
    const int maxCountOfNominals = 10;
    CustomHashTableElement *head = 0;

public:
    CustomHashTable()
    {
        // TODO: create 10 elements, can do it in function and here call it
    }

    void createBaseTable()
    {
        // create CustomHashTableElement elements and set them nominal: i + 1, value by default is 0
    }

    void addCoinToTable(int position)
    {
        // find needed pair and countOfCoinsValue++
    }

    void takeCoinFromTable(int position)
    {
        // take coin if countOfCoinsValue is not 0, else error message ???
    }
};

class Coin
{
private:
    int nominal;

public:
    Coin()
    {
        // nominal from 1 to 10
        nominal = rand() % 10 + 1;
    }
    // added getter for private nominal
    int getNominal()
    {
        return nominal;
    }

    friend ostream &operator<<(ostream &output, Coin &coin)
    {
        output << coin.getNominal();
        return output;
    }
};

class MoneyBox
{
private:
    int sumOfCoins;

    // TODO: можно было сделать массивом с подмассивами, типо: {{1, 4}, {2, 34}, {3, 5}} (первое значение это номинал монеты, второе это количество таких монет)
    CustomHashTable countOfCoinsByNomination;

public:
    MoneyBox()
    {
        // maybe code ???
    }

    void saveCoinToBox(Coin coin)
    {
        sumOfCoins += coin.getNominal();
        int positionInHashTable = coin.getNominal() - 1; // nominal 7, position 6

        countOfCoinsByNomination.addCoinToTable(positionInHashTable);
    }
};

int main()
{
    srand(time(0));
    const int countCoins = 100, countBoxes = 3;

    MoneyBox moneyBoxes[countBoxes];
    Coin coins[countCoins];

    for (int i = 0; i < countCoins; i++)
    {
        int numberOfRandomBox = rand() % countBoxes;
        moneyBoxes[numberOfRandomBox].saveCoinToBox(coins[i]);
    }
    return 0;
}