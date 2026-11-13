struct Makefile{
    Variable *variables;
    Regle *regles;
} typedef Makefile;

struct Variable{
    char *nom;
    char *valeur;
    struct Variable *next;
} typedef Variable;

struct Regle{
    char *target;
    char **dependencies;
    char **recipe;
    int dependenciesCount;
    int recipeCount;
    struct Regle *next;
} typedef Regle;

Makefile* parser(const char *path);
void effacer_espaces(char *str);
Variable* ajouter_variable(Variable *variables, char line[]);