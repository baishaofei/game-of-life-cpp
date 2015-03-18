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

    typedef void(*Visit)(int rows, int columns);

    void visitAllCells(Visit visit, int rows, int columns)
    {
        for(int i = 0; i < rows * columns; ++i)
        {
            int row = i / rows;
            int column = i % columns;

            visit(row, column);
        }
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
        int row = i / rows;
        int column = i % columns;
        initCell(at(row, column), initCells[i] == 1);
    }
}

Universal::~Universal()
{
    destroyCells();
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
        int row = i / rows;
        int column = i % columns;
        sum += counter[at(row, column).status()  !=  rhs.at(row, column).status()];
    }

    return sum == 0;
}

Cell& Universal::at(int row, int column) const
{
    static Cell NullCell;
    Cell* cell[] = {&cells[row * rows + column], &NullCell};

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
        int row = i / rows;
        int column = i % columns;
        
        visitor.visit(at(row, column), row, column);
    }
}

void Universal::print(char aliveSymbol, char deadSymbol) const
{
    for(int i= 0; i < rows * columns; ++i)
    {
        int row = i / rows;
        int column = i % columns;

        char symbols[] = { deadSymbol, aliveSymbol };
        char separator[] = {' ', '\n'};
        std::cout << symbols[at(row, column).status()] << separator[column == columns -1];
    }
}

 int Universal::countAliveNeighboursAt(int row, int column) const
 {
        return (  at(row - 1, column - 1).status()
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
