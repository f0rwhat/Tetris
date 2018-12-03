#include "Block.h"


class BlockLine : public Block
{
public:
    BlockLine(int color)
    {
        color_ = color;
        parts = new Part[N];
        for (int i = 0; i < N; i++)
            parts[i].Y = 0;
        for (int i = 0, j = Mm / 2 - 2; i < N; i++, j++)
            parts[i].X = j;
        for (int i = 0; i < N; i++)
        {
            parts[i].incheckDown = true;
            parts[i].incheckLeft = false;   //0 1 2 3
            parts[i].incheckRight = false;
        }
        parts[0].incheckLeft = true;
        parts[3].incheckRight = true;
    }

    void turn() override
    {
        switch (side_)
        {
        case 1:
            if (parts[0].Y < Nm - 4)
            {
                /*
                for (int i = parts[0].Y, j = parts[0].X; i <= parts[0].Y + 3; i++)
                    if (map->map[i][j] != 0)
                        check = false;
                        */
            }
            else check = false;
            if (check)
            {
                for (int i = 1; i < N; i++)
                {
                    parts[i].X = parts[0].X;
                    parts[i].Y = parts[0].Y + i;
                }
                for (int i = 0; i < N; i++)
                {
                    parts[i].incheckDown = false;
                    parts[i].incheckLeft = true;
                    parts[i].incheckRight = true;
                }
                parts[3].incheckDown = true;
                side_ = 2;
            }
            break;
        case 2:
            if (parts[0].X < Mm - 4)
            {
                /*
                for (int j = parts[0].X, i = parts[0].Y; j <= parts[0].X + 3; j++)
                    if (map->map[i][j] != 0)
                        check = false;
                        */
            }
            else check = false;
            if (check)
            {
                for (int i = 1; i < N; i++)
                {
                    parts[i].Y = parts[0].Y;
                    parts[i].X = parts[0].X + i;
                }
                for (int i = 0; i < N; i++)
                {
                    parts[i].incheckDown = true;
                    parts[i].incheckLeft = false;
                    parts[i].incheckRight = false;
                }
                parts[0].incheckLeft = true;
                parts[3].incheckRight = true;
                side_ = 1;
            }
            break;
        }
    }
};

class BlockSquare : public Block
{
public:
    BlockSquare(int color)
    {
        color_ = color;
        parts = new Part[N];
        parts[0].Y = 0; parts[0].X = Mm / 2;
        parts[1].Y = 0; parts[1].X = Mm / 2 + 1;			//0 1
        parts[2].Y = 1; parts[2].X = Mm / 2;				//2 3
        parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
        parts[0].incheckDown = false;
        parts[0].incheckLeft = true;
        parts[0].incheckRight = false;
        parts[1].incheckDown = false;
        parts[1].incheckLeft = false;
        parts[1].incheckRight = true;
        parts[2].incheckDown = true;
        parts[2].incheckLeft = true;
        parts[2].incheckRight = false;
        parts[3].incheckDown = true;
        parts[3].incheckLeft = false;
        parts[3].incheckRight = true;
    }

    void turn() override {    }
};

class BlockZigZag : public Block
{
public:
    BlockZigZag(int color)
    {
        color_ = color;
        parts = new Part[N];
        parts[0].Y = 0; parts[0].X = Mm / 2 - 1;
        parts[1].Y = 0; parts[1].X = Mm / 2;			//0 1
        parts[2].Y = 1; parts[2].X = Mm / 2;			//  2 3
        parts[3].Y = 1; parts[3].X = Mm / 2 + 1;
        parts[0].incheckDown = true;
        parts[0].incheckLeft = true;
        parts[0].incheckRight = false;
        parts[1].incheckDown = false;
        parts[1].incheckLeft = false;
        parts[1].incheckRight = true;
        parts[2].incheckDown = true;
        parts[2].incheckLeft = true;
        parts[2].incheckRight = false;
        parts[3].incheckDown = true;
        parts[3].incheckLeft = false;
        parts[3].incheckRight = true;
    }

    void turn() override
    {
        switch (side_)
        {
        case 1:
            if (!(parts[0].Y < Nm - 3)) check = false;
            /*
            if (map->map[parts[0].X][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X - 1][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X - 1][parts[0].Y + 2] != 0) check = false;
            */
            if (check)
            {
                parts[1].X = parts[0].X;
                parts[1].Y = parts[0].Y + 1;
                parts[2].X = parts[0].X - 1;
                parts[2].Y = parts[0].Y + 1;
                parts[3].X = parts[0].X -1;
                parts[3].Y = parts[0].Y + 2;

                parts[0].incheckDown = false;
                parts[0].incheckLeft = true;
                parts[0].incheckRight = true;
                parts[1].incheckDown = true;
                parts[1].incheckLeft = false;
                parts[1].incheckRight = true;
                parts[2].incheckDown = false;
                parts[2].incheckLeft = true;
                parts[2].incheckRight = false;
                parts[3].incheckDown = true;
                parts[3].incheckLeft = true;
                parts[3].incheckRight = true;

                side_ = 2;
            }
            break;
        case 2:
            if (!(parts[0].X < Mm - 3)) check = false;
            /*
            if (map->map[parts[0].X + 1][parts[0].Y] != 0) check = false;
            if (map->map[parts[0].X + 1][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X + 2][parts[0].Y + 1] != 0) check = false;
            */
            if (check)
            {
                parts[1].X = parts[0].X + 1;
                parts[1].Y = parts[0].Y;
                parts[2].X = parts[0].X + 1;
                parts[2].Y = parts[0].Y + 1;
                parts[3].X = parts[0].X + 2;
                parts[3].Y = parts[0].Y + 1;

                parts[0].incheckDown = true;
                parts[0].incheckLeft = true;
                parts[0].incheckRight = false;
                parts[1].incheckDown = false;
                parts[1].incheckLeft = false;
                parts[1].incheckRight = true;
                parts[2].incheckDown = true;
                parts[2].incheckLeft = true;
                parts[2].incheckRight = false;
                parts[3].incheckDown = true;
                parts[3].incheckLeft = false;
                parts[3].incheckRight = true;
                side_ = 1;
            }
            break;
        }
    }
};

class BlockZigZagLeft : public Block
{
public:
    BlockZigZagLeft(int color)
    {
        color_ = color;
        parts = new Part[N];
        parts[0].Y = 0; parts[0].X = Mm / 2 + 1;
        parts[1].Y = 0; parts[1].X = Mm / 2;			//   1 0
        parts[2].Y = 1; parts[2].X = Mm / 2;			// 3 2
        parts[3].Y = 1; parts[3].X = Mm / 2 - 1;
        parts[0].incheckDown = true;
        parts[0].incheckLeft = false;
        parts[0].incheckRight = true;
        parts[1].incheckDown = false;
        parts[1].incheckLeft = true;
        parts[1].incheckRight = false;
        parts[2].incheckDown = true;
        parts[2].incheckLeft = false;
        parts[2].incheckRight = true;
        parts[3].incheckDown = true;
        parts[3].incheckLeft = true;
        parts[3].incheckRight = false;
    }

    void turn() override
    {
        switch (side_)
        {
        case 1:
            if (!(parts[0].Y < Nm - 3)) check = false;
            /*
            if (map->map[parts[0].X][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X + 1][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X + 1][parts[0].Y + 2] != 0) check = false;
            */
            if (check)
            {
                parts[1].X = parts[0].X;
                parts[1].Y = parts[0].Y + 1;
                parts[2].X = parts[0].X + 1;
                parts[2].Y = parts[0].Y + 1;
                parts[3].X = parts[0].X + 1;
                parts[3].Y = parts[0].Y + 2;

                parts[0].incheckDown = false;
                parts[0].incheckLeft = true;
                parts[0].incheckRight = true;
                parts[1].incheckDown = true;
                parts[1].incheckLeft = true;
                parts[1].incheckRight = false;
                parts[2].incheckDown = false;
                parts[2].incheckLeft = false;
                parts[2].incheckRight = true;
                parts[3].incheckDown = true;
                parts[3].incheckLeft = true;
                parts[3].incheckRight = true;

                side_ = 2;
            }
            break;
        case 2:
            if (!(parts[0].X > 2)) check = false;
            /*
            if (map->map[parts[0].X - 1][parts[0].Y] != 0) check = false;
            if (map->map[parts[0].X - 1][parts[0].Y + 1] != 0) check = false;
            if (map->map[parts[0].X - 2][parts[0].Y + 1] != 0) check = false;
            */
            if (check)
            {
                parts[1].X = parts[0].X - 1;
                parts[1].Y = parts[0].Y;
                parts[2].X = parts[0].X - 1;
                parts[2].Y = parts[0].Y + 1;
                parts[3].X = parts[0].X - 2;
                parts[3].Y = parts[0].Y + 1;
                parts[0].incheckDown = true;
                parts[0].incheckLeft = false;
                parts[0].incheckRight = true;
                parts[1].incheckDown = false;
                parts[1].incheckLeft = true;
                parts[1].incheckRight = false;
                parts[2].incheckDown = true;
                parts[2].incheckLeft = false;
                parts[2].incheckRight = true;
                parts[3].incheckDown = true;
                parts[3].incheckLeft = true;
                parts[3].incheckRight = false;
                side_ = 1;
            }
            break;
        }
    }
};


Block *Block::newBlock()
{
    srand ((unsigned)time(NULL));
    int type, color, side;
    color = rand() % 6 + 1;
    type  = rand() % 4 + 1;

    Block *block;

    switch (type)
    {
    case 1:
        block = new BlockLine(color);
        break;
    case 2:
        block = new BlockSquare(color);
        break;
    case 3:
        block = new BlockZigZag(color);
        break;
    case 4:
        block = new BlockZigZagLeft(color);
    }

    return block;
}

int Block::move(Keyboard::Key key)
{
    switch (key)
    {
    case Keyboard::Down:
        /*
            for (int i = 0; i < N; i++)
                if (parts[i].incheckDown && map->map[parts[i].Y + 1][parts[i].X] != 0)
                    return 0;
                    */
        for (int i = 0; i < N; i++)
            parts[i].Y++;
        break;
    case Keyboard::Left:
        /*
            for (int i = 0; i < N; i++)
                if (parts[i].incheckLeft && map->map[parts[i].Y][parts[i].X - 1] != 0)
                    return 0;
                    */
        for (int i = 0; i < N; i++)
            parts[i].X--;
        break;
    case Keyboard::Right:
        /*
            for (int i = 0; i < N; i++)
                if (parts[i].incheckRight && map->map[parts[i].Y][parts[i].X + 1] != 0)
                    return 0;
                    */
        for (int i = 0; i < N; i++)
            parts[i].X++;
        break;
    default:;
    }
    return 1;
}
