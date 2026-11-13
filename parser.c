#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimakefile.h"

Makefile* parser(const char *path){
    FILE *makefile = fopen(path, "r");

    if (!makefile){
        perror("Erreur lors de l'ouverture du makefile\n");
        return NULL;
    }

    Makefile *result = malloc(sizeof(Makefile));
    result->variables = NULL;
    result->regles = NULL;

    char line[256];
    while (fgets(line, sizeof(line), makefile)){
        if (strchr(line, '=') != NULL){
            result->variables = ajouter_variable(result->variables, line);
        }
    }
}

Variable* ajouter_variable(Variable *variables, char line[]){
    Variable *new = malloc(sizeof(Variable));
    char *token = strtok(line, "=");
    effacer_espaces(token);
    new->nom = token;
    token = strtok(NULL, "=");
    effacer_espaces(token);
    new->valeur = token;
    new->next = NULL;
    if (!variables){
        variables = new;
    } else {
        Variable *tmp = variables;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    return variables;
}

void effacer_espaces(char *str){
    int i = 0;
    int j = 0;
    while (str[i] != '\0'){
        if (str[i] != ' '){
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}