#include "Tetris.h"

int main()
{
    std::cout << "TETRIS SETTING\n";

    std::cout << "Input screen width : ";
    int width{};
    std::cin >> width;

    std::cout << "Input screen height : ";
    int height{};
    std::cin >> height;

    std::cout << "block moving  : use �� and ��\n";
    std::cout << "block rotating: use z  and x\n";
    std::cout << "\nPress any key to start game.\n";

    _getch();
    std::system("cls");

    ws::Tetris{ width, height }.Run();

    return 0;
}
