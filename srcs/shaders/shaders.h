#ifndef SCOP_SHADERS_H
#define SCOP_SHADERS_H

#include "scop.h"
#include "scop_struct.h"

GLuint create_shader_program_vert_frag(const char *vert_shader_src,
									   const char *frag_shader_src);
void	update_uniforms_locations(t_shaders *shaders);

#endif
