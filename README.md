
A small ISO C99 library to manage simple dynamic string vectors a-la argv
=========================================================================

Author: <carlovalenti@ac.c4q.nyc>
Public domain.



Interface
---------

* struct argv *argv_init()
* long argv_find(struct argv *vec, const char *string)
* void argv_append(struct argv *vec, const char *string)
* void argv_free(struct argv *vec);

