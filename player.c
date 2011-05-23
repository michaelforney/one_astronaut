/* One Astronaut: player.c
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

#include "player.h"

#include <allegro5/allegro_image.h>

#include "one_astronaut.h"
#include "update.h"

static const double player_mass = 5;
static const double player_speed = 120;
static const double player_jump_power = 300;

struct player player;

static int player_ground_begin(cpArbiter * arb, cpSpace * space, void * data)
{
    player.on_ground = true;
    return true;
}

static void player_ground_separate(cpArbiter * arb, cpSpace * space, void * data)
{
    player.on_ground = false;
}

void setup_player()
{
    int width, height;

    player.sprite = al_load_bitmap("data/sprites/gerald.png");

    width = al_get_bitmap_width(player.sprite);
    height = al_get_bitmap_height(player.sprite);

    player.body = cpBodyNew(player_mass, INFINITY);
    player.shape = cpPolyShapeNew(player.body, 4,
        (cpVect[]) {
            cpv(-width / 2, -height / 2), cpv(-width / 2, height / 2),
            cpv(width / 2, height / 2), cpv(width / 2, -height / 2)
        },
        cpv(0, 0));

    player.body->p = cpv(al_get_display_width(display) / 2,
        al_get_display_height(display) / 2);
    player.shape->collision_type = PLAYER;

    cpSpaceAddCollisionHandler(&space, PLAYER, GROUND, &player_ground_begin,
        NULL, NULL, &player_ground_separate, NULL);

    cpSpaceAddBody(&space, player.body);
    cpSpaceAddShape(&space, player.shape);
}

void cleanup_player()
{
    cpShapeFree(player.shape);
    cpBodyFree(player.body);
    al_destroy_bitmap(player.sprite);
}

void player_begin_move_right()
{
    player.body->v.x += player_speed;
}

void player_end_move_right()
{
    player.body->v.x -= player_speed;
}

void player_begin_move_left()
{
    player.body->v.x -= player_speed;
}

void player_end_move_left()
{
    player.body->v.x += player_speed;
}

void player_jump()
{
    if (player.on_ground)
        player.body->v.y = -player_jump_power;
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

