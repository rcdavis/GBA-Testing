#include <gba.h>
#include <stdio.h>
#include <stdlib.h>

#include "Sprites.h"
#include "Player.h"
#include "World.h"

#include "../data/SMB_Test_World.h"
#include "../data/BlockTiles.h"

Player* const player = (Player*)EWRAM;
World* const world = (World*)(player + 1);

void Init();

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main()
{
    Init();

    while (true)
    {
        scanKeys();

        Player_Update(player);

        World_Update(world, player);

        VBlankIntrWait();

        Sprites_Render();
    }
}

void Init()
{
    // the vblank interrupt must be enabled for VBlankIntrWait() to work
    // since the default dispatcher handles the bios flags no vblank handler
    // is required
    irqInit();
    irqEnable(IRQ_VBLANK);

    //consoleDemoInit();

    SetMode(MODE_0 | BG0_ENABLE | BG1_ENABLE | OBJ_ENABLE | OBJ_1D_MAP);

    Sprites_Init();

    Player_Init(player);
    Player_SetVFlipped(player, true);

    World_Init(world, SMB_Test_World_Map, BlockTilesTiles, BlockTilesPal,
        SMB_TEST_WORLD_LENGTH, BlockTilesTilesLen, BlockTilesPalLen);

    dmaCopy(Tile_Layer_2, MAP_BASE_ADR(8), SMB_TEST_WORLD_LENGTH << 1);
    REG_BG1CNT = TILE_BASE(0) | MAP_BASE(8) | BG_PRIORITY(1) | BG_256_COLOR | TEXTBG_SIZE_256x256;
}
