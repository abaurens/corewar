/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 01:50:25 by abaurens          #+#    #+#             */
/*   Updated: 2019/12/02 17:30:53 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include <map>
# include <SDL2/SDL.h>
# include "chunk.hpp"

# ifdef __cplusplus
extern "C" {
# endif

# include "config.h"
# include "vm.h"

# ifdef __cplusplus
}
# endif

extern chunk	g_chunks[MEM_SIZE];

# define TITLE	"Corewar"
# define WIDTH	1280
# define HEIGHT	720
# define TPS	60.0f
# define ANIM	0.08f

extern std::map<int, bool>	keys;
extern std::map<int, bool>	btns;

# ifdef __APPLE__

#  define KEY_FRONT		SDLK_w
#  define KEY_LEFT		SDLK_a

# else

#  define KEY_FRONT		SDLK_z
#  define KEY_LEFT		SDLK_q

# endif

#  define KEY_RIGHT		SDLK_d
#  define KEY_BACK		SDLK_s
#  define KEY_DOWN		SDLK_LSHIFT
#  define KEY_UP		SDLK_SPACE

#endif
