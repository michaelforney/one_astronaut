/* One Astronaut: player.h
 *
 * Copyright (c) 2011 Michael Forney <mforney@mforney.org>
 *
 * This file is a part of One Astronaut.
 *
 * One Astronaut is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2, as published by
 * the Free Software Foundation.
 *
 * One Astronaut is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * One Astronaut.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ONE_ASTRONAUT_PLAYER_H
#define ONE_ASTRONAUT_PLAYER_H

#include <allegro5/allegro.h>
#include <chipmunk/chipmunk.h>

struct player
{
    ALLEGRO_BITMAP * sprite;
    cpBody * body;
    cpShape * shape;

    enum {
        MOVEMENT_STILL,
        MOVEMENT_RIGHT,
        MOVEMENT_LEFT
    } movement;

    cpShape * ground_contact[4];
};

extern struct player player;

/**
 * Create the player object.
 */
void setup_player();

/**
 * Clean up the player object.
 */
void cleanup_player();

/* Player Movement */

/**
 * Cause the player to begin moving right.
 */
void player_begin_move_right();

/**
 * Cause the player to stop moving right.
 */
void player_end_move_right();

/**
 * Cause the player to begin moving left.
 */
void player_begin_move_left();

/**
 * Cause the player to stop moving left.
 */
void player_end_move_left();

/**
 * Cause the player to jump in the air.
 */
void player_jump();

#endif

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

