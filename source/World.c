
#include "World.h"

#include <gba_dma.h>
#include <gba_input.h>

void World_Init(
    World* const world,
    const u16* const tileMap,
    const u16* const tileSet,
    const u16* const palette,
    const u32 mapLen,
    const u32 tileSetLen,
    const u32 paletteLen)
{
    dmaCopy(palette, BG_PALETTE, paletteLen);
    dmaCopy(tileMap, MAP_BASE_ADR(4), mapLen << 1);
    dmaCopy(tileSet, TILE_BASE_ADR(0), tileSetLen << 1);

    REG_BG0CNT = TILE_BASE(0) | MAP_BASE(4) | BG_PRIORITY(0) | BG_256_COLOR | TEXTBG_SIZE_256x256;

    world->mapLen = mapLen;
    world->tileSetLen = tileSetLen;
    world->posX = 0;
    world->posY = 0;
    world->width = 256;
    world->height = 256;
}

void World_Update(World* const world, Player* const player)
{
    const u16 keysH = keysHeld();

    if (keysH & KEY_RIGHT)
    {
        if (world->posX + SCREEN_WIDTH < world->width)
            ++world->posX;
    }
    else if (keysH & KEY_LEFT)
    {
        if (world->posX > 0)
            --world->posX;
    }

    if (keysH & KEY_UP)
    {
        if (world->posY > 0)
            --world->posY;
    }
    else if (keysH & KEY_DOWN)
    {
        if (world->posY + SCREEN_HEIGHT < world->height)
            ++world->posY;
    }

    REG_BG0HOFS = world->posX;
    REG_BG0VOFS = world->posY;
}

/**
 * Sets the size of the map for the background.
 * 
 * @param world World representing the background.
 * @param size Size to set. Valid values are:
 *      TEXTBG_SIZE_256x256,
 *      TEXTBG_SIZE_512x256,
 *      TEXTBG_SIZE_256x512,
 *      TEXTBG_SIZE_512x512,
 *      ROTBG_SIZE_128x128,
 *      ROTBG_SIZE_256x256,
 *      ROTBG_SIZE_512x512,
 *      ROTBG_SIZE_1024x1024
 */
void World_SetMapSize(World* const world, u32 size)
{
    REG_BG0CNT &= ~BG_SIZE(3);
    REG_BG0CNT |= size;
}
