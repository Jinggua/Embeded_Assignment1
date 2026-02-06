/* file: status.h
 * author: Yao
 * created: 2026/01/30
 * description: Contains data structures and declarations for HTTP status table
 */

#ifndef _STATUS_H_
#define _STATUS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define NUL '\0'
#define BUF_LEN 64

typedef struct {
  int code;
  const char *name;
  const char *category;
} StatusEntry;

// Table accessors (provided in status.c)
const StatusEntry *statustablebegin(void);
const StatusEntry *statustableend(void);
size_t statustablesize(void);

// You implement these:
const StatusEntry *LookupStatus(int code);

void PrintRange(FILE *stream, int lo, int hi);

void PrintStatus(FILE *stream, const StatusEntry *status);

// Optional (stretch)
const StatusEntry *BinaryLookupStatus(int code);

#endif // _STATUS_H_
