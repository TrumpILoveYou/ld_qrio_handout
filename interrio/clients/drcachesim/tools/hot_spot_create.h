/* hot_spot tool creation */

#ifndef _HOT_SPOT_CREATE_H_
#define _HOT_SPOT_CREATE_H_ 1

#include "analysis_tool.h"

/**
 * @file drmemtrace/hot_spot_create.h
 * @brief DrMemtrace tool that computes the hot spot fucntions and blocks.
 */

/**
 * Creates an analysis tool which computes hot spot function and basic block
 */
analysis_tool_t *
hot_spot_tool_create(unsigned int verbose = 0);

#endif /* _HOT_SPOT_CREATE_H_ */