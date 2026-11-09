#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int showMenu();
void registerSignal(vector<int> &signals, int value);
void showSignals(const vector<int> &signals);
double averageSignal(const vector<int> &signals);
int minimumSignal(const vector<int> &signals);
int maximumSignal(const vector<int> &signals);
int countWeak(const vector<int> &signals, int index);
void showAnalytics(const vector<int> &signals);

int main()
{
    string probeName;
    vector<int> signals;
    int choice;

    cout << "Введите название или позывной зонда: ";
    getline(cin, probeName);

    while (true)
    {
        cout << "\nЗонд " << probeName << "\n";
        choice = showMenu();

        if (choice == 0)
        {
            cout << "Программа завершена\n";
            break;
        }
        else if (choice == 1)
        {
            int value;
            cout << "Введите качество сигнала (0-100): ";

            if (cin >> value)
            {
                registerSignal(signals, value);
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Нужно ввести целое число\n";
            }
        }
        else if (choice == 2)
        {
            showSignals(signals);
        }
        else if (choice == 3)
        {
            showAnalytics(signals);
        }
        else
        {
            cout << "Такой команды нет\n";
        }
    }

    return 0;
}

int showMenu()
{
    int choice;

    cout << "1 - зарегистрировать измерение\n"
         << "2 - показать историю измерений\n"
         << "3 - показать аналитику\n"
         << "0 - завершить программу\n"
         << "Ваш выбор: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }

    return choice;
}

void registerSignal(vector<int> &signals, int value)
{
    static int count = 0;

    if (value >= 0 && value <= 100)
    {
        signals.push_back(value);
        count++;
        cout << "Измерение зарегистрировано. Всего зарегистрировано: "
             << count << "\n";
    }
    else
    {
        cout << "Ошибка: значение должно быть от 0 до 100\n";
    }
}

void showSignals(const vector<int> &signals)
{
    if (signals.empty())
    {
        cout << "Измерений пока нет\n";
        return;
    }

    cout << "История измерений: ";
    for (int i = 0; i < signals.size(); i++)
    {
        cout << signals[i] << " ";
    }

    cout << "\nКоличество измерений: " << signals.size() << "\n";
}

double averageSignal(const vector<int> &signals)
{
    int sum = 0;

    for (int i = 0; i < signals.size(); i++)
    {
        sum += signals[i];
    }

    return static_cast<double>(sum) / signals.size();
}

int minimumSignal(const vector<int> &signals)
{
    int minimum = signals[0];

    for (int i = 1; i < signals.size(); i++)
    {
        if (signals[i] < minimum)
        {
            minimum = signals[i];
        }
    }

    return minimum;
}

int maximumSignal(const vector<int> &signals)
{
    int maximum = signals[0];

    for (int i = 1; i < signals.size(); i++)
    {
        if (signals[i] > maximum)
        {
            maximum = signals[i];
        }
    }

    return maximum;
}

int countWeak(const vector<int> &signals, int index)
{
    if (index >= signals.size())
    {
        return 0;
    }

    if (signals[index] < 30)
    {
        return 1 + countWeak(signals, index + 1);
    }

    return countWeak(signals, index + 1);
}

void showAnalytics(const vector<int> &signals)
{
    if (signals.empty())
    {
        cout << "Нет данных для анализа\n";
        return;
    }

    double average = averageSignal(signals);

    cout << "Средний уровень сигнала: " << average << "\n";
    cout << "Самое слабое измерение: " << minimumSignal(signals) << "\n";
    cout << "Самое сильное измерение: " << maximumSignal(signals) << "\n";
    cout << "Измерений ниже 30: " << countWeak(signals, 0) << "\n";

    if (average >= 70)
    {
        cout << "Состояние связи: Стабильная\n";
    }
    else if (average >= 40)
    {
        cout << "Состояние связи: Нестабильная\n";
    }
    else
    {
        cout << "Состояние связи: Критическая\n";
    }
}
