
A small ISO C90 library to manage simple dynamic string vectors a-la argv
=========================================================================

Author: <carlovalenti@ac.c4q.nyc>

Public domain.

Link against a libc with POSIX-defined call strdup(), which is fairly commonplace even though not strictly standard C.

Data structure
---------
```C
struct argv {
    char **argv;  // string vector, delimited by (char**)NULL
    size_t argc;  // currently held item count
    /**
     ... other memebers of this struct are internal to the implementation
     */
};
```

API
---
* ```struct argv *argv_init()```

  Initialize a brand new vector and return associated pointer handle
  
* ```long argv_find(struct argv *vec, const char *string)```

  Return position of first occurrence of argv in vector, -1 otherwise

* ```void argv_append(struct argv *vec, const char *string)```

  Copy string argument (by value, [strdup](http://man7.org/linux/man-pages/man3/strdup.3.html)) into argv

* ```void argv_free(struct argv *vec)```

  Free up dynamically allocated resources, invalidates handle
