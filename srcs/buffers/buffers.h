#ifndef BUFFERS_H
# define BUFFERS_H

void set_buf_data_from_obj(t_obj_data *obj, GLuint vbo, GLuint ibo);
void set_vao_for_obj(t_obj_data *obj, GLuint vao, GLuint vbo, GLuint ibo);

#endif
