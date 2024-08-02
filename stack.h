#ifndef _STACK_H_
#define _STACK_H_

typedef void *data_type;

typedef struct stack Stack;

// Aloca e inicializa uma nova pilha.
Stack *stack_construct();

// Libera todos os recursos alocados pela pilha.
void stack_destroy(Stack *s, void (*element_free)(void *));

// Empilha um elemento no topo da pilha.
void stack_push(Stack *s, data_type element);

// Desempilha o elemento do topo da pilha e o retorna.
data_type stack_pop(Stack *s);

// Retorna o elemento do topo da pilha sem removê-lo.
data_type stack_peek(Stack *s);

// Retorna o número de elementos atualmente na pilha.
int stack_size(Stack *s);

// Verifica se a pilha está vazia.
int stack_is_empty(Stack *s);

#endif