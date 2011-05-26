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

#include <stdio.h>
#include <math.h>
#include <allegro5/allegro_image.h>

#include "one_astronaut.h"
#include "update.h"

static const double player_mass = 5;
static const double player_speed = 120;
static const double player_jump_power = 400;

struct player player;

enum direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

static enum direction vector_direction(cpVect v)
{
    if (v.x > v.y)
        if (v.y > -v.x)
            return RIGHT;
        else
            return UP;
    else
        if (v.y > -v.x)
            return DOWN;
        else
            return LEFT;
}

static char * direction_string(enum direction direction)
{
    static char string[256];

    switch (direction)
    {
        case LEFT: sprintf(string, "LEFT"); break;
        case RIGHT: sprintf(string, "RIGHT"); break;
        case UP: sprintf(string, "UP"); break;
        case DOWN: sprintf(string, "DOWN"); break;
    }

    return string;
}

static int player_ground_begin(cpArbiter * arb, cpSpace * space, void * data)
{
    cpContactPointSet set;
    enum direction direction;
    cpShape * player_shape, * ground_shape;

    printf("ground_begin\n");

    cpArbiterGetShapes(arb, &player_shape, &ground_shape);
    set = cpArbiterGetContactPointSet(arb);
    direction = vector_direction(cpvneg(set.points[0].normal));

    if (direction != DOWN)
        return false;

    player.ground_contact[DOWN] = ground_shape;
    player.body->p.y += set.points[0].dist + 0.001;
    player.body->v.y = 0.0;

    return false;
}

static void player_ground_separate(cpArbiter * arb, cpSpace * space, void * data)
{
    printf("ground_separate\n");

    player.ground_contact[DOWN] = NULL;
}

static int player_wall_begin(cpArbiter * arb, cpSpace * space, void * data)
{
    cpContactPointSet set;
    enum direction direction;
    cpShape * player_shape, * wall_shape;
    int index;

    printf("wall_begin\n");

    cpArbiterGetShapes(arb, &player_shape, &wall_shape);
    set = cpArbiterGetContactPointSet(arb);
    direction = vector_direction(cpvneg(set.points[0].normal));

    if (direction == UP || direction == DOWN)
        return false;

    for (index = 0; index < set.count; ++index)
    {
        printf("\tset.points[%u].point: %s\n", index,
            cpvstr(set.points[index].point));
        printf("\tset.points[%u].normal: %s\n", index,
            cpvstr(set.points[index].normal));
    }

    player.ground_contact[direction] = wall_shape;

    return false;
}

static void player_wall_separate(cpArbiter * arb, cpSpace * space, void * data)
{
    cpShape * player_shape, * wall_shape;

    printf("wall_separate\n");

    cpArbiterGetShapes(arb, &player_shape, &wall_shape);

    if (player.ground_contact[LEFT] == wall_shape)
        player.ground_contact[LEFT] = NULL;
    else if (player.ground_contact[RIGHT] == wall_shape)
        player.ground_contact[RIGHT] = NULL;
}

static void player_velocity(cpBody * body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    /* Ignore gravity if player is contacting the ground. */
    if (player.ground_contact[DOWN])
        cpBodyUpdateVelocityDefault(body, cpvzero, damping, dt);
    else
        cpBodyUpdateVelocityDefault(body, gravity, damping, dt);
}

static void player_position(cpBody * body, cpFloat dt)
{
    cpVect v = body->v;

    if (player.movement == MOVEMENT_RIGHT)
        v.x += player_speed;
    else if (player.movement == MOVEMENT_LEFT)
        v.x -= player_speed;

    if ((v.x > 0.0 && player.ground_contact[RIGHT])
        || (v.x < 0.0 && player.ground_contact[LEFT]))
    {
        v.x = 0;
    }

    if ((v.y < 0.0 && player.ground_contact[UP])
        || (v.y > 0.0 && player.ground_contact[DOWN]))
    {
        v.y = 0;
    }

    body->p = cpvadd(body->p, cpvmult(v, dt));
}

void setup_player()
{
    int width, height;

    player.sprite = al_load_bitmap("data/sprites/gerald.png");

    width = al_get_bitmap_width(player.sprite);
    height = al_get_bitmap_height(player.sprite);

    player.body = cpBodyNew(player_mass, INFINITY);
    player.body->p = cpv(al_get_display_width(display) / 2,
        al_get_display_height(display) / 2);
    player.body->velocity_func = &player_velocity;
    player.body->position_func = &player_position;

    player.shape = cpPolyShapeNew(player.body, 4,
        (cpVect[]) {
            cpv(-width / 2, -height / 2), cpv(-width / 2, height / 2),
            cpv(width / 2, height / 2), cpv(width / 2, -height / 2)
        },
        cpv(0, 0));
    player.shape->collision_type = PLAYER;

    cpSpaceAddCollisionHandler(&space, PLAYER, GROUND, &player_ground_begin,
        NULL, NULL, &player_ground_separate, NULL);
    cpSpaceAddCollisionHandler(&space, PLAYER, WALL, &player_wall_begin,
        NULL, NULL, &player_wall_separate, NULL);

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
    player.movement = MOVEMENT_RIGHT;
}

void player_end_move_right()
{
    if (player.movement == MOVEMENT_RIGHT)
        player.movement = MOVEMENT_STILL;
}

void player_begin_move_left()
{
    player.movement = MOVEMENT_LEFT;
}

void player_end_move_left()
{
    if (player.movement == MOVEMENT_LEFT)
        player.movement = MOVEMENT_STILL;
}

void player_jump()
{
    if (player.ground_contact[DOWN] && !player.ground_contact[UP])
        player.body->v.y = -player_jump_power;
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

