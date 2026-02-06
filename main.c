/*
 * File: main.c
 * Author: 
 * Date: 
 * Description: 
 */

#include "status.h"
#include <ctype.h>  // 需要 isspace() 函数
#include <stdlib.h> // 需要 atoi() 函数
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
  // error information
  if (argc != 2) {
    Usage(argv[0]); // Calls usage with program name (first argument from CLI)
    return 1;
  }

  char *arg = argv[1]; // argument passed in from CLI

  //TODO

  // Detect range "A-B"
  // parse first integer
  // parse second integer
  // if first < second, then print range
  // otherwise print error msg and exit
  
  // Single code
  // Parse integer
  // if invalid int, print error msg and exit
  // lookup value in table
  // print to stdout
  return 0;
}


// ------------------------------------------
// Detect range "A-B"
char *dash = strchr(arg, '-');

if (dash != NULL) {
    // === Handle range format "A-B" ===
    
    // 检查只有一个'-'（拒绝"---", "200--204"等）
    int dash_count = 0;
    for (char *p = arg; *p != '\0'; p++) {
        if (*p == '-') dash_count++;
    }
    
    if (dash_count != 1) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // 分割字符串
    size_t left_len = dash - arg;  // 左边长度
    
    // 严格检查：必须是3位数！
    if (left_len != 3) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // 复制左边部分（正好3个字符）
    char left[4] = {0};  // 3个字符 + '\0'
    strncpy(left, arg, 3);
    left[3] = '\0';
    
    // 检查右边部分
    char *right_start = dash + 1;
    if (strlen(right_start) != 3) {  // 也必须是3位数！
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // 复制右边部分
    char right[4] = {0};
    strncpy(right, right_start, 3);
    right[3] = '\0';
    
    // 解析数字
    int lo, hi;
    if (!ParseInt(left, &lo) || !ParseInt(right, &hi)) {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
    // 检查范围顺序
    if (lo <= hi) {
        PrintRange(stdout, lo, hi);
    } else {
        fprintf(stderr, "Error: Invalid Input\n");
        Usage(argv[0]);
        return 2;
    }
    
} else {
    // === Handle single code ===
    // 单个状态码也必须是3位数
    if (strlen(arg) != 3) {
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
    
    const StatusEntry *entry = LookupStatus(code);
    if (entry == NULL) {
        fprintf(stderr, "Error: HTTP status code %d not found\n", code);
        return 2;
    }
    
    fprintf(stdout, "%d %s (%s)\n", entry->code, entry->message, entry->category);
}