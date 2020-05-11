/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:07:56 by abaurens          #+#    #+#             */
/*   Updated: 2019/11/22 04:52:01 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "texture.hpp"

GLenum getInternalFormat(SDL_Surface *s)
{
	char	i = (s->format->BytesPerPixel - 3);

	/*if (s->format->BytesPerPixel == 3)
		return (GL_RGB);
	else if (s->format->BytesPerPixel == 4)
		return (GL_RGBA);
	else
		return (0);*/
	if (i <= 1)
		return (GL_RGB + i);
	return (0);
}

GLenum getFormat(SDL_Surface *s)
{
	char	i = (s->format->BytesPerPixel - 3);

	/*if (s->format->BytesPerPixel == 3)
		return (s->format->Rmask == 0xff ? GL_RGB : GL_BGR);
	else
		return (s->format->Rmask == 0xff ? GL_RGBA : GL_BGRA);*/
	return (((s->format->Rmask == 0xff) ? GL_RGB : GL_BGR) + i);
}

SDL_Surface	*flipImage(SDL_Surface *src)
{
	int				dataSize;
	unsigned char	*pixSrc;

	pixSrc = (unsigned char *)src->pixels;
	dataSize = src->w * src->format->BytesPerPixel;
	for (int y = 0; y < src->h / 2; ++y)
		for (int x = 0; x < dataSize; ++x)
			std::swap(pixSrc[(src->h - 1 - y) * dataSize + x], pixSrc[y * dataSize + x]);
	return (src);
}

GLuint loadTexture(const char *file_path, GLint minFilter, GLint magFilter)
{
	SDL_Surface	*surface(nullptr);

	GLuint		textureId(0);
	GLenum		internal(0);
	GLenum		format(0);

	if (!(surface = IMG_Load(file_path)))
	{
		std::cout << "error: " << SDL_GetError() << std::endl;
		return (0);
	}
	flipImage(surface);
	if (!(internal = getInternalFormat(surface)))
	{
		std::cout << "error: unknown image format" << std::endl;
		SDL_FreeSurface(surface);
		return (0);
	}
	format = getFormat(surface);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, internal, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surface);
	return (textureId);
}

GLuint	loadTexture(const char *file_path)
{
	return (loadTexture(file_path, GL_LINEAR, GL_NEAREST));
}

GLuint	loadCubemap(std::vector<std::string> files)
{
	GLuint		textureId;
	GLenum		internal(0);
	GLenum		format(0);
	SDL_Surface	*cur;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	
	for (GLuint i = 0; i < files.size(); ++i)
	{
		if (!(cur = IMG_Load(files[i].c_str())))
		{
			std::cout << "error: " << SDL_GetError() << std::endl;
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glDeleteTextures(1, &textureId);
			return (0);
		}
		if (!(internal = getInternalFormat(cur)))
		{
			std::cout << "error: unknown image format" << std::endl;
			SDL_FreeSurface(cur);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glDeleteTextures(1, &textureId);
			return (0);
		}
		format = getFormat(cur);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal, cur->w, cur->h, 0, format, GL_UNSIGNED_BYTE, cur->pixels);
		SDL_FreeSurface(cur);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return (textureId);
}
