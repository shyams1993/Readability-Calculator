#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
/* Declaration of constants to be used to check states for word calculation */
const int IN = 1;
const int OUT = 0;
int readabilityScore(int lc, int wc, int sc); /* Initializing the function to calculate readability score */
int main(void)
{
    /* Declaration of variables for state, length, user input */
    int state = OUT;
    string s = get_string("Text: ");
    int length = strlen(s);
    int lc = 0, wc = 0, sc = 0; /*Declaration and initialization of variables to hold letter count, word count and sentence count */
    for (int i = 0; i < length; i++)
    {
        /* counting letters first by a simple counter variable*/
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            lc++;
        }
        /* Logic to count number of words by setting state to a 0 constant by default. If a space, tab or newline is encountered,
        state is set to 0. So counter intuitively the state is 0 only if it encounters a space,tab or newline. If otherwise, 
        if state is 0, then state becomes 1 and thus word count variable is incremented */
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            wc++;
        }
        else if (s[i] == '!' || s[i] == '.' || s[i] == '?')
        {
            sc++;
        }
    }
    /* Printing out the readability score based on the grade */
    int grade = readabilityScore(lc, wc, sc);
    /* If grade is less than 1, then it's before Grade 1 */
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    /* If grade is greater than 16, then the grade is 16+ readability level */
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    /* Else print out the appropriate grade level */
    else
    {
        printf("Grade %i\n", grade);
    }
}
/* Function to calculate the readability score and return the appropriate score index */
/* Arguments provided are the letter counts, word counts and sentence counts */
int readabilityScore(int lc, int wc, int sc)
{
    /* Type casting int to float to handle the decimal point precision */
    float L = ((float)lc / (float)wc) * 100;
    float S = ((float)sc / (float)wc) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8); /* Coleman-Liau formula to calculate the reading level as index */
    return index;
}
