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
#include "update.h"
#include "draw.h"
#include "player.h"

ALLEGRO_EVENT_QUEUE * event_queue;

static void handle_display_close(ALLEGRO_EVENT * event)
{
    running = false;
}

static void handle_timer(ALLEGRO_EVENT * event)
{
    if (event->timer.source == fps_timer
        && al_is_event_queue_empty(event_queue))
    {
        update();
        draw();
    }
}

static void handle_key_down(ALLEGRO_EVENT * event)
{
    switch (event->keyboard.keycode)
    {
        case ALLEGRO_KEY_LEFT:
            player_begin_move_left();
            break;
        case ALLEGRO_KEY_RIGHT:
            player_begin_move_right();
            break;
        case ALLEGRO_KEY_SPACE:
            player_jump();
            break;
    }
}

static void handle_key_up(ALLEGRO_EVENT * event)
{
    switch (event->keyboard.keycode)
    {
        case ALLEGRO_KEY_LEFT:
            player_end_move_left();
            break;
        case ALLEGRO_KEY_RIGHT:
            player_end_move_right();
            break;
    }
}

void setup_events()
{
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
}

void cleanup_events()
{
    al_destroy_event_queue(event_queue);
}

void handle_event(ALLEGRO_EVENT * event)
{
    switch (event->type)
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            handle_display_close(event); break;
        case ALLEGRO_EVENT_TIMER:
            handle_timer(event); break;
        case ALLEGRO_EVENT_KEY_DOWN:
            handle_key_down(event); break;
        case ALLEGRO_EVENT_KEY_UP:
            handle_key_up(event); break;
    }
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

