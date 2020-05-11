/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_loop.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 00:25:16 by abaurens          #+#    #+#             */
/*   Updated: 2019/12/03 04:01:37 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "window.hpp"
#include "viewer.hpp"
#include "chunk.hpp"
#include "config.h"

extern "C" void	flush_buffer(int fd);

chunk	g_chunks[MEM_SIZE];

void	set_color(int pos, float r, float g, float b)
{
	g_chunks[pos].changeColor(r, g, b);
}

bool	escapeHandler(window &win)
{
	bool	quit(true);

	if (win.isGrabed() && !(quit = false))
		win.ungrab();
	if (win.isFullscreen() && !(quit = false))
		win.toggleFullscreen();
	if (quit)
		win.close();
	return (true);
}

bool	pHandler(window &win)
{
	if (win.isGrabed())
		win.ungrab();
	return (true);
}

bool	fullscreenHandler(window &win)
{
	win.toggleFullscreen();
	return (true);
}

bool	leftClicHandler(window &win)
{
	if (win.isGrabed())
		return (false);
	win.grab();
	return (true);
}

bool	closeHandler(window &win)
{
	win.close();
	return (true);
}

bool	loseFocus(window &win)
{
	win.ungrab();
	return (true);
}

bool	gainFocus(window &win)
{
	if (!win.isFullscreen())
		return (false);
	win.grab();
	return (true);
}

char	graphic_loop(t_vm *vm)
{
	window	win(vm, "Corewar", 1280, 720);

	win.addKeyHandler(SDLK_p, pHandler);
	win.addKeyHandler(SDLK_ESCAPE, escapeHandler);
	win.addKeyHandler(SDLK_F11, fullscreenHandler);
	win.addKeyHandler(SDLK_PAGEUP, fullscreenHandler);

	win.addWindowHandler(SDL_WINDOWEVENT_CLOSE, closeHandler);
	win.addWindowHandler(SDL_WINDOWEVENT_FOCUS_LOST, loseFocus);
	win.addWindowHandler(SDL_WINDOWEVENT_FOCUS_GAINED, gainFocus);

	win.addButtonHandler(SDL_BUTTON_LEFT, leftClicHandler);
	
	win.loop();
	flush_buffer(1);
	return (0);
}
