/**
 * @file dependence_distance_create.h
 * @author Chaoyi Liang (cappuccinocup@126.com)
 * @brief A tool that can calculate the instruction level 
 * dependence distance of a program based on its instruction trace. 
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Dependence distance tool creation */

#ifndef _DEP_DISTANCE_CREATE_H_
#define _DEP_DISTANCE_CREATE_H_ 1

#include "analysis_tool.h"

analysis_tool_t *
dep_distance_tool_create();

#endif /* _DEP_DISTANCE_CREATE_H_ */