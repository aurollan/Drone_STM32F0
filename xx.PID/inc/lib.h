#ifndef __LIB_H__
#define __LIB_H__

#include "itm.h"
#include "stm32f303xc.h"
#include <sys/stat.h>

int		_isatty(int file);
int		_fstat(int file, struct stat *st);
int		_lseek(int file, int ptr, int dir);
int		_read(int file, char *ptr, int len);
int		_close(int fd);
caddr_t _sbrk(int incr);

#endif
