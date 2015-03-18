#include "gtest/gtest.h"
#include "Cell.h"

struct CellTest : testing::Test
{
protected:
    void ASSERT_CELL_WITH(int* neighbours, int len, CellStatus fromStatus,  CellStatus toStatus)
    {
        for(int i = 0; i < len; ++i)
        {
            fromStatus ? cell.live()  : cell.die();
            cell.evolveCurrentGeneration(neighbours[i]);
            cell.createNextGeneration();
            ASSERT_EQ(cell.status(), toStatus);
        }
    }

protected:
    Cell cell;
};

TEST_F(CellTest, should_not_be_alive_when_a_cell_be_created)
{
    ASSERT_EQ(cell.status(), DEAD);
}

TEST_F(CellTest, should_a_dead_cell_becomes_to_alive_cell)
{
    cell.live();
    ASSERT_EQ(cell.status(), ALIVE);
}

TEST_F(CellTest, should_a_alive_cell_become_to_dead_cell)
{
    cell.live();
    cell.die();
    ASSERT_EQ(cell.status(), DEAD);
}

TEST_F(CellTest, should_a_alive_cell_dies_in_next_generation_when_alive_neighbous_fewer_than_two)
{
    int neighbours[] = {0, 1};
    ASSERT_CELL_WITH(neighbours,  2, ALIVE, DEAD);
}

TEST_F(CellTest, should_a_alive_cell_remain_lives_in_next_generation_when_alive_neighbous_equals_two_or_three)
{
    int neighbours[] = {2, 3};
    ASSERT_CELL_WITH(neighbours,  2, ALIVE, ALIVE);
}

TEST_F(CellTest, should_a_alive_cell_dies_in_next_generation_when_alive_neighbous_more_than_three)
{
    int neighbours[] = {4,5,6,7,8};
    ASSERT_CELL_WITH(neighbours,  5, ALIVE, DEAD);
}

TEST_F(CellTest, should_a_dead_cell_lives_in_next_generation_when_live_neighbous_equals_three)
{
     int neighbours[] = {3};
    ASSERT_CELL_WITH(neighbours,  1, DEAD, ALIVE);
}

TEST_F(CellTest, should_a_dead_cell_remain_dies_in_next_generation_when_live_neighbous_fewer_than_three_or_more_than_three)
{
    int neighbours[] = {0, 1, 2, 4, 5, 6, 7, 8};
    ASSERT_CELL_WITH(neighbours,  8, DEAD, DEAD);
}


