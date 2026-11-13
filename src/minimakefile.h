typedef struct Variable{
    char *nom;
    char *valeur;
    struct Variable *next;
} Variable;

typedef struct Regle{
    char *target;
    char **dependencies;
    char **recipe;
    int dependenciesCount;
    int recipeCount;
    struct Regle *next;
} Regle;

typedef struct Makefile{
    Variable *variables;
    Regle *regles;
} Makefile;

Makefile* parser(const char *path);
Regle* ajouter_recipe(Regle *regles, char *line);
Variable* ajouter_variable(Variable *variables, char line[]);
Regle* ajouter_target_dependencies(Regle *regles, char line[]);
char** ajouter_elt(char **elt, char *line, int *count);
void effacer_espaces(char *str);