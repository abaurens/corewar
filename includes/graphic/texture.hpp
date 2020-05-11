/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:07:00 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/22 04:52:04 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <vector>
# include <string>
# include <GL/glew.h>

GLuint	loadTexture(const char *file_path);
GLuint	loadTexture(const char *file_path, GLint minFilter, GLint magFilter);
GLuint	loadCubemap(std::vector<std::string> files);

#endif