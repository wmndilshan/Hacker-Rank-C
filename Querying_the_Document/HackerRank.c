#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

enum SPLIT
{
    SPLIT_PARAGRAPH,
    SPLIT_SENTNECE,
    SPLIT_WORD
};

int paragraphCount, sentenceCount, wordCount;

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) 
{
    return document[k][m][n];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) 
{ 
    return document[k][m];
}   

char*** kth_paragraph(char**** document, int k) 
{
    return document[k];
}



char** split(char* text, enum SPLIT textType) 
{
    char* delimiter;
    size_t maxLength = 0;
    int count = 0;

    switch(textType) 
    {
        case 0: 
            paragraphCount = 0;
            delimiter = "\n";
            break;
        case 1:
            sentenceCount = 0;
            delimiter = ".";
            break;
        case 2:
            wordCount = 0;
            delimiter = " ";
            break; 
        default:
            perror("Wrong SPLIT TYPE");
            exit(0);
    }

    char* copyText = (char*)calloc(strlen(text) + 1, sizeof(char));
    strcpy(copyText, text);

    char* splitedChunk = strtok(copyText, delimiter);
    char* memForSplitedChunk;

    do
    {
        count++;
        maxLength = strlen(splitedChunk);
        if (strlen(splitedChunk) > maxLength) maxLength = strlen(splitedChunk);
        splitedChunk = strtok(NULL, delimiter);
    } while (splitedChunk != NULL);

    switch (textType)
    {
        case 0: paragraphCount = count; break;
        case 1: sentenceCount = count; break;
        case 2: wordCount = count; break;
    }

    maxLength++;
    char** results = (char**)calloc(count, sizeof(char*));
    strcpy(copyText, text);
    
    splitedChunk = strtok(copyText, delimiter);


    int i = 0;
    do
    {
        memForSplitedChunk = (char*)calloc(maxLength, sizeof(char));
        strcpy(memForSplitedChunk, splitedChunk);
        results[i++] = memForSplitedChunk;
        splitedChunk = strtok(NULL, delimiter);

    } while (splitedChunk != NULL);
    
    free(copyText);
    return results;
}

char**** get_document(char* text) 
{
    char **currentParagraph, **currentSentence, **currentWord;
    currentParagraph = split(text, SPLIT_PARAGRAPH);
    char**** document = (char****)calloc(paragraphCount, sizeof(char***));
    char*** paragraph;
    char** sentence;

    for (int i = 0; i < paragraphCount; i++) 
    {
        currentSentence = split(currentParagraph[i], SPLIT_SENTNECE);
        paragraph = (char***)calloc(sentenceCount, sizeof(char**));

        for (int j = 0; j < sentenceCount; j++)
        {
            currentWord = split(currentSentence[j], SPLIT_WORD);
            sentence = (char**)calloc(wordCount, sizeof(char*));
            paragraph[j] = sentence;
        }
        document[i] = paragraph;
    }
    
    return document;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}