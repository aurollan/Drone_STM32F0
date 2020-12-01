#include "lib.h"

caddr_t _sbrk(int incr)
{
  extern char _end;		/* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
  uint32_t stack_ptr;

  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  
  stack_ptr = __get_MSP();

  if (((uint32_t)(heap_end + incr)) > stack_ptr)
  {
    _write(1, "Heap and stack collision\n", 25);
    /* abort (); */
	while (1) {};
  }
  heap_end += incr;
  return ((caddr_t) prev_heap_end);
}

int _close(int fd)
{
	(void)fd;
	return (-1);
}

int _read(int file, char *ptr, int len)
{
	(void)file;
	(void)ptr;
	(void)len;
	return (0);
}

int _lseek(int file, int ptr, int dir)
{
	(void)file;
	(void)ptr;
	(void)dir;
	return (0);
}

int _fstat(int file, struct stat *st)
{
	(void)file;
	st->st_mode = S_IFCHR;
	return (0);
}

int _isatty(int file)
{
	(void)file;
	return (1);
}
