/* One Astronaut: events.c
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

#include "events.h"
#include "one_astronaut.h"
#include "draw.h"

typedef void (* event_handler_t)(ALLEGRO_EVENT * event);

void handle_display_close(ALLEGRO_EVENT * event)
{
    running = false;
}

void handle_timer(ALLEGRO_EVENT * event)
{
    if (event->timer.source == fps_timer
        && al_is_event_queue_empty(event_queue))
    {
        draw();
    }
}

void handle_event(ALLEGRO_EVENT * event)
{
    switch (event->type)
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            handle_display_close(event); break;
        case ALLEGRO_EVENT_TIMER:
            handle_timer(event); break;
    }
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

