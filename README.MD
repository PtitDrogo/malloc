# We are recoding our own malloc, fun !

ZONES:

```
TINY: 1-128
SMALL: 128-1024
LARGE 1024+
```

```
Flags	                         Result
MAP_PRIVATE + file	             Read file contents, edits stay local to your process
MAP_SHARED + file	             Read file contents, edits go back to the file
MAP_PRIVATE | MAP_ANONYMOUS	     Private zeroed memory (what malloc uses for large allocations)
MAP_SHARED | MAP_ANONYMOUS	     Zeroed memory shared with child processes after fork()
```

Cool Idea to get a 16 bytes size header.

```
to save space later, pack free into the low bit of size (the low 4 bits are always zero after rounding).
```