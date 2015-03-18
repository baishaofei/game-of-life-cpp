#include "gtest/gtest.h"
#include "Universal.h"
#include "Cell.h"
#include "Role.h"

namespace
{
    const int ROWS = 3;
    const int COLUMNS = 3;
    const int GIVEN_CELLS[ROWS * COLUMNS] = 
    {
        0, 1, 0,
        0, 1, 0,
        0, 1, 0
    }; 

    const int EXPECT_CELLS[ROWS * COLUMNS] = 
    {
        0, 0, 0,
        1, 1, 1,
        0, 0, 0
    }; 
}

TEST(UniversalTest, should_init_universal_given_a_cell_array_with_rows_and_columns)
{
    Universal u(GIVEN_CELLS, ROWS, COLUMNS);

    ASSERT_EQ(u.at(0, 0).status(), DEAD);
    ASSERT_EQ(u.at(0, 1).status(), ALIVE);
    ASSERT_EQ(u.at(0, 2).status(), DEAD);

    ASSERT_EQ(u.at(1, 0).status(), DEAD);
    ASSERT_EQ(u.at(1, 1).status(), ALIVE);
    ASSERT_EQ(u.at(1, 2).status(), DEAD);

    ASSERT_EQ(u.at(2, 0).status(), DEAD);
    ASSERT_EQ(u.at(2, 1).status(), ALIVE);
    ASSERT_EQ(u.at(2, 2).status(), DEAD);
}

TEST(UniversalTest, should_not_init_universal_given_a_abnormal_rows_or_columns)
{
    Universal u1(GIVEN_CELLS, 0, -1);
    Universal u2(GIVEN_CELLS, -1, 0);
}

TEST(UniversalTest, should_return_a_dead_cell_given_row_or_column_out_of_bound)
{
    Universal u(GIVEN_CELLS, ROWS , COLUMNS);

    ASSERT_EQ(u.at(ROWS, COLUMNS - 1).status(), DEAD);
    ASSERT_EQ(u.at(ROWS - 1, COLUMNS).status(), DEAD);
}

TEST(UniversalTest, should_print_universal_given_alive_symbol_and_dead_symbol)
{
    Universal u(GIVEN_CELLS, ROWS , COLUMNS);
    u.print('o', '-');
}

namespace
{
    void ASSERT_UNIVERSAL_EQ(int* GIVEN_CELLS, int* EXPECT_CELLS, int ROWS = 3, int COLUMNS = 3, int evolveNum = 1)
    {
        Universal expect(EXPECT_CELLS, ROWS , COLUMNS);

        Universal given(GIVEN_CELLS, ROWS , COLUMNS);
        for(int i = 0; i < evolveNum; ++i)
        {
            given.evolve();
        }

        ASSERT_EQ(given, expect);
    }
}

TEST(UniversalTest, should_given_cells_equals_expect_cells_given_no_neighbour_alive_cell)
{
    int GIVEN_CELLS[] = 
    {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0,
    };
    int EXPECT_CELLS[] = 
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
    };
    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS);
}

TEST(UniversalTest, should_given_cells_equals_expect_cells_given_a_alive_neighbour_cell)
{
    int GIVEN_CELLS[] = 
    {
        1, 0, 0,
        0, 1, 0,
        0, 0, 0,
    };
    int EXPECT_CELLS[] = 
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
    };
    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS);
}

TEST(UniversalTest, should_given_cells_equals_expect_cells_given_two_alive_neighbour_cell)
{
    int GIVEN_CELLS[] = 
    {
        1, 1, 0,
        0, 1, 0,
        0, 0, 0,
    };
    int EXPECT_CELLS[] = 
    {
        1, 1, 0,
        1, 1, 0,
        0, 0, 0,
    };
    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS);
}

TEST(UniversalTest, should_given_cells_equals_expect_cells_given_three_alive_neighbour_cell)
{
    int GIVEN_CELLS[] = 
    {
        1, 1, 1,
        0, 1, 0,
        0, 0, 0,
    };
    int EXPECT_CELLS[] = 
    {
        1, 1, 1,
        1, 1, 1,
        0, 0, 0,
    };
    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS);
}

TEST(UniversalTest, should_given_cells_equals_expect_cells_given_more_than_three_alive_neighbour_cell)
{
    int GIVEN_CELLS[] = 
    {
        1, 1, 1,
        1, 1, 0,
        0, 0, 0,
    };
    int EXPECT_CELLS[] = 
    {
        1, 0, 1,
        1, 0, 1,
        0, 0, 0,
    };
    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS);
}



TEST(UniversalTest, should_given_cells_equals_expect_cells_given_a_20_rows_and_20_column_cells)
{
    int GIVEN_CELLS[20 * 20] = 
    {
        0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1,
       1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
       1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0,
       0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0,
       1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1,
       1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1,
       0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
       1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0,
       1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0,
       1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
       1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1,
       0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
       1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
       1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
       0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
       0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
       1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
       1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0,
       1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    };

    int EXPECT_CELLS[] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    ASSERT_UNIVERSAL_EQ(GIVEN_CELLS,  EXPECT_CELLS, 20, 20, 54);
}
