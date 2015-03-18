#ifndef _INCL_GAME_OF_LIFE_CELL_H_
#define _INCL_GAME_OF_LIFE_CELL_H_

enum CellStatus { DEAD = 0, ALIVE = 1 };

struct Cell
{
    Cell();
    CellStatus status() const;

    void live();
    void die();

    void evolveCurrentGeneration(int neighbours);
    void createNextGeneration();

private:
    struct CellState;
    struct AliveCellState;
    struct DeadCellState;

private:
    CellState* state;
    bool isStateChanged;
    
private:
    friend struct AliveCellState;
    friend struct DeadCellState;
};

#endif
