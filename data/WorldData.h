
#ifndef _WORLD_DATA_H_
#define _WORLD_DATA_H_

#include <gba_video.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _TileLayerData {
    const u16* const tileMapData;
    const u16 tileMapDataLen;
    const u16 mapIndex;
    const u16 tileIndex;
    const u16 mapWidth;
    const u16 mapHeight;
    const u16 mapSize;
    const u16 priority;
} TileLayerData;

typedef struct _WorldData {
    const TileLayerData tileLayerData[2];
    const u32 numLayers;
    const u32 width, height;
    const u16* const tileSetData;
    const u16* const tilePaletteData;
    const u32 tileSetDataLen;
    const u32 tilePaletteDataLen;
    const u16 tileSetIndex;
} WorldData;

extern const WorldData WORLD_1_DATA;

#ifdef __cplusplus
}
#endif

#endif // _WORLD_DATA_H_
