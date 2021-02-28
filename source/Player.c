
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
    player->state = PLAYER_IDLE;

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
        Player_ChangeState(player, PLAYER_RUNNING);
    }
    else if (keysH & KEY_LEFT)
    {
        //--player->posX;
        Sprites_SetHFlipped(player->sprite, true);
        Player_ChangeState(player, PLAYER_RUNNING);
    }
    else
    {
        Player_ChangeState(player, PLAYER_IDLE);
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
        if (player->curFrame >= Player_GetNumFrames(player))
            player->curFrame = 0;
    }

    Sprites_SetTileIndex(player->sprite, Player_GetCurrentFrame(player));
}

u16 Player_GetNumFrames(const Player* const player)
{
    if (player->state == PLAYER_RUNNING)
    {
        return 4;
    }

    return 4;
}

u16 Player_GetCurrentFrame(const Player* const player)
{
    if (player->state == PLAYER_RUNNING)
    {
        return (player->curFrame + 4) * 8;
    }

    return player->curFrame * 8;
}

void Player_ChangeState(Player* const player, const PlayerState state)
{
    if (player->state != state)
    {
        player->curFrame = 0;
        player->curTick = 0;
    }
    player->state = state;
}
