
#include "Sprites.h"

#include <gba_dma.h>

OBJATTR spriteAttrs[NUM_SPRITES];

void Sprites_Init()
{
    for (int i = 0; i < NUM_SPRITES; ++i)
    {
        spriteAttrs[i].attr0 = 0;
        spriteAttrs[i].attr1 = 0;
        spriteAttrs[i].attr2 = 0;
        spriteAttrs[i].dummy = 0;
    }
}

void Sprites_SetPos(OBJATTR* const objAttr, const u16 posX, const u16 posY)
{
    objAttr->attr0 &= ~(0x00FF);
    objAttr->attr1 &= ~(0x01FF);

    objAttr->attr0 |= OBJ_Y(posY);
    objAttr->attr1 |= OBJ_X(posX);
}

/**
 * Sets the size of the palette that the sprite uses.
 * 
 * @param objAttr Sprite to set the palette size.
 * @param size Size to set. Values are OBJ_16_COLOR or OBJ_256_COLOR.
 */
void Sprites_SetPaletteSize(OBJATTR* const objAttr, const u16 size)
{
    objAttr->attr0 &= ~BIT(13);
    objAttr->attr0 |= size;
}

void Sprites_SetSize(OBJATTR* const objAttr, const enum SPRITE_SIZECODE size)
{
    objAttr->attr1 &= ~OBJ_SIZE(0xF);
    objAttr->attr1 |= OBJ_SIZE(size);
}

void Sprites_SetTileIndex(OBJATTR* const objAttr, const u16 index)
{
    objAttr->attr2 &= ~0x03FF;
    objAttr->attr2 |= OBJ_CHAR(index);
}

void Sprites_Render()
{
    dmaCopy(spriteAttrs, OAM, sizeof(spriteAttrs));
}
