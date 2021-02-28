
#include "Player.h"

#include <gba.h>

#include "../data/charsprites.h"

void Player_Init(Player* const player)
{
    dmaCopy(charspritesPal, SPRITE_PALETTE, charspritesPalLen);
    dmaCopy(charspritesTiles, SPRITE_GFX, charspritesTilesLen);

    player->sprite = spriteAttrs;
    player->curFrame = 0;
    player->numFrames = 4;
    player->curTick = 0;
    player->ticksPerFrame = 5;
    player->posX = 0;
    player->posY = 0;
    player->width = 16;
    player->height = 16;

    Sprites_SetPaletteSize(player->sprite, OBJ_256_COLOR);
    Sprites_SetSize(player->sprite, Sprite_16x16);
}

void Player_Update(Player* const player)
{
    const u16 keysH = keysHeld();

    if (keysH & KEY_RIGHT)
    {
        //++player->posX;
        Sprites_SetHFlipped(player->sprite, false);
    }
    else if (keysH & KEY_LEFT)
    {
        //--player->posX;
        Sprites_SetHFlipped(player->sprite, true);
    }

    // if (keysH & KEY_UP)
    //     --player->posY;
    // else if (keysH & KEY_DOWN)
    //     ++player->posY;

    // Sprites_SetPos(player->sprite, player->posX, player->posY);

    ++player->curTick;
    if (player->curTick >= player->ticksPerFrame)
    {
        player->curTick = 0;
        ++player->curFrame;
        if (player->curFrame >= player->numFrames)
            player->curFrame = 0;
    }

    Sprites_SetTileIndex(player->sprite, player->curFrame * 8);
}
