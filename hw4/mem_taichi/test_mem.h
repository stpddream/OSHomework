/* 
 * File:   test.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on March 30, 2014, 5:49 PM
 */

#ifndef TEST_H
#define	TEST_H

#include "mem.h"
#include "mem_util.h"
#include <stdio.h>

#define TEST_SUCCESS 0
#define TEST_FAIL -1
#define TOTAL_MEMORY 8192

extern int m_error;
int check_for_eight_byte();
int simple_8_byte_alloc();
int aligned_alloc();
int odd_sized_alloc();
int bad_args_to_mem_init();
int worst_fit_alloc();
int coalesce_of_space();
int simple_alloc_free();
int aligned_alloc_free();
int odd_sized_alloc_free();
int init_size_one_page();
int init_size_round_one_page();
int no_space_left_allocate();
int free_null();
int check_memory_written_after_allocation();


#endif	/* TEST_H */

