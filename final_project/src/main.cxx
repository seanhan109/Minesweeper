#include "controller.hxx"

#include <stdexcept>
#include<string>
#include<iostream>

int
main(int argc, char* argv[])
{
    try {
        int width;
        int height;
        int numMines;
        /// 1 argument sets the board as default; 2 arguments means it's one of the 3 pre-set boards; 4 arguments means
        /// a user defined board
        switch(argc)
        {
            case 1:
                width = 10;
                height = 10;
                numMines = 10;
                break;
            case 2:
                // 0 is easy, 1 is medium, everything else is hard
                if(std::stoi(argv[1]) == 0)
                {
                    width = 10;
                    height = 10;
                    numMines = 10;
                }
                else if (std::stoi(argv[1]) == 1)
                {
                    width = 18;
                    height = 14;
                    numMines = 40;
                }
                else
                {
                    width = 16;
                    height = 30;
                    numMines = 99;
                }
                break;
            case 4:
                width = std::stoi(argv[1]);
                height = std::stoi(argv[2]);
                numMines = std::stoi(argv[3]);
                break;
            default:
                std::cerr<< "Usage: " << argv[0] << " [WIDTH HEIGHT NUMMINES]\n";
                return 1;

        }
        Controller(width, height, numMines).run();
    }catch(std::exception const& e)
    {
        std::cerr << argv[0] <<": " << e.what() << "\n";
        return 1;
    }
    return 0;
}
