/**
 * @file Represents sprites and OAM.
 */
#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <gba_sprites.h>

#define NUM_SPRITES 128

#ifdef __cplusplus
extern "C" {
#endif

extern OBJATTR spriteAttrs[NUM_SPRITES];

void Sprites_Init();

void Sprites_SetPos(OBJATTR* const objAttr, const u16 posX, const u16 posY);

/**
 * Sets the size of the palette that the sprite uses.
 * 
 * @param objAttr Sprite to set the palette size.
 * @param size Size to set. Values are OBJ_16_COLOR or OBJ_256_COLOR.
 */
void Sprites_SetPaletteSize(OBJATTR* const objAttr, const u16 size);

void Sprites_SetSize(OBJATTR* const objAttr, const enum SPRITE_SIZECODE size);

void Sprites_SetTileIndex(OBJATTR* const objAttr, const u16 index);

inline bool Sprites_IsVFlipped(const OBJATTR* const objAttr)
{
    return (objAttr->attr1 & OBJ_VFLIP) != 0;
}

inline bool Sprites_IsHFlipped(const OBJATTR* const objAttr)
{
    return (objAttr->attr1 & OBJ_HFLIP) != 0;
}

inline void Sprites_SetVFlipped(OBJATTR* const objAttr, bool flipped)
{
    flipped ? (objAttr->attr1 |= OBJ_VFLIP) : (objAttr->attr1 &= ~OBJ_VFLIP);
}

inline void Sprites_SetHFlipped(OBJATTR* const objAttr, bool flipped)
{
    flipped ? (objAttr->attr1 |= OBJ_HFLIP) : (objAttr->attr1 &= ~OBJ_HFLIP);
}

void Sprites_Render();

#ifdef __cplusplus
}
#endif

#endif // _SPRITES_H_
