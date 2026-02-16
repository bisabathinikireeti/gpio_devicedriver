/* Program of Stack using Array */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int stack_arr[MAX];
int top = -1;

/* Function Prototypes */
void push(int item);
int pop();
int peek();
int isEmpty();
int isFull();
void display();

int main()
{
    int choice, item;

    while (1)
    {
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Display the top element");
        printf("\n4. Display all stack elements");
        printf("\n5. Quit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the item to be pushed: ");
                scanf("%d", &item);
                push(item);
                break;

            case 2:
                item = pop();
                printf("Popped item is: %d\n", item);
                break;

            case 3:
                printf("Item at the top is: %d\n", peek());
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Wrong choice\n");
        }
    }

    return 0;
}

/* Push Function */
void push(int item)
{
    if (isFull())
    {
        printf("Stack Overflow\n");
        return;
    }

    top = top + 1;
    stack_arr[top] = item;
}

/* Pop Function */
int pop()
{
    int item;

    if (isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    item = stack_arr[top];
    top = top - 1;

    return item;
}

/* Peek Function */
int peek()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    return stack_arr[top];
}

/* Check if Stack is Empty */
int isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

/* Check if Stack is Full */
int isFull()
{
    if (top == MAX - 1)
        return 1;
    else
        return 0;
}

/* Display Stack Elements */
void display()
{
    int i;

    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements are:\n");

    for (i = top; i >= 0; i--)
    {
        printf("%d\n", stack_arr[i]);
    }
}
