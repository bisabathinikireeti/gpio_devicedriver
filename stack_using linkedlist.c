/* Program of Stack using Linked List */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *link;
};

struct node *top = NULL;

/* Function Prototypes */
void push(int item);
int pop();
int peek();
int isEmpty();
void display();

int main()
{
    int choice, item;

    while (1)
    {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display item at the top\n");
        printf("4. Display all items of the stack\n");
        printf("5. Quit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the item to be pushed : ");
                scanf("%d", &item);
                push(item);
                break;

            case 2:
                item = pop();
                printf("Popped item is : %d\n", item);
                break;

            case 3:
                printf("Item at the top is : %d\n", peek());
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
    struct node *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));

    if (tmp == NULL)
    {
        printf("Stack Overflow\n");
        return;
    }

    tmp->info = item;
    tmp->link = top;
    top = tmp;
}

/* Pop Function */
int pop()
{
    struct node *tmp;
    int item;

    if (isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    tmp = top;
    item = tmp->info;
    top = tmp->link;
    free(tmp);

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

    return top->info;
}

/* isEmpty Function */
int isEmpty()
{
    if (top == NULL)
        return 1;
    else
        return 0;
}

/* Display Function */
void display()
{
    struct node *ptr = top;

    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements :\n");

    while (ptr != NULL)
    {
        printf("%d\n", ptr->info);
        ptr = ptr->link;
    }
}
