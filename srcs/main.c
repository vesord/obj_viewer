#include "scop.h"
#include "shaders.h"
#include "parsing.h"
#include "events.h"
#include "buffers.h"
#include "initialization.h"
#include "display.h"

int main()
{
	t_scop scop;

	initialization(&scop);
	RegisterCallbacks(scop.window); // TODO: move to init

//	scop.obj = parse_obj_file("./models/teapot.obj");
//	scop.obj = parse_obj_file("./models/teapot2.obj");
	scop.obj = parse_obj_file("./models/42.obj");
//	scop.obj = parse_obj_file("./models/agalia.obj");
//	scop.obj = parse_obj_file("./models/agalia2.obj");
//	scop.obj = parse_obj_file("./models/vamp_female.obj");
//	scop.obj = parse_obj_file("./models/female.obj");
//	scop.obj = parse_obj_file("./models/cube3.obj");

	// BUFFERS;
	set_buf_data_from_obj(scop.obj, scop.bufs.vbo, scop.bufs.ibo); // Use after model change
	set_vao_for_obj(scop.obj, scop.bufs.vao, scop.bufs.vbo, scop.bufs.ibo); // Use after on model change

	// TODO: add help message
	display(scop);
	glfwTerminate();
	return 0;
}
