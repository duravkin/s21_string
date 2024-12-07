#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

double s21_atof(const char *str) {
  // string to double.
  return 0;
}

char *s21_itoa(int num) {
  // int to string.
  return NULL;
}

char *s21_ftoa(float num) {
  // float to string.
  return NULL;
}

char *s21_uitoa(unsigned int num) {
  // unsigned int to string.
  return NULL;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int dot = 0, START = -1;
  int width = 0, accuracy = 0;
  for (int i = 0; format[i]; i++) {
    printf("[%d] - %s\n", i, str);
    char sym = format[i];
    if (format[i] == '%') {
      dot = 0;
      START = i;
    }

    if (START >= 0) {
      switch (sym) {
        case 's':
          char *s = va_arg(args, char *);
          for (int j = 0; j < width - strlen(s); j++) strcat(str, " ");
          strcat(str, s);
          START = -1;
          break;
        case 'c':
          char c = va_arg(args, int);
          strcat(str, &c);
          START = -1;
          break;
        case 'd':
          int d = va_arg(args, int);
          strcat(str, s21_itoa(d));
          START = -1;
          break;
        case 'f':
          float f = va_arg(args, double);
          strcat(str, s21_ftoa(f));
          START = -1;
          break;
        case 'u':
          unsigned int u = va_arg(args, unsigned int);
          strcat(str, s21_uitoa(u));
          START = -1;
          break;
        default:
          if (sym == ' ' || sym == '-' || sym == '+') {
            printf("FLAG: %c\n", sym);
          } else if (sym >= '0' && sym <= '9' || sym == '.') {
            if (sym == '.')
              dot = 1;
            else {
              if (dot)
                accuracy = accuracy * 10 + (sym - '0');
              else
                width = width * 10 + (sym - '0');
            }
            // printf("NUM: %c - DOT: %d\n", sym, dot);
          }
          break;
      }
    } else {
      strcat(str, &sym);
    }
  }
  printf("%d - %d\n", width, accuracy);
  va_end(args);
  return 0;
}

int main() {
  char str[100];

  s21_sprintf(str, "Hello %12s", "World");
  printf("%s\n", str);
  return 0;
}