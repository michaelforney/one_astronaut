/* One Astronaut: events.h
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

#ifndef ONE_ASTRONAUT_EVENTS_H
#define ONE_ASTRONAUT_EVENTS_H

#include <allegro5/allegro.h>

extern ALLEGRO_EVENT_QUEUE * event_queue;

/**
 * Setup the event queue and anything else necessary for processing events.
 */
void setup_events();

/**
 * Perform all necessary cleanup related to processing events.
 */
void cleanup_events();

/**
 * Handle the given event, calling the appropriate event handler.
 */
void handle_event(ALLEGRO_EVENT * event);

#endif

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

