#include "list.h"
#include "state.h"
#include "test_util.h"
#include <assert.h>
#include <stdlib.h>

typedef struct {
  state_t *state;
  size_t index;
} state_access_t;

typedef struct state {
  size_t points;
  size_t start;
  size_t end;
  list_t *list;
} state_t;

int main(int argc, char *argv[]) {

  state_access_t *access = malloc(sizeof(*access));
  access->state = malloc(sizeof(state_t));
  access->state->start = 0;
  access->state->end = 1;

  assert(access->state != NULL);
  assert(access->state->start == 0);
  assert(access->state->end == 1);

  list_free(access->state->list);
  free(access->state);
  free(access);

  puts("state_test PASS");
}
