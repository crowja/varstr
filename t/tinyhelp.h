/**
 * @file tinyhelp.h
 * @version 0.1.0
 * @see https://github.com/crowja/tinyhelp
 * @date Sun Feb 16, 2020 11:18:06 PM CST
 * @copyright 2020 John A. Crow <crowja@gmail.com>
 * @license Unlicense <http://unlicense.org/>
 * @brief Helpers supporting Joe Walnes' tinytest.h unit test framework.
 */

#ifndef TINY_HELP_H
#define TINY_HELP_H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "tinytest.h"

#ifdef  TH_COLOR_RED
#undef  TH_COLOR_RED
#endif
#define TH_COLOR_RED        "\x1B[31;1m"

#ifdef  TH_COLOR_GREEN
#undef  TH_COLOR_GREEN
#endif
#define TH_COLOR_GREEN      "\x1B[32;1m"

#ifdef  TH_COLOR_YELLOW
#undef  TH_COLOR_YELLOW
#endif
#define TH_COLOR_YELLOW     "\x1B[33;1m"

#ifdef  TH_COLOR_BLUE
#undef  TH_COLOR_BLUE
#endif
#define TH_COLOR_BLUE       "\x1B[34;1m"

#ifdef  TH_COLOR_RESET
#undef  TH_COLOR_RESET
#endif
#define TH_COLOR_RESET      "\x1B[0m"

static int
doubles_are_close(double x, double y, double tol)
{
   return fabs(x - y) <= fabs(tol) ? 1 : 0;
}

static int
doubles_are_equal(double x, double y)
{
   return doubles_are_close(x, y, 2 * DBL_EPSILON);
}

static void
fprintf_test_info(FILE *out, char *name, const char *info)
{
   fprintf(out, TH_COLOR_YELLOW "%s" TH_COLOR_RESET, name);

   if (NULL != info)
      printf(" [%s]", info);

   printf("\n");
}

#define ASSERT_DOUBLE_EQUALS(expected, actual) ASSERT((#actual), 1 == doubles_are_equal((expected), (actual)))
#define ASSERT_DOUBLE_CLOSE(expected, actual, tol) ASSERT((#actual), 1 == doubles_are_close((expected), (actual), (tol)))

#endif
