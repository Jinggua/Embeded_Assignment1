/*
 * File: main.c
 * Author: Dianyao Su
 * Date: 2026/02/05
 * Description: This program provides a command-line interface for looking up HTTP status codes and their description. It  * supports both single code lookup and range-based quries. 
 */

#include "status.h"
#include <string.h>
#include <ctype.h>  
#include <stdlib.h> 
static void Usage(const char *prog) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  %s <CODE>\n", prog);
  fprintf(stderr, "  %s <LOW>-<HIGH>\n", prog);
  fprintf(stderr, "Examples:\n");
  fprintf(stderr, "  %s 404\n", prog);
  fprintf(stderr, "  %s 200-204\n", prog);
}

// Takes a string and parses it for an integer value. Ignore surrounding whitespace.
static bool ParseInt(const char *s, int *out) {
  if (s == NULL || out == NULL) {
    return false;
  }
  // Skip leading whitespace characters
  while (isspace(*s)) {
    s++;
  }
  
  // Check if already at end of string (all whitespace)
  if (*s == '\0') {
    return false;
  }
  
  // Check each character to ensure all are digits
  const char *p = s;
  while (*p != '\0' && !isspace(*p)) {
    if (*p < '0' || *p > '9') {  // Not a digit character
      return false;
    }
    p++;
  }
  
  // Skip trailing whitespace characters
  while (isspace(*p)) {
    p++;
  }
  
  // If there are still non-whitespace characters, format is incorrect
  if (*p != '\0') {
    return false;
  }
  
  // Convert to integer
  int value = atoi(s);
  
  //  Check if it's a 3-digit number 
  if (value < 100 || value > 999) {
    return false;
  }
  
  *out = value;
  return true;
}

int main(int argc, char *argv[]) {
  char *arg = argv[1]; // argument passed in from CLI
  // error information
  if (argc != 2) {
    Usage(argv[0]); // Calls usage with program name (first argument from CLI)
    return 1;
  }
  // Detect range "A-B"
  // parse first integer
  // parse second integer
  // if first < second, then print range
  // otherwise print error msg and exit
  char *dash = strchr(arg, '-');

  if (dash != NULL) {
    // === Handle range format "A-B" ===
    
    // check there is only one'-'（reject"---", "200--204"等）
    int dash_count = 0;
    for (char *p = arg; *p != '\0'; p++) {
        if (*p == '-') dash_count++;
    }
    
    if (dash_count != 1) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // split the string
    size_t left_len = dash - arg;  // length of the left part
    
    // must be 3 digits
    if (left_len != 3) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // copy the left part
    char left[4] = {0};  // 3 digits + '\0'
    strncpy(left, arg, 3);
    left[3] = '\0';
    
    // check the right parts
    char *right_start = dash + 1;
    if (strlen(right_start) != 3) {  
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // copy the right part
    char right[4] = {0};
    strncpy(right, right_start, 3);
    right[3] = '\0';
    
    // parse number values
    int lo, hi;
    if (!ParseInt(left, &lo) || !ParseInt(right, &hi)) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // check rang order
    if (lo <= hi) {
        PrintRange(stdout, lo, hi);
    } else {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
} else {
	 // Single code
     // Parse integer
     // if invalid int, print error msg and exit
     // lookup value in table
     // print to stdout
     // Handle single code 
    if (strlen(arg) != 3) { // Single status code must also be 3 digits
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    int code;
    if (!ParseInt(arg, &code)) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    const StatusEntry *entry = BinaryLookupStatus(code);
    if (entry == NULL) {
        fprintf(stderr, "Error: HTTP status code %d not found\n", code);
        return 2;
    }
    
    fprintf(stdout, "%d %s (%s)\n", entry->code, entry->name, entry->category);
}
  return 0;
}


