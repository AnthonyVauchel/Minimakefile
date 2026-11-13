/*
 * Programme de test du parser (ce n'est pas le -p final de minimake).
 * Usage : ./test_parser fichier.mk
 * Affiche ce que le parser a rangé, au format du -p du sujet.
 * Code de retour : 0 si le parser a réussi, 2 s'il a renvoyé NULL.
 */
#include <stdio.h>

#include "minimakefile.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s fichier.mk\n", argv[0]);
        return 2;
    }

    Makefile *mk = parser(argv[1]);
    if (mk == NULL)
        return 2;

    printf("# variables\n");
    for (Variable *v = mk->variables; v != NULL; v = v->next)
        printf("'%s' = '%s'\n", v->nom, v->valeur);

    printf("# rules\n");
    for (Regle *r = mk->regles; r != NULL; r = r->next)
    {
        printf("(%s):", r->target);
        for (int i = 0; i < r->dependenciesCount; i++)
            printf(" [%s]", r->dependencies[i]);
        printf("\n");
        for (int i = 0; i < r->recipeCount; i++)
            printf("    '%s'\n", r->recipe[i]);
    }

    return 0;
}