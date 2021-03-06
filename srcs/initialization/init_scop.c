#include "scop.h"
#include "scop_struct.h"
#include "initialization_private.h"
#include "shaders.h"

static void	init_shaders(t_shaders *shaders)
{
	static const int	total_shaders_count = 1;
	char			*shader_vert_src;
	char			*shader_frag_src;

	shaders->count = total_shaders_count;
	shaders->arr = malloc(sizeof(*shaders->arr) * shaders->count);
	shader_vert_src = load_shader("./srcs/shaders/scop.vert.shader");
	shader_frag_src = load_shader("./srcs/shaders/scop.frag.shader");
	if (!shader_frag_src || !shader_vert_src || !shaders->arr)
		init_fail("Not enough memory");
	shaders->arr[0] = create_shader_program_vert_frag(shader_vert_src,
													  shader_frag_src);
	free(shader_vert_src);
	free(shader_frag_src);
	shaders->cur = shaders->arr[0];
	glUseProgram(shaders->cur);
	update_uniforms_locations(shaders);
	glUseProgram(0);
}

static void	init_buf_objects(t_buf_objects *bufs)
{
	glGenBuffers(1, &bufs->vbo);
	glGenBuffers(1, &bufs->ibo);
	glGenVertexArrays(1, &bufs->vao);
}

static void	init_keys(t_keys *keys)
{
	keys->right = 0;
	keys->left = 0;
	keys->back = 0;
	keys->forward = 0;
	keys->up = 0;
	keys->down = 0;
	keys->enable_rotation = 0;
	keys->draw_points = 0;
	keys->draw_lines = 0;
	keys->draw_triangles = 0;
	keys->render_triangles = 0;
	keys->render_texture = 0;
	keys->render_light = 0;
	keys->render_textured_light = 0;
	keys->move_decrease = 0;
	keys->move_increase = 0;
	keys->fill_color_decrease = 0;
	keys->fill_color_increase = 0;
}

static void	init_states(t_states *states)
{
	static const t_vec3f initial_fill_color = {.x = 0.1f, .y = 0.1f, .z = 0.1f};

	states->enable_rotation = 1;
	states->draw_type = GL_TRIANGLES;
	states->moving_step = 0.1f;
	states->shading_type = 0;
	states->fill_color = initial_fill_color;
}

static void	init_textures(t_scop *scop)
{
	scop->bmp = NULL;
	glGenTextures(1, &scop->texture_obj);
	glBindTexture (GL_TEXTURE_2D, scop->texture_obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void		init_scop(t_scop *scop)
{
	scop->obj = NULL;
	init_matrices(&scop->mat);
	init_shaders(&scop->shaders);
	init_buf_objects(&scop->bufs);
	init_keys(&scop->keys);
	init_states(&scop->state);
	init_textures(scop);
}