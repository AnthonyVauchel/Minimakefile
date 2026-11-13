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
        line[strcspn(line, "\n")] = '\0';
        char *first = strpbrk(line, "=:");
        if (line[0] == '\t'){
            result->regles = ajouter_recipe(result->regles, line+1); // + 1 pour éviter le \t
        } else if (first != NULL && *first == '='){
            result->variables = ajouter_variable(result->variables, line);
            
        } else if (first != NULL && *first == ':'){
            result->regles = ajouter_target_dependencies(result->regles, line);
        }
    }

    fclose(makefile);
    return result;
}

Regle* ajouter_recipe(Regle *regles, char *line){
    Regle *tmp = regles;
    while (tmp->next != NULL){
        tmp = tmp->next;
    }

    //Ajout de la commande à la dernière règle créée
    tmp->recipe = ajouter_elt(tmp->recipe, line, &tmp->recipeCount);

    return regles;
}

Variable* ajouter_variable(Variable *variables, char *line){
    Variable *new = malloc(sizeof(Variable));

    //Partie gauche du "=" = nom
    char *token = strtok(line, "=");
    effacer_espaces(token);
    new->nom = strdup(token);

    //Partie droite du "=" = valeur
    token = strtok(NULL, "=");
    if (token){
        effacer_espaces(token);
        new->valeur = strdup(token);
    } else {
        new->valeur = strdup("");
    }
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

Regle* ajouter_target_dependencies(Regle *regles, char *line){
    Regle *new = malloc(sizeof(Regle));
    new->dependencies = NULL;
    new->dependenciesCount = 0;
    new->recipe = NULL;
    new->recipeCount = 0;
    new->next = NULL;

    //Partie gauche du ":" = target
    char *token = strtok(line, ":");
    effacer_espaces(token);
    new->target = strdup(token);

    //Partie droite du ":" = dependencies
    token = strtok(NULL, ":");
    token = strtok(token, " ");
    while (token != NULL){
        new->dependencies = ajouter_elt(new->dependencies, token, &new->dependenciesCount);
        token = strtok(NULL, " ");
    }

    if (!regles){
        regles = new;
    } else {
        Regle *tmp = regles;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new;
    }

    return regles;
}


char** ajouter_elt(char **elt, char *line, int *count){
    char **tmpTab = realloc(elt, (*count + 1) * sizeof(char*)); //Ajout d'une case de la taille d'un pointeur de char
    elt = tmpTab;
    elt[*count] = strdup(line);
    (*count)++;
    return elt;
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