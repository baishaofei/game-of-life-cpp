#include "Cell.h"
#include "Role.h"

DEFINE_ROLE(Cell::CellState)
{
    ABSTRACT(CellStatus status() const);
    ABSTRACT(void transition(Cell& cell) const);
    ABSTRACT(void evolve(int neighbours, Cell& cell) const);

    void remain(Cell& cell) const { }
};

struct Cell::AliveCellState : Cell::CellState
{
    static CellState& getInstance()
    {
        static AliveCellState state;
        return state;
    }

private:
    OVERRIDE(CellStatus status() const)
    {
        return ALIVE;
    }
    OVERRIDE(void transition(Cell& cell) const)
    {
        cell.die();
    }
    OVERRIDE(void evolve(int neighbours, Cell& cell) const)
    {
        static bool stateChangeTable[] = {true, true, false, false, true, true, true, true, true };
        cell.isStateChanged = stateChangeTable[neighbours];
    }
};

struct Cell::DeadCellState : Cell::CellState
{
    static CellState& getInstance()
    {
        static DeadCellState state;
        return state;
    }

private:
    OVERRIDE(CellStatus status() const)
    {
        return DEAD;
    }
    OVERRIDE(void transition(Cell& cell) const)
    {
        cell.live();
    }
    OVERRIDE(void evolve(int neighbours, Cell& cell) const)
    {
        static bool stateChangeTable[] = {false, false, false, true, false, false, false, false, false};
        cell.isStateChanged = stateChangeTable[neighbours];
    }
};

namespace
{
    #define ALIVE_STATE &AliveCellState::getInstance()
    #define DEAD_STATE &DeadCellState::getInstance()
}
/////////////////////////////////////////////////////////////////////////////////////////////////
Cell::Cell() : state(DEAD_STATE), isStateChanged(false)
{
}

CellStatus Cell::status() const
 {
    return state->status();
 }

void Cell::live()
{
    state = ALIVE_STATE;
}

void Cell::die()
{
    state = DEAD_STATE;
}

void Cell::evolveCurrentGeneration(int neighbours)
{
    state->evolve(neighbours, *this);
}

void Cell::createNextGeneration()
{
    typedef void (Cell::CellState::*StateChangeFun)(Cell& cell) const;
    StateChangeFun process[] = { &Cell::CellState::remain
                               , &Cell::CellState::transition};
    (state->*process[isStateChanged])(*this);                                           
}
