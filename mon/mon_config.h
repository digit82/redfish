/*
 * The OneFish distributed filesystem
 *
 * Copyright (C) 2011 Colin Patrick McCabe <cmccabe@alumni.cmu.edu>
 *
 * This is licensed under the Apache License, Version 2.0.  See file COPYING.
 */

#ifndef ONEFISH__MON_CONFIG_DOT_H
#define ONEFISH__MON_CONFIG_DOT_H

#include "core/log_config.h"

#define JORM_CUR_FILE "mon/mon_config.jorm"
#include "jorm/jorm_generate_include.h"
#undef JORM_CUR_FILE

#endif
