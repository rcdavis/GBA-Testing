
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprites.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _PlayerState {
    PLAYER_IDLE,
    PLAYER_RUNNING
} PlayerState;

typedef struct _Player {
    OBJATTR* sprite;
    u16 curFrame, numFrames;
    u16 curTick, ticksPerFrame;
    u16 posX, posY;
    u16 width, height;
    PlayerState state;
} Player;

void Player_Init(Player* const player);

void Player_Update(Player* const player);

inline bool Player_IsVFlipped(const Player* const player)
{
    return Sprites_IsVFlipped(player->sprite);
}

inline bool Player_IsHFlipped(const Player* const player)
{
    return Sprites_IsHFlipped(player->sprite);
}

inline void Player_SetVFlipped(Player* const player, bool flipped)
{
    Sprites_SetVFlipped(player->sprite, flipped);
}

inline void Player_SetHFlipped(Player* const player, bool flipped)
{
    Sprites_SetHFlipped(player->sprite, flipped);
}

u16 Player_GetNumFrames(const Player* const player);

u16 Player_GetCurrentFrame(const Player* const player);

void Player_ChangeState(Player* const player, const PlayerState state);

#ifdef __cplusplus
}
#endif

#endif // _PLAYER_H_
