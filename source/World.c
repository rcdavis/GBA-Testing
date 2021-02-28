
#include "World.h"

#include <gba_dma.h>
#include <gba_input.h>

void World_Init(World* const world, const WorldData* const worldData)
{
    dmaCopy(worldData->tilePaletteData, BG_PALETTE, worldData->tilePaletteDataLen);
    dmaCopy(worldData->tileSetData, TILE_BASE_ADR(worldData->tileSetIndex), worldData->tileSetDataLen << 1);

    for (int i = 0; i < worldData->numLayers; ++i)
    {
        const TileLayerData* const tileLayerData = worldData->tileLayerData + i;
        dmaCopy(tileLayerData->tileMapData, MAP_BASE_ADR(tileLayerData->mapIndex), tileLayerData->tileMapDataLen);
        (*(BGCTRL + i)) = TILE_BASE(tileLayerData->tileIndex) | MAP_BASE(tileLayerData->mapIndex) |
            BG_PRIORITY(tileLayerData->priority) | BG_256_COLOR | tileLayerData->mapSize;
    }

    world->posX = 0;
    world->posY = 0;
    world->width = worldData->width;
    world->height = worldData->height;
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
}

void World_Render(const World* const world)
{
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
