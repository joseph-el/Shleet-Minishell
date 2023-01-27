

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/*
Matching algorithm 
int WildcardMatch(const char *pszString, const char *pszMatch)
{
    while (*pszMatch)
    {
       if (*pszMatch == '*')
        {
            // Need to do some tricks.

            // 1. The wildcard * is ignored. 
            //    So just an empty string matches. This is done by recursion.
            //      Because we eat one character from the match string, the
            //      recursion will stop.
            if (WildcardMatch(pszString, pszMatch + 1))
                // we have a match and the * replaces no other character
                return 1;

            // 2. Chance we eat the next character and try it again, with a
            //    wildcard * match. This is done by recursion. Because we eat
            //      one character from the string, the recursion will stop.
            if (*pszString && WildcardMatch(pszString+1,pszMatch))
                return 1;
            // Nothing worked with this wildcard.
            return 0;
        }
        else
        {
            // Standard compare of 2 chars. Note that *pszSring might be 0
            // here, but then we never get a match on *pszMask that has always
            // a value while inside this loop.
            if (toupper(*pszString++) != toupper(*pszMatch++))
                return 0;
        }
    }
    // Have a match? Only if both are at the end...
    return !*pszString && !*pszMatch;
}
*/


/*
The function "match" takes in two parameters: "text" and "pattern". It is used to check if the string "text" matches the pattern defined by the string "pattern".

The function starts by checking if both "text" and "pattern" have reached the end (indicated by the null character '\0'). If they have, the function returns "true" indicating a match.

If the first character of the "pattern" is a wildcard character '*', the function recursively calls itself twice: once with the "text" and "pattern + 1" (to match the rest of the string after the wildcard) and once with "text + 1" and "pattern" (to check for a match by skipping one character in the text). If either of the recursive calls return "true", the function returns "true", indicating a match. If neither recursive call return "true", the function returns "false", indicating no match.

If the first character of the "text" and "pattern" match, the function recursively calls itself with "text + 1" and "pattern + 1" to check for a match with the next characters.

If the first character of the "text" and "pattern" do not match, the function returns "false" indicating no match.

It is a recursive function that check for a pattern match
*/
bool match(char *text, char *pattern)
{
    if (!*text && !*pattern)
        return (true);
    if (*pattern == '*')
        return (match(text, pattern + 1) || (*text != 0 && match(text + 1, pattern)));
    if (*text == *pattern)
        return match(text + 1, pattern + 1);
    return (false);
}

int main()
{
    char string[200] = "test";
    char pattern[200] = "*t";

    if (match(string, pattern) == 1)
        printf("Match\n");
    else
        printf("No Match\n");
    return 0;
}
