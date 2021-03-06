#include "parsing_private.h"

#include <string.h>
#include <errno.h>

static void	realloc_if_need(t_buf *buf)
{
	static const size_t	initial_size = 1024;

	if (buf->data == NULL)
	{
		buf->data = malloc(buf->elem_size * initial_size);
		buf->buf_size = initial_size * buf->elem_size;
	}
	else if (buf->count == buf->buf_size / buf->elem_size)
	{
		buf->buf_size *= 2;
		buf->data = realloc(buf->data, buf->buf_size);
	}
	if (errno == EINVAL) {
		errno = 0;
	}
}

void		*get_value(t_buf *buf, size_t index)
{
	return ((char*)buf->data + index * buf->elem_size);
}

void		push_back(t_buf *buf, void *data)
{
	errno = 0;
	realloc_if_need(buf);
	if (!errno)
		memcpy(get_value(buf, buf->count++), data, buf->elem_size);
}

void		buf_init(t_buf *buf, size_t size)
{
	buf->data = NULL;
	buf->elem_size = size;
	buf->buf_size = 0;
	buf->count = 0;
}

void		buf_free(t_buf *buf)
{
	void *to_free;

	to_free = buf->data;
	buf_init(buf, buf->elem_size);
	free(to_free);
}
