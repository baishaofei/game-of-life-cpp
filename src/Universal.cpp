#include "Universal.h"
#include "Cell.h"
#include <iostream>
#include "Role.h"

namespace
{
    void initCell(Cell& cell, bool isAlive)
    {
        typedef void (Cell::*Action)();
        Action actions[] = {&Cell::die, &Cell::live};
        (cell.*actions[isAlive])();
    }
}

DEFINE_ROLE(Universal::CellVisitor)
{
    ABSTRACT(void visit(Cell& cell, int row, int column) const);
};

Universal::Universal(const int* initCells, int rows, int columns) : rows(rows), columns(columns), cells(createCells())
{
    for(int i = 0; i < rows * columns; ++i)
    {
        int row = i / columns;
        int column = i % columns;

        initCell(at(row, column), initCells[i] == 1);
    }
}

Universal::~Universal()
{
    destroyCells();
}

int Universal::row(int i) const
{
	return i/columns;
}

int Universal::column(int i) const
{
	return i%columns;
}

bool Universal::isOutOfBound(int row, int column) const
{
    return row < 0 || row >= rows || column < 0 || column >= columns;
}

bool Universal::operator==(const Universal& rhs) const
{
    int sum = 0;
    int counter[] = {0, 1};

    for(int i= 0; i < rows * columns; ++i)
    {
        sum += counter[at(row(i), column(i)).status()  !=  rhs.at(row(i), column(i)).status()];
    }

    return sum == 0;
}

Cell& Universal::at(int row, int column) const
{

    static Cell NullCell;
    Cell* cell[] = {&cells[row * columns + column], &NullCell};

    return *cell[isOutOfBound(row, column)];
}

Cell* Universal::createCells()
{
    return new Cell[ rows * columns ];
}

void Universal::destroyCells()
{
    delete[] cells;
}

void Universal::visitUniversal(CellVisitor& visitor) const
{
    for(int i= 0; i < rows * columns; ++i)
    {
        visitor.visit(at(row(i), column(i)), row(i), column(i));
    }
}

void Universal::print(char aliveSymbol, char deadSymbol) const
{
    for(int i= 0; i < rows * columns; ++i)
    {
        char symbols[] = { deadSymbol, aliveSymbol };
        char separator[] = {' ', '\n'};
        std::cout << symbols[at(row(i), column(i)).status()] << separator[column(i) == columns -1];
    }
}

 int Universal::countAliveNeighboursAt(int row, int column) const
 {
        return ( at(row - 1, column - 1).status()
        	   + at(row - 1, column).status()
               + at(row - 1, column + 1).status()
               + at(row, column - 1).status()
               + at(row, column + 1).status()
               + at(row + 1, column - 1).status()
               + at(row + 1, column).status()
               + at(row + 1, column + 1).status());
 }

void Universal::evolve()
{
    evolveCurrentGeneration();
    createNextGeneration();
}

void Universal::evolveCurrentGeneration()
{
    struct CurrentGenerationVisitor : Universal::CellVisitor
    {
        CurrentGenerationVisitor(const Universal& u)  : u(u) {}

        OVERRIDE(void visit(Cell& cell, int row, int column) const)
        {
            int aliveNum = u.countAliveNeighboursAt(row, column);
            cell.evolveCurrentGeneration(aliveNum);
        }
       const Universal& u;
    };

    CurrentGenerationVisitor visitor(*this);
    visitUniversal(visitor);
}

void Universal::createNextGeneration()
{
    struct : Universal::CellVisitor
    {
        OVERRIDE(void visit(Cell& cell, int row, int column) const)
        {
            cell.createNextGeneration();
        }
    } visitor;

    visitUniversal(visitor);
}
