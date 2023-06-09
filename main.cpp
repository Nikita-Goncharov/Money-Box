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
    int maxCountOfNominals;

    void _createBaseTable()
    {
        for (int i = 0; i < maxCountOfNominals; i++)
        {
            CustomHashTableElement *newElement = new CustomHashTableElement();
            newElement->nominalCoinKey = i + 1;

            if (head == 0)
            {
                head = newElement;
            }
            else
            {
                CustomHashTableElement *currentElement = head;
                while (currentElement->next != 0)
                {
                    currentElement = currentElement->next;
                }
                currentElement->next = newElement;
            }
        }
    }

    void _deleteTable()
    {
        CustomHashTableElement *currentElement;
        while (head)
        {
            currentElement = head;
            head = head->next;
            delete currentElement;
        }
    }

public:
    CustomHashTableElement *head;

    CustomHashTable()
    {
        maxCountOfNominals = 10;
        head = 0;
        _createBaseTable();
    }

    ~CustomHashTable()
    {
        _deleteTable();
    }

    void addCoinToTable(int nominal)
    {
        CustomHashTableElement *currentElement = head;
        while (currentElement)
        {
            if (currentElement->nominalCoinKey == nominal)
            {
                currentElement->countOfCoinsValue++;
                return;
            }
            currentElement = currentElement->next;
        }
    }

    string returnStringStatistic() const
    {
        string returnStatistic = "Count coins: \n";
        CustomHashTableElement *currentElement = head;
        while (currentElement != 0)
        {
            returnStatistic += "Nominal of coin: " + to_string(currentElement->nominalCoinKey) + ", Count of coins: " + to_string(currentElement->countOfCoinsValue) + "\n";
            currentElement = currentElement->next;
        }
        return returnStatistic;
    }

    void rewritePair(int nominal, int newCount)
    {
        CustomHashTableElement *currentElement = head;
        while (currentElement != 0)
        {
            if (currentElement->nominalCoinKey == nominal)
            {
                currentElement->countOfCoinsValue = newCount;
                return;
            }
            currentElement = currentElement->next;
        }
    }

    CustomHashTable& operator+(const CustomHashTable &hashTable)
    {
        CustomHashTableElement *currentElementOfOuterTable = hashTable.head;
        CustomHashTableElement *currentElementOfCurrentTable = head;

        while (currentElementOfCurrentTable && currentElementOfOuterTable)
        {
            int globalCount = currentElementOfOuterTable->countOfCoinsValue + currentElementOfCurrentTable->countOfCoinsValue;
            this->rewritePair(currentElementOfOuterTable->nominalCoinKey, globalCount);

            currentElementOfOuterTable = currentElementOfOuterTable->next;
            currentElementOfCurrentTable = currentElementOfCurrentTable->next;
        }

        return *this;
    }
};

class Coin
{
private:
    int nominal;

public:
    Coin()
    {
        nominal = rand() % 10 + 1;  // nominal from 1 to 10
    }

    // added getter for private nominal
    int getNominal()
    {
        return nominal;
    }
};

class MoneyBox
{
private:
    int sumOfCoins;
    CustomHashTable countOfCoinsByNomination;

public:
    MoneyBox() {
        sumOfCoins = 0;
    }

    void saveCoinToBox(Coin coin)
    {
        int nominal = coin.getNominal();
        sumOfCoins += nominal;

        countOfCoinsByNomination.addCoinToTable(nominal);
    }

    int getSumOfCoins()
    {
        return sumOfCoins;
    }

    friend ostream &operator<<(ostream &output, const MoneyBox &moneyBox)
    {
        output << "Sum of coins: " << moneyBox.sumOfCoins << endl;
        output << moneyBox.countOfCoinsByNomination.returnStringStatistic();
        return output;
    }

    MoneyBox& operator+(const MoneyBox &moneyBox)
    {
        sumOfCoins = sumOfCoins + moneyBox.sumOfCoins;
        countOfCoinsByNomination = countOfCoinsByNomination + moneyBox.countOfCoinsByNomination;
        return *this;
    }

    MoneyBox& operator+(const Coin &coin)
    {
        this->saveCoinToBox(coin);
        return *this;
    }
};

int main()
{
    srand(time(0));
    const int countCoins = 100, countBoxes = 3;

    int BiggestsumOfCoins = 0;
    int indexOfBiggestMoneyBox, menu, selectingMoneyBoxForAddingCoin;

    MoneyBox moneyBoxes[countBoxes];
    MoneyBox boxForSum;
    Coin coins[countCoins];

    for (int i = 0; i < countCoins; i++)
    {
        int numberOfRandomBox = rand() % countBoxes;
        moneyBoxes[numberOfRandomBox].saveCoinToBox(coins[i]);
    }

    while (true)
    {
        cout << "Menu: " << endl;
        cout << "1 - Print all money boxes" << endl;
        cout << "2 - Print biggest money box" << endl;
        cout << "3 - Print sum of all boxes" << endl;
        cout << "4 - Add coin to box" << endl;
        cout << "5 - Exit" << endl;
        cout << "Your choise: ";
        cin >> menu;

        if (menu < 1 || menu > 5)
        {
            continue;
        }

        if (menu == 5)
        {
            break;
        }

        switch (menu)
        {
        case 1:
            for (int i = 0; i < countBoxes; i++)
            {
                cout << "Money box number - " << i + 1 << endl;
                cout << moneyBoxes[i];
                cout << endl;
            }
            break;
        case 2:
            for (int i = 0; i < countBoxes; i++)
            {
                if (BiggestsumOfCoins < moneyBoxes[i].getSumOfCoins())
                {
                    BiggestsumOfCoins = moneyBoxes[i].getSumOfCoins();
                    indexOfBiggestMoneyBox = i;
                }
            }
            cout << "Biggest money box: " << endl;
            cout << moneyBoxes[indexOfBiggestMoneyBox];
            break;
        case 3:
             for (int i = 0; i < countBoxes; i++)
             {
                 boxForSum = boxForSum + moneyBoxes[i];
             }
            cout << "Sum of all money boxes: " << endl;
            cout << boxForSum;
            break;
        case 4:
            for (int i = 0; i < countBoxes; i++)
            {
                cout << i << " - Box" << i << endl;
            }
            cout << "Select box where you want add coin: ";
            cin >> selectingMoneyBoxForAddingCoin;
            Coin c;
            cout << moneyBoxes[selectingMoneyBoxForAddingCoin] + c;
            break;
        }
    }
    return 0;
}