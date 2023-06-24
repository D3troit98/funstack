// funstack.c: This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack312_ll.h"

void makeStack(Stack312* sp)
{
    sp->top = NULL;
}

bool isFull(Stack312 s)
{
    return false; // Linked list implementation does not have a fixed size
}

bool isEmpty(Stack312 s) {
    return (s.top == NULL);
}

void push(StackEntry e, Stack312* sp)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed. Unable to push element onto the stack.\n");
        exit(EXIT_FAILURE);
    }
    newNode->pixel = e;
    newNode->next = sp->top;
    sp->top = newNode;
    print("here");
}

StackEntry pop(Stack312* sp)
{
    if (isEmpty(*sp))
    {
        fprintf(stderr, "Stack underflow. Unable to pop element from the stack.\n");
        exit(EXIT_FAILURE);
    }
    StackNode* topNode = sp->top;
    StackEntry topEntry = topNode->pixel;
    sp->top = topNode->next;
    free(topNode);
    return topEntry;
}

void floodFill(char picture[25][25], int numRows, int numCols, int startRow, int startCol, char newColor)
{
    char originalColor = picture[startRow][startCol];
    if (originalColor == newColor)
        return;
    Stack312 stack;
    makeStack(&stack);

    Pixel startPixel = { startRow, startCol, originalColor };
    push(startPixel, &stack);

    while (!isEmpty(stack)) {
        Pixel currentPixel = pop(&stack);
        int row = currentPixel.row;
        int col = currentPixel.col;

        if (picture[row][col] == originalColor) {
            picture[row][col] = newColor;

            //check neighboring pixels
            if (row > 0 && picture[row - 1][col] == originalColor)
            {
                Pixel neighbor = { row - 1, col, originalColor };
                push(neighbor, &stack);
            }
            if (row < numRows - 1 && picture[row + 1][col] == originalColor) {
                Pixel neighbor = { row - 1, col, originalColor };
                push(neighbor, &stack);
            }
            if (col > 0 && picture[row][col - 1] == originalColor) {
                Pixel neighbor = { row, col - 1, originalColor };
                push(neighbor, &stack);
            }
            if (col < numCols - 1 && picture[row][col + 1] == originalColor)
            {
                Pixel neighbor = { row, col + 1, originalColor };
                push(neighbor, &stack);
            }
        }
    }
}

void printPicture(char picture[25][25], int numRows, int numCols)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++) {
            printf("%c", picture[row][col]);
        }
        printf("\n");
    }
}
int main()
{
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the input file.\n");
        return 1;
    }

    char picture[25][25];
    int numRows = 0;
    int numCols = 0;

    //Read the picture from the file
    while (fgets(picture[numRows], sizeof(picture[numRows]), file) != NULL) {
        numCols = strlen(picture[numRows]);
        picture[numRows][numCols - 1] = '\0'; //Remove newLine character
        numRows++;
    }
    fclose(file);

    //Prompt the user for flood fill inputs
    int row, col;
    char color;

    printf("Original Picture:\n");
    printPicture(picture, numRows, numCols);

    while (true)
    {
        printf("Enter a row (-1 to exit): ");
        scanf("%d", &row);
        if (row == -1)
            break;

        printf("Enter a column: ");
        scanf("%d", &col);

        printf("Enter a color: ");
        scanf(" %c", &color); // Note the space before %c to consume the newline character

        floodFill(picture, numRows, numCols, row, col, color);

        printf("Updated Picture: \n");
        printPicture(picture, numRows, numCols);
    }
    return 0;
}


