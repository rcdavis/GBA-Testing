#include <gba.h>
#include <stdio.h>
#include <stdlib.h>

#include "Sprites.h"
#include "Player.h"
#include "World.h"

#include "../data/BlockTiles.h"
#include "../data/WorldData.h"

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

        World_Render(world);
        Player_Render(player);
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

    World_Init(world, &WORLD_1_DATA, BlockTilesTiles, BlockTilesPal,
        BlockTilesTilesLen, BlockTilesPalLen);
}
