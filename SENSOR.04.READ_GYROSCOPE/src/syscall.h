#pragma once

#include "stm32f0xx.h"
#include <sys/stat.h>

int		_isatty(int file);
int		_fstat(int file, struct stat *st);
int		_lseek(int file, int ptr, int dir);
int		_read(int file, char *ptr, int len);
int		_close(int fd);
caddr_t _sbrk(int incr);

