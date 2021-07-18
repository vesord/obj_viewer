#include "scop.h"
#include "scop_struct.h"
#include "events_private.h"
#include "parsing.h"
#include "buffers.h"
#include "calculations.h"
#include "initialization.h"
#include "libft.h"
#include <stdio.h>

void term_show_help()
{
	fprintf(stdout, "Program for viewing .obj 3D models.\n"
					"commands:\n"
					"h : show this help\n"
					"t texture_path : open texture\n"
					"o object_path : open .obj file\n");
}

void term_open_obj(const char *filename)
{
	t_scop		*scop;
	t_obj_data	*new_obj;

	scop = get_scop(NULL);
	new_obj = parse_obj_file(filename);
	if (new_obj)
	{
		// TODO: free old obj;
		scop->obj = new_obj;
		set_buf_data_from_obj(scop->obj, scop->bufs.vbo, scop->bufs.ibo); // Use after model change
		set_vao_for_obj(scop->obj, scop->bufs.vao, scop->bufs.vbo,
						scop->bufs.ibo); // Use after on model change
		init_transform(&scop->mat.transf);
		translate(&scop->mat.transf.rotate, &scop->obj->center_offset);
	}
}

void term_open_texture()
{
	fprintf(stdout, "Not implemented yet\n");
}

/*
**	supported commands:
**	h : help
**	t texture_path : open texture
**	o object_path : open object
*/
void exec_line(const char *line)
{
	if (!*line)
		return;
	if (line[0] == 'h' && line[1] == '\0')
		term_show_help();
	else if (line[0] == 'o' && line[1] == ' ')
		term_open_obj(line + 2);
	else if (line[0] == 't' && line[1] == ' ')
		term_open_texture(line);
}

void poll_terminal()
{
	char	*line;
	ssize_t	ret;

	ret = get_next_line(0, &line);
	if (ret <= 0)
		return ;
	exec_line(line);
	free(line);
}