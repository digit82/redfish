/*
 * The OneFish distributed filesystem
 *
 * Copyright (C) Colin Patrick McCabe <cmccabe@alumni.cmu.edu>
 *
 * This is licensed under the Apache License, Version 2.0.  See file COPYING.
 */

#ifndef ONEIFHS_CHUNK_IO_H
#define ONEIFHS_CHUNK_IO_H

#include <stdint.h>

int onechunk_set_prefix(const char *prefix);
int onechunk_write(uint64_t bid, const char *data, int count, int offset);
int onechunk_read(uint64_t bid, char *data, int count, int offset);

#endif