#include <iostream>
#include <cmath>
#include <string>
#include <curses.h>

using namespace std;

void smth(int A, int B, int C, int& X, int& Y, float& Z)
{
    X = min(A + B, A + C);
    X = min(X, B + C);
    Y = max(A, 2 * B);
    Y = max(Y, 3 * C);
    if (Y == 0 || X == 0)
        Z = 0;
    else
        Z = (float)X / (float)Y;
}

float rUsure(float X, float Y)
{
    if ((X * X) + (Y * Y) <= 1)
        return 2;
    else if ((X >= -3 && X <= -2) && (Y >= -2 && Y <= 1))
        return 1;
    else
        return 0;
}

int check(WINDOW* win, int x, int y, const char* prompt)
{
    int num;//верное число
    bool is_valid = false;//флаг

    while (!is_valid) {
        char* input_str = new char[256];// Выделяем память для массива символов, который будет хранить введенное пользователем значение
        echo(); // Включаем эхо-режим, чтобы введенные символы отображались на экране
        wgetstr(win, input_str); // Считываем строку ввода 
        noecho(); // Выключаем эхо-режим
        try 
        {
            num = stoi(input_str);// Преобразуем строку в число типа int
            is_valid = true;// Если преобразование прошло успешно, устанавливаем флаг is_valid в значение true
        }
        catch (invalid_argument&)
        {
            // Если не удалось преобразовать в число, выводим ошибку и повторяем ввод
            mvwprintw(win, x, y + 8, "                            ");
            mvwprintw(win, x, y + 8, "Invalid input. Try again: ");
            wrefresh(win);
        }
    }

    return num;
}


int main()
{
    initscr();

    // создаем окно для ввода данных
    WINDOW* inputwin = newwin(10, 40, 12, 30);
    // создаем окно для вывода данных
    WINDOW* outputwin = newwin(10, 30, 12, 70);

    // выводим рамки окон
    box(inputwin, 0, 0);
    box(outputwin, 0, 0);
    // выводим заголовки окон
    mvwprintw(inputwin, 0, 1, "Input:");
    mvwprintw(outputwin, 0, 1, "Output:");
    // делаем окна цветными
    start_color();
    /*
        COLOR_BLACK
        COLOR_RED
        COLOR_GREEN
        COLOR_YELLOW
        COLOR_BLUE
        COLOR_MAGENTA
        COLOR_CYAN
        COLOR_WHITE
        */
    
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    wbkgd(inputwin, COLOR_PAIR(1));
    wbkgd(outputwin, COLOR_PAIR(2));
    //делаем окна видимыми
    wrefresh(inputwin);
    wrefresh(outputwin);

    //переменные для вычислений
    int A, B, C, X, Y, DD = 0;
    float Z, U;

    // ждем ввода данных в окно "input"
    mvwprintw(inputwin, 2, 1, "Enter A: ");
    wrefresh(inputwin);
    A = check(inputwin, 2, 1, "Enter A: ");

    mvwprintw(inputwin, 4, 1, "Enter B: ");
    wrefresh(inputwin);
    B = check(inputwin, 4, 1, "Enter B: ");

    mvwprintw(inputwin, 6, 1, "Enter C: ");
    wrefresh(inputwin);
    C = check(inputwin, 6, 1, "Enter C: ");

    // вызываем функцию smth для вычисления X, Y, Z
    smth(A, B, C, X, Y, Z);

    //вычисляем U
    if (rUsure(X, Y) == 2)
    {
        U = X - Y + Z;
        DD = 2;
    }
    if (rUsure(X, Y) == 1)
    {
        U = log10(abs(X + Y));
        DD = 1;
    } 
    if (rUsure(X, Y) == 0)
    {
        U = 1;
    }

    // выводим результаты в окно "output"
    mvwprintw(outputwin, 1, 1, "A: %d", A);
    mvwprintw(outputwin, 2, 1, "B: %d", B);
    mvwprintw(outputwin, 3, 1, "C: %d", C);
    mvwprintw(outputwin, 4, 1, "X: %d", X);
    mvwprintw(outputwin, 5, 1, "Y: %d", Y);
    mvwprintw(outputwin, 6, 1, "Z: %.2f", Z);
    mvwprintw(outputwin, 7, 1, "U: %.2f", U);
    if(DD ==1)
        mvwprintw(outputwin, 8, 1, "D1");
    if (DD == 2)
        mvwprintw(outputwin, 8, 1, "D2");
    


    // обновляем содержимое обоих окон перед ожиданием нажатия клавиши
    wrefresh(inputwin);
    wrefresh(outputwin);

    // ждем нажатия на клавишу, чтобы закрыть окна
    wgetch(outputwin);

    // закрываем библиотеку curses
    endwin();

    return 0;
}