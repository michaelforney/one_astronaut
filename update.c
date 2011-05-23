/* One Astronaut: update.c
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

#include "update.h"
#include "one_astronaut.h"

#include <allegro5/allegro.h>

static double delta_time = 0.0;

static void update_fps()
{
    static double time = 0.0;
    double new_time = al_get_time();
    delta_time = new_time - time;
    fps = 1.0 / delta_time;
    time = new_time;
}

void update()
{
    update_fps();

    cpSpaceStep(&space, delta_time);
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

