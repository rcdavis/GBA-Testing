
#ifndef _WORLD_H_
#define _WORLD_H_

#include <gba_video.h>
#include "Player.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Represents a tile map background.
 */
typedef struct _World {
    const u16* tileMap;
    const u16* tileSet;
    u32 mapLen, tileSetLen;
    u16 posX, posY;
    u32 width, height;
} World;

void World_Init(
    World* const world,
    const u16* const tileMap,
    const u16* const tileSet,
    const u16* const palette,
    const u32 mapLen,
    const u32 tileSetLen,
    const u32 paletteLen);

void World_Update(World* const world, Player* const player);

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
void World_SetMapSize(World* const world, u32 size);

#ifdef __cplusplus
}
#endif

#endif // _WORLD_H_
