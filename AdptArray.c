#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

//I assist in this assigment in the ADT class from c course 

typedef struct AdptArray_ 
{
PElement* AdpElements;
int size_of_array;
/* Function Pointers */
COPY_FUNC CopyFunc;
DEL_FUNC DelElementFunc;
PRINT_FUNC PrintElementFunc;
} AdptArray_;

//PAdptArray is a pointer to AdptArray struct
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func,PRINT_FUNC print_func){
PAdptArray pAD;
pAD = (PAdptArray)malloc(sizeof(AdptArray_)); //allocate this type of pointer
if (pAD){ // if malloc worked
    pAD->DelElementFunc= del_func;
    pAD->CopyFunc = copy_func;
    pAD->PrintElementFunc = print_func;
    pAD->size_of_array = 0;
    pAD->AdpElements = NULL;
    return pAD;
}
return NULL; // if malloc didn't worked
}

void DeleteAdptArray(PAdptArray pAD){
for (int i = 0; i < pAD->size_of_array; i++){
    if ((pAD->AdpElements)[i]){ // if the element in the array in this index isn't null -> delete it
    pAD->DelElementFunc((pAD->AdpElements)[i]);
    }
}
free(pAD->AdpElements); // free the pointer to the array
free(pAD); // free the pointer to the struct
}

//this function assist when there isn't enogh space in the array of the struct
PAdptArray resize(PAdptArray pAD, int index){
    int size = index + 1;
    PElement* temp;
    temp = (PElement*) calloc(size, sizeof(PElement));
    if(temp == NULL){
        return FAIL;
    }
    memcpy(temp, pAD->AdpElements, (pAD-> size_of_array) * sizeof(PElement));
	free(pAD->AdpElements);
    
    pAD->size_of_array = index +1;
	pAD->AdpElements = temp;

    return pAD;
}

//Result returns FAIL or SUCCESS
Result SetAdptArrayAt(PAdptArray pAD, int index, PElement elem){
int size = pAD->size_of_array;

if (pAD == NULL || elem == NULL){
return FAIL;
}
if(index > size){
    pAD = resize(pAD, index);
}
if ((pAD->AdpElements)[index]!=NULL) //if there is already element in this index -> delete it
{
    pAD->DelElementFunc((pAD->AdpElements)[index]);
}
(pAD->AdpElements)[index] = pAD->CopyFunc(elem); //insert a copy of the new element
return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAD, int index){
    if(pAD && index > 0 && index < pAD->size_of_array && pAD->AdpElements[index]){
        return pAD->CopyFunc(pAD->AdpElements[index]);
    }
    return NULL;
}

int GetAdptArraySize(PAdptArray pAD){
    if(!pAD){ // if pAD is null
        return -1;
    }
    return pAD->size_of_array;
}

void PrintDB(PAdptArray pAD){
    int i;
    if (pAD == NULL || pAD->AdpElements == NULL)
        return;
    for (i = 0; i < pAD->size_of_array; i++)
        {
        if ((pAD->AdpElements)[i] != NULL)
            pAD->PrintElementFunc(pAD->AdpElements[i]);
        }
}
