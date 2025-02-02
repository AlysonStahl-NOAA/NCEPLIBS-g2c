/* This is a test for the NCEPLIBS-g2c project. This test is for
 * ddrstemplates.c.
 *
 * Ed Hartnett 10/25/21
 */

#include "grib2_int.h"
#include <stdio.h>
#include <stdlib.h>

/* Prototypes. */
g2int getdrsindex(g2int number);

int
main()
{
    printf("Testing drstemplates.\n");
    printf("Testing simple getdrstemplate() calls...");
    {
        gtemplate *tmpl;

        /* Check for one that's there. */
        tmpl = getdrstemplate(0);
        if (!tmpl)
            return G2C_ERROR;
        if (tmpl->num != 0 || tmpl->maplen != 5 || tmpl->needext)
            return G2C_ERROR;
        free(tmpl);

        /* Check for one that's not there. */
        tmpl = getdrstemplate(-1);
        if (tmpl)
            return G2C_ERROR;
    }
    printf("ok!\n");
    printf("Testing simple g2c_get_drs_template() call...");
    {

        int maplen, needext;
        int map[G2C_MAX_DRS_TEMPLATE_MAPLEN];
        int expected_map[5] = {4, -2, -2, 1, 1};
        int m;
        int ret;

        /* This won't work. */
        if (g2c_get_drs_template(G2C_MAX_DRS_TEMPLATE + 1, &maplen, map, &needext) != G2C_ENOTEMPLATE)
            return G2C_ERROR;

        /* Check for one that's there. */
        if ((ret = g2c_get_drs_template(0, &maplen, map, &needext)))
            return ret;
        if (maplen != 5 || needext)
            return G2C_ERROR;
        for (m = 0; m < maplen; m++)
            if (map[m] != expected_map[m])
                return G2C_ERROR;
    }
    printf("ok!\n");
    printf("Testing extdrstemplate() calls (expect and ignore error messages)...");
    {
#define MAX_LIST 40
        gtemplate *tmpl;
        g2int list[MAX_LIST];
        int i;

        for (i = 0; i < MAX_LIST; i++)
            list[i] = 2;

        /* Check for one that's there but does not need an extension. */
        tmpl = extdrstemplate(0, list);
        if (!tmpl)
            return G2C_ERROR;
        if (tmpl->num != 0 || tmpl->maplen != 5 || tmpl->needext)
            return G2C_ERROR;
        free(tmpl);

        /* Check for one that's not there. */
        tmpl = extdrstemplate(-1, list);
        if (tmpl)
            return G2C_ERROR;
    }
    printf("ok!\n");
    printf("Testing all getdrstemplate() calls...\n");
    {
#define NUM_TEST 10
        int number[NUM_TEST] = {0, 2, 3, 50, 51, 40, 41, 40000, 40010, 53};
        int expected_maplen[NUM_TEST] = {5, 16, 18, 5, 10, 7, 5, 7, 5, 11};
        int expected_map[NUM_TEST][18] = {
            {4, -2, -2, 1, 1},                                        /* 0 */
            {4, -2, -2, 1, 1, 1, 1, 4, 4, 4, 1, 1, 4, 1, 4, 1},       /* 2 */
            {4, -2, -2, 1, 1, 1, 1, 4, 4, 4, 1, 1, 4, 1, 4, 1, 1, 1}, /* 3 */
            {4, -2, -2, 1, 4},                                        /* 50 */
            {4, -2, -2, 1, -4, 2, 2, 2, 4, 1},                        /* 51 */
            {4, -2, -2, 1, 1, 1, 1},                                  /* 40 */
            {4, -2, -2, 1, 1},                                        /* 41 */
            {4, -2, -2, 1, 1, 1, 1},                                  /* 40000 */
            {4, -2, -2, 1, 1},                                        /* 40010 */
            {4, -2, -2, 1, 1, 1, -4, 2, 2, 4, 1},                     /* 53*/
        };

        int t;

        for (t = 0; t < NUM_TEST; t++)
        {
            printf("\ttesting getdrstemplate() for template %d...", number[t]);
            {
                gtemplate *tmpl;
                int m;

                tmpl = getdrstemplate(number[t]);
                if (!tmpl)
                    return G2C_ERROR;
                if (tmpl->num != number[t] || tmpl->maplen != expected_maplen[t] || tmpl->needext)
                    return G2C_ERROR;
                for (m = 0; m < tmpl->maplen; m++)
                    if (tmpl->map[m] != expected_map[t][m])
                        return G2C_ERROR;
                free(tmpl);
            }
            printf("ok\n");
            printf("\ttesting g2c_get_drs_template() for template %d...", number[t]);
            {
                int maplen, needext;
                int map[G2C_MAX_DRS_TEMPLATE_MAPLEN];
                int m;
                int ret;

                if ((ret = g2c_get_drs_template(number[t], &maplen, map, &needext)))
                    return ret;
                if (maplen != expected_maplen[t] || needext)
                    return G2C_ERROR;
                for (m = 0; m < maplen; m++)
                    if (map[m] != expected_map[t][m])
                        return G2C_ERROR;
            }
            printf("ok\n");
        }
    }
    printf("ok!\n");
    printf("SUCCESS!\n");
    return 0;
}
