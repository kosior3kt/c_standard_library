#ifndef __STACK__
#define __STACK__

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "../utils.h"
#include "../defines.h"
#include "../allocators/arena.h"
#include "dynamic_array.h"

///////////////////////////// EXAMPLE
/*
arena_s arena;
arena_init(&arena);

stack_s stack_arena, stack_malloc;
stack_init(&stack_malloc, <size>, NULL);
stack_init(&stack_arena, <size>, arena);

stack_add(&stack_malloc, <value>);
int returned_value = stack_pop(&stack_malloc);
*/


typedef struct {
	uint current_size, max_size;
	dynamic_array_s data_;
}stack_s;

///////////////////////////// DECLARATIONS
static void  stack_init(stack_s*, const uint, arena_s*);
static void  stack_add(stack_s*, void*);
static void* stack_pop(stack_s*);
static void* stack_peek(stack_s*);
static bool  stack_is_empty(stack_s*);
static void  stack_print(stack_s*);

///////////////////////////// DEFINITIONS
static void
stack_init(stack_s* _stack, const uint _size, arena_s* _arena)
{
	if(_arena == NULL) {
		da_init(&_stack->data_, _size, NULL);
	} else {
		da_init(&_stack->data_, _size, _arena);
	}
	_stack->current_size = 0;
	_stack->max_size = _size;
	if(_stack->max_size <= 0) _stack->max_size = 1;
}

static void
stack_add(stack_s* _stack, void* _value)
{
	if(_stack->current_size >= _stack->max_size) {
		_stack->max_size *= 2;
		da_resize(&_stack->data_, _stack->max_size);
	}

	da_add_at(&_stack->data_, _stack->current_size, _value);
	++_stack->current_size;
}

static void*
stack_pop(stack_s* _stack)
{
	if(_stack->current_size <= 0) {
		return NULL;
	}

	--_stack->current_size;
	void* ret_val = da_get_at(&_stack->data_, _stack->current_size);
	return ret_val;
}

static void*
stack_peek(stack_s* _stack)
{
	if(_stack->current_size <= 0) {
		perror("stack is empty\n");
		assert(0);
	}

	void* ret_val = da_get_at(&_stack->data_, _stack->current_size - 1);
	return ret_val;
}

static bool
stack_is_empty(stack_s* _stack)
{
	//printf("test me! (stack_is_empty)");
	return (_stack->current_size == 0);
}

static void
stack_print(stack_s* _stack)
{
	uint index = _stack->current_size;
	while(index > 0) {
		--index;
		//printf("%d, ", (int)da_get_at(&_stack->data_, index));
	}
}

#endif//__STACK__
