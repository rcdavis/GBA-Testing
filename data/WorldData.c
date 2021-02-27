
#include "WorldData.h"

#include "BlockTiles.h"
#include "SMB_Test_World.h"

const WorldData WORLD_1_DATA = {
    {
        {
            SMB_Test_World_Map,
            SMB_TEST_WORLD_LENGTH * sizeof(unsigned short),
            4,
            0,
            256,
            256,
            TEXTBG_SIZE_256x256,
            0
        },
        {
            Tile_Layer_2,
            SMB_TEST_WORLD_LENGTH * sizeof(unsigned short),
            8,
            0,
            256,
            256,
            TEXTBG_SIZE_256x256,
            1
        }
    },
    2,
    256,
    256
};
