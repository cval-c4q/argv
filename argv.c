/**
 * A small ISO C90 library to manage simple dynamic string vectors a-la argv
 * Author: <carlovalenti@ac.c4q.nyc>, public domain
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "argv.h"

#define    ARGV_ALLOC_GRAIN    0x0F  /* grow by multiples of this many entries */

/**
 *  @function initializates a new argv structure, empty save for an implicit trailing NULL
 *  @returns {struct argv*} pointer to newly allocated argv
 */
struct argv *argv_init()
{
	struct argv *newargv = (struct argv*)malloc(sizeof(struct argv));
	if (!newargv) return NULL;
	newargv->_vector_size = 1;
	newargv->argc = 0;
	newargv->argv = (char**)malloc(sizeof(char*) * newargv->_vector_size);
	newargv->argv[0] = NULL; /* end of vector sentinel */
	return newargv;
}

/**
 *  @function argv_find - does a linear lookup for entry in the argv
 *  @returns zero-based index of entry if found, -1 otherwise
 */
long argv_find(struct argv *argv, const char *string)
{
	char **p = argv ? argv->argv : NULL;
	assert(argv != NULL && argv->argv != NULL);
	if (string == NULL)
		return -1;
	while (*p != NULL) {
		if (strcmp(*p, string) == 0)
			return p - argv->argv;
		p++;
	}
	return -1;
}

/**
 * internal helper @function, manages dynamic memory growth for storage
 */
static void argv_grow(struct argv *argv, size_t elements)
{
	argv->_vector_size = (argv->_vector_size + elements + ARGV_ALLOC_GRAIN) & ~ ARGV_ALLOC_GRAIN;
	argv->argv = (char**)realloc(argv->argv, sizeof(char*) * argv->_vector_size);
}

/**
 *  @function appends entry to the back of string vector
 */
void argv_append(struct argv *argv, const char *string)
{
	assert(argv != NULL && argv->argv != NULL);
	if (argv->argc >= argv->_vector_size-1)
		argv_grow(argv, 1);
	argv->argv[argv->argc++] = strdup(string);
	argv->argv[argv->argc] = NULL;
}

/**
 *  @function cleans up resources used by entries as well as struct itself
 *  Caller must ensure to set handle to NULL to avoid double-free
 */
void argv_free(struct argv *argv)
{
	if (!argv)
		return;
	if (argv->argv) {
		char ** const tmp = argv->argv;
		while (argv->argc--)
			free(*(argv->argv++));
		free(tmp);
	}
	free(argv);
}

