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

void print_spaces(char *str, char *s, int width, int right_allign) {
  if (right_allign) strcat(str, s);
  for (int j = 0; j < width - (int)strlen(s); j++) strcat(str, " ");
  if (!right_allign) strcat(str, s);
}

void print_sign(char *str, int num, int sign, int space) {
  if (num >= 0 && sign) strcat(str, "+");
  if (num < 0 && sign) strcat(str, "-");
  if (num >= 0 && space) strcat(str, " ");
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int dot = 0, START = -1;
  int sign = 0, right_allign = 0, space = 0;
  int width = 0, accuracy = 0;
  int SHORT = 0, LONG = 0;
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
          print_spaces(str, s, width, right_allign);
          START = -1;
          break;
        case 'c':
          char c = va_arg(args, int);
          strcat(str, &c);
          START = -1;
          break;
        case 'd':
          if (SHORT) {
            short int d = va_arg(args, short int);
            strcat(str, s21_itoa(d));

          } else if (LONG) {
            long int d = va_arg(args, long int);
            strcat(str, s21_itoa(d));

          } else {
            int d = va_arg(args, int);
            strcat(str, s21_itoa(d));
          }
          START = -1;
          break;
        case 'f':
          if (LONG) {
            double f = va_arg(args, double);
            strcat(str, s21_ftoa(f));

          } else {
            float f = va_arg(args, float);
            strcat(str, s21_ftoa(f));
          }
          START = -1;
          break;
        case 'u':
          if (SHORT) {
            unsigned short int u = va_arg(args, unsigned short int);
            strcat(str, s21_uitoa(u));

          } else if (LONG) {
            unsigned long int u = va_arg(args, unsigned long int);
            strcat(str, s21_uitoa(u));

          } else {
            unsigned int u = va_arg(args, unsigned int);
            strcat(str, s21_uitoa(u));
          }
          START = -1;
          break;
        case ' ':
          space = 1;
          break;
        case '+':
          sign = 1;
          break;
        case '-':
          right_allign = 1;
          break;
        case 'h':
          SHORT = 1;
          break;
        case 'l':
          LONG = 1;
          break;
        default:
          if (sym >= '0' && sym <= '9' || sym == '.') {
            if (sym == '.')
              dot = 1;
            else {
              if (dot)
                accuracy = accuracy * 10 + (sym - '0');
              else
                width = width * 10 + (sym - '0');
            }
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
  char str1[100], str2[100];
  s21_sprintf(str1, "Hello %7s. How sosal?", "world");
  sprintf(str2, "Hello %7s. How sosal?", "world");

  printf("%s\n", str1);
  printf("%s\n", str2);
  printf("%d\n", strcmp(str1, str2));
  return 0;
}