/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 01:50:25 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/14 08:50:02 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include <map>

# ifdef __cplusplus
extern "C" {
# endif

# include "vm.h"

# ifdef __cplusplus
}
# endif

# define TITLE	"Corewar"
# define WIDTH	1280
# define HEIGHT	720

extern std::map<int, bool>	keys;
extern std::map<int, bool>	btns;

#endif
