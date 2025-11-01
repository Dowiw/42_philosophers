#include <sys/time.h>

/**
 * @brief Get miliseconds since epoch.
 *
 * @param time a struct from gettimeofday(2) check `man timeval`
 * @return miliseconds in long
 */
long	get_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
