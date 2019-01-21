[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e1e44c7bbbd4466dad51db05df391ffc)](https://www.codacy.com/app/cval-c4q/argv?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=cval-c4q/argv&amp;utm_campaign=Badge_Grade)

A small ISO C90 library to manage simple dynamic string vectors a-la argv
=========================================================================

Author: <carlovalenti@ac.c4q.nyc>

Public domain.

Link against a libc with system-supplied library routine strdup(), which is fairly commonplace even though not strictly standard C.

Type naming convention
----------------------
```C
typedef const char *  TStr;
typedef strut argv    TVec;
```

Methods (API)
-------------
* ```TVec *argv_init()```

  Initialize a brand new vector and return associated pointer handle
 
* ```void argv_free(TVec *vec)```

  Free up dynamically allocated resources, invalidates handle
 
* ```long argv_find(TVec *haystack, TStr needle)```

  Return zero-based index of first occurrence of needle in haystack, -1 otherwise.
  This performs a simple linear search.

* ```void argv_append(TVec *vec, TStr entry)```

  Copy string argument (by value, [strdup](http://man7.org/linux/man-pages/man3/strdup.3.html)) into argv

Data members (ABI)
------------
* ```TVec.argv``` of type ```*TStr```, aka ```const char**```

  a ```NULL```-terminated string ector

* ```TVec.argc```, size of argv, number of elements (not including implicit NULL entry)

Characteristics
---------------
* Vector is append-only, no direct method of removing elements

* Methods are re-entrant, but not thread-safe, explicit synchornization of access to shared argv is left up to the user

* Only simple linear search is provided as a shortcut, other methods of search with assumptions about the relative order of elements, or different interpretations of the identity relation can be trivially achieved through use of standard routines such as bsearch(3)/qsort(3).

* No methods of iteration are provided, argv is walkable by either subscripting argv with index 0 up to the value of argc-1, or by testing for the (char*)NULL entry

Typical use cases
-----------------
* Construction of an ```argv``` suitable for use with the ```exec```(2) family of syscalls (with trailing NULL entry)

* With a combination of find/append, can be used to represent a set of strings elements

