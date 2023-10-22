#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <iterator>

#pragma warning(disable: 4996)
using namespace std;

void drow_map(char map[]); // Объявление функции для вывода игрового поля в консоль

int minimax(char map[], char player); // Объявлении функции minimax

bool winning(char map[], char player); // Функция проверки на победу

bool draw(char map[]); // Объявление функции draw (проверка на ничью)

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    char map[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }; // инициализируем пустое игровое поле

    int button;
    int chk_score = 0;
    int score = -10000;
    int chk_ind = 0;
    int ind = 0;
    bool cor = false;
    char who = ' '; // O - человек, X - компьютер
    char human = 'O';
    char ai = 'X';

    while (true) // цикл, чтобы начинать новую игру
    {
        while (true) // главный цикл
        {
            while (!cor)
            {
                system("cls");
                drow_map(map); // рисуем карту
                cout << endl << "Нажмите одну из клавиш:" << endl << "q, w, e," << endl << "a, s, d," << endl << "z, x, c." << endl;
                cout << "Сделайте ход!" << endl << "Ожидание нажатия клавиши...";
                button = getch(); // ловим нажатие клавиши
                //cout << "button = " << button << endl; // узнать код нажатой клавиши

                switch (button)
                {
                case 113: // клавиша "q" (eng)
                    if (map[0] == ' ')
                    {
                        map[0] = 'O';
                        cor = true;
                    }
                    break;
                case 119: // клавиша "w" (eng)
                    if (map[1] == ' ')
                    {
                        map[1] = 'O';
                        cor = true;
                    }
                    break;
                case 101: // клавиша "e" (eng)
                    if (map[2] == ' ')
                    {
                        map[2] = 'O';
                        cor = true;
                    }
                    break;
                case 97: // клавиша "a" (eng)
                    if (map[3] == ' ')
                    {
                        map[3] = 'O';
                        cor = true;
                    }
                    break;
                case 115: // клавиша "s" (eng)
                    if (map[4] == ' ')
                    {
                        map[4] = 'O';
                        cor = true;
                    }
                    break;
                case 100: // клавиша "d" (eng)
                    if (map[5] == ' ')
                    {
                        map[5] = 'O';
                        cor = true;
                    }
                    break;
                case 122: // клавиша "z" (eng)
                    if (map[6] == ' ')
                    {
                        map[6] = 'O';
                        cor = true;
                    }
                    break;
                case 120: // клавиша "x" (eng)
                    if (map[7] == ' ')
                    {
                        map[7] = 'O';
                        cor = true;
                    }
                    break;
                case 99: // клавиша "c" (eng)
                    if (map[8] == ' ')
                    {
                        map[8] = 'O';
                        cor = true;
                    }
                    break;
                default:
                    system("cls");
                    break;
                }
            }

            system("cls");
            drow_map(map); // рисуем карту

            if (winning(map, human)) // если победа человека, выходим из цикла
            {
                cout << endl << "Человечество победило! Планета спасена!" << endl;
                break;
            }
            else if (draw(map)) // если ничья, выходим из цикла
            {
                cout << endl << "Ничья! Баланс сил в мире сохранен!" << endl;
                break;
            }
            else who = ai; // иначе определяем ход компьютера

            if (who == 'X') // если сейчас ходит компьютер
            {
                for (int i = 0; i < 9; i++) // проходим по всем клеткам
                {
                    if (map[i] == ' ') // если клетка пустая
                    {
                        map[i] = 'X'; // делаем в нее ход Х (от лица компьютера)
                        chk_ind = i; // запоминаем индекс
                        who = human;
                        chk_score = minimax(map, who); // вызываем функцию минимакс и получаем от нее счет
                        map[i] = ' '; // очищаем клетку
                        if (chk_score > score) // если полученный счет больше текущего
                        {
                            score = chk_score; // обновляем текущий счет
                            ind = chk_ind; // запоминаем индекс клетки
                        }
                    }
                }
            }
            map[ind] = 'X'; // компьютер ходит Х в клетку с индексом соответствующему максимальному счету
            system("cls");
            drow_map(map); // рисуем карту
            if (winning(map, ai)) // Если победил компьютер
            {
                cout << endl << "Поражение! Машины захватили планету!" << endl;
                break;
            }
            else if (draw(map)) // Если ничья
            {
                cout << endl << "Ничья! Баланс сил в мире сохранен!" << endl;
                break;
            }
            else
            {
                who = human;
                cor = false;
                score = -10000;
                ind = 0;
            }
        }
        cout << endl << "Начать новую игру?" << endl << endl << "ENTER - начать новую игру" << endl << "ESC - выход" << endl << endl << "Ожидание нажатия клавиши..." << endl;
        button = getch(); // ловим нажатие клавиши
        switch (button)
        {
        case 13:
            for (int i = 0; i < 9; i++)
                map[i] = ' ';
            who = human;
            cor = false;
            score = -10000;
            ind = 0;
            break;
        case 27:
            return 0;
            break;
        }
    }

    return 0;
}

void drow_map(char map[]) // Определение функции для вывода игрового поля в консоль
{
    string part[2] = { " +---+---+---+ ", " | " }; // массив типа строка для построения границ игрового поля
    for (int i = 0; i < 9; i++)
    {
        if ((i == 0) || (i == 3) || (i == 6))
            cout << endl << part[0] << endl << part[1];
        cout << map[i] << part[1];
        if (i == 8)
            cout << endl << part[0] << endl;
    }
}

int minimax(char map[], char player) // Определение функции minimax
{
    int max_score = 0;
    int min_score = 0;
    int score = 0;
    char human = 'O';
    char ai = 'X';

    if (winning(map, human)) // Если победа человека
        return -10;
    else if (winning(map, ai)) // Если победа компьютера
        return 10;
    else if (draw(map)) // Если ничья
        return 0;
    else // если терминальное состояние не достигнуто
    {
        list <int> moves;
        list <int>::iterator it;
        if (player == ai) // если ходит компьютер
        {
            for (int i = 0; i < 9; i++) // проходим по всем клеткам
            {
                if (map[i] == ' ') // если клетка пустая
                {
                    map[i] = 'X'; // делаем в нее ход Х (от лица компьютера)
                    player = human; // делаем текущим игроком человека
                    score = minimax(map, player);
                    map[i] = ' ';
                    moves.push_back(score);
                }
            }
            for (it = moves.begin(); it != moves.end(); it++)
            {
                if (it == moves.begin())
                    max_score = *it;
                else if (*it > max_score)
                    max_score = *it;
            }
            return max_score;
        }
        else if(player == human) // если ходит человек
        {
            for (int i = 0; i < 9; i++) // проходим по всем клеткам
            {
                if (map[i] == ' ') // если клетка пустая
                {
                    map[i] = 'O'; // делаем в нее ход Х (от лица человека)
                    player = ai; // делаем текущим игроком компьютер
                    score = minimax(map, player);
                    map[i] = ' ';
                    moves.push_back(score);
                }
            }
            for (it = moves.begin(); it != moves.end(); it++)
            {
                if (it == moves.begin())
                    min_score = *it;
                else if (*it < min_score)
                    min_score = *it;
            }
            return min_score;
        }
    }
}

bool winning(char map[], char player)
{
    if (
        (map[0] == player && map[1] == player && map[2] == player) || // горизонтальный ряд 1
        (map[3] == player && map[4] == player && map[5] == player) || // горизонтальный ряд 2
        (map[6] == player && map[7] == player && map[8] == player) || // горизонтальный ряд 3
        (map[0] == player && map[3] == player && map[6] == player) || // вертикальный ряд 1
        (map[1] == player && map[4] == player && map[7] == player) || // вертикальный ряд 2
        (map[2] == player && map[5] == player && map[8] == player) || // вертикальный ряд 3
        (map[0] == player && map[4] == player && map[8] == player) || // главная диагональ
        (map[2] == player && map[4] == player && map[6] == player)    // побочная диагональ
        ) return true;
    else return false;
}

bool draw(char map[])
{
    if ( // Если ничья
        (map[0] != ' ') && (map[1] != ' ') && (map[2] != ' ') &&
        (map[3] != ' ') && (map[4] != ' ') && (map[5] != ' ') &&
        (map[6] != ' ') && (map[7] != ' ') && (map[8] != ' ')
        ) return true;
    else return false;
}