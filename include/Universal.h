#ifndef _INCL_GAME_OF_LIFE_UNIVERSAL_H_
#define _INCL_GAME_OF_LIFE_UNIVERSAL_H_

struct Cell;

struct Universal
{
    Universal(const int* initCells, int rows, int columns);
    ~Universal();

    void evolve();

    Cell& at(int row, int column) const;
    void print(char aliveSymbol = 'o', char deadSymbol = '-') const;
    bool operator==(const Universal& rhs) const;

private:
    bool isOutOfBound(int row, int column) const;
    int countAliveNeighboursAt(int row, int column) const;

    void evolveCurrentGeneration();
    void createNextGeneration();
    Cell* createCells();
    void destroyCells();

    struct CellVisitor;
    void visitUniversal(CellVisitor&) const;

private:
    int row(int i) const;
    int column(int i) const;

private:
    int rows;
    int columns;
    Cell* cells;
}; 

#endif
