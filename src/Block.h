#ifndef BLOCKCLASS_H
#define BLOCKCLASS_H


#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int Nm = 21, Mm = 12;

class Block
{
protected:
    struct Part
	{
		int X, Y;
        bool incheckDown, incheckLeft, incheckRight;
	};

public:	
    static Block* newBlock();
    virtual void turn() = 0;
    int move(Keyboard::Key key);

public:
    Part *parts = nullptr;
    static constexpr int N = 4;
    int type_, color_, side_ = 1;
    bool check = true;
};

#endif
