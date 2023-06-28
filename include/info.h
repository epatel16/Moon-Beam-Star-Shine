#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A structure that contains extra info pertaining to bodies.
 */
typedef struct info info_t;

/**
 * Initializes the info structure with the type of body.
 * 
 * @return a pointer to the newly allocated info
 */
info_t *info_init(size_t type);

/**
 * Initializes the info structure with the type of body and a constant.
 * 
 * @return a pointer to the newly allocated info
 */
info_t *info_init_with_const(size_t type, double constant);

/**
 * Releases the memory allocated for an info struct.
 *
 * @param info a pointer to an info struct returned from an init function
 */
void info_free(info_t *info);

/**
 * Returns the type of the body that is contained in the info struct.
 *
 * @param info a pointer to an info struct
 */
size_t get_typ(info_t *info);
