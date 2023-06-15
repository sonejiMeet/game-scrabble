#ifndef ENUM_H
#define ENUM_H

enum Orientation{
    VERTICAL,
    HORIZONTAL,
    NONE
};

enum Argument{
    SKIP_TURN,
    SWAP_TILES,
    CONTINUE_PLAYING
};

enum TurnAction{
    SHUFFLE_TILES,
    LOCK_IN_WORD,
    FORFEIT,
    CONTINUE
};

#endif