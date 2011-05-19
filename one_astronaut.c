/* One Astronaut: one_astronaut.c
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

#include "one_astronaut.h"

ALLEGRO_DISPLAY * display;
ALLEGRO_EVENT_QUEUE * event_queue;

bool running = true;

void setup()
{
    al_set_app_name("one_astronaut");
    al_set_org_name("one_astronaut");

    al_init();

    event_queue = al_create_event_queue();
    display = al_create_display(800, 600);
}

void cleanup()
{
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

void run()
{
    ALLEGRO_EVENT event;

    while (running)
    {
        al_wait_for_event(event_queue, &event);
    }
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

