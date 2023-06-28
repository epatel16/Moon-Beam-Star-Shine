#include "info.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct info {
  double constant;
  size_t type;
} info_t;

info_t *info_init(size_t type) {
  info_t *info = malloc(sizeof(info_t));
  info->type = type;
  return info;
}

info_t *info_init_with_const(size_t type, double constant) {
  info_t *info = malloc(sizeof(info_t));
  info->type = type;
  info->constant = constant;
  return info;
}

void info_free(info_t *info) { free(info); }

size_t get_typ(info_t *info) { return info->type; }

double get_constant(info_t *info) { return info->constant; }
