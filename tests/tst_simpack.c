/* This is a test for the NCEPLIBS-g2c project. This test is for
 * the simpack() and simunpack() functions.
 *
 * Ed Hartnett 10/28/21
 */

#include "grib2_int.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 4
#define PACKED_LEN 40

g2int simunpack(unsigned char *cpack, g2int *idrstmpl, g2int ndpts,
                float *fld);

int
main()
{
    printf("Testing simple packing/unpacking functions.\n");
    printf("Testing simpack() call...");
    {
        g2int ndpts = DATA_LEN;
        float fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
        float fld_in[DATA_LEN];
        unsigned char cpack[PACKED_LEN];
        g2int lcpack;
        g2int idrstmpl[5] = {0, 1, 1, 16, 0};
        int i;

        /* Pack the data. */
        simpack(fld, ndpts, idrstmpl, cpack, &lcpack);

        /* Unpack the data. */
        if (simunpack(cpack, idrstmpl, ndpts, fld_in))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            /* printf("%g %g\n", fld[i], fld_in[i]); */
            if (fld[i] != fld_in[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("Testing simpack() call with constant field..");
    {
        g2int ndpts = DATA_LEN;
        float fld[DATA_LEN] = {3.0, 3.0, 3.0, 3.0};
        float fld_in[DATA_LEN];
        unsigned char cpack[PACKED_LEN];
        g2int lcpack;
        g2int idrstmpl[5] = {0, 1, 1, 16, 0};
        int i;

        /* Pack the data. */
        simpack(fld, ndpts, idrstmpl, cpack, &lcpack);

        /* Unpack the data. */
        if (simunpack(cpack, idrstmpl, ndpts, fld_in))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            /* printf("%g %g\n", fld[i], fld_in[i]); */
            if (fld[i] != fld_in[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("Testing simpack() call with idrstmpl[1] = 1, nbits = 0...");
    {
        g2int ndpts = DATA_LEN;
        float fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
        float fld_in[DATA_LEN];
        unsigned char cpack[PACKED_LEN];
        g2int lcpack;
        g2int idrstmpl[5] = {0, 1, 1, 0, 0};
        int i;

        /* Pack the data. */
        simpack(fld, ndpts, idrstmpl, cpack, &lcpack);

        /* Unpack the data. */
        if (simunpack(cpack, idrstmpl, ndpts, fld_in))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            /* printf("%g %g\n", fld[i], fld_in[i]); */
            if (fld[i] != fld_in[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("Testing simpack() call with idrstmpl[1] = 0, nbits = 0...");
    {
        g2int ndpts = DATA_LEN;
        float fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
        float fld_in[DATA_LEN];
        unsigned char cpack[PACKED_LEN];
        g2int lcpack;
        g2int idrstmpl[5] = {0, 0, 1, 0, 0};
        int i;

        /* Pack the data. */
        simpack(fld, ndpts, idrstmpl, cpack, &lcpack);

        /* Unpack the data. */
        if (simunpack(cpack, idrstmpl, ndpts, fld_in))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            /* printf("%g %g\n", fld[i], fld_in[i]); */
            if (fld[i] != fld_in[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("Testing simpack() call with idrstmpl[1] = 0, nbits = 16...");
    {
        g2int ndpts = DATA_LEN;
        float fld[DATA_LEN] = {1.0, 2.0, 3.0, 0.0};
        float fld_in[DATA_LEN];
        unsigned char cpack[PACKED_LEN];
        g2int lcpack;
        g2int idrstmpl[5] = {0, 0, 1, 16, 0};
        int i;

        /* Pack the data. */
        simpack(fld, ndpts, idrstmpl, cpack, &lcpack);

        /* Unpack the data. */
        if (simunpack(cpack, idrstmpl, ndpts, fld_in))
            return G2C_ERROR;

        for (i = 0; i < DATA_LEN; i++)
        {
            /* printf("%g %g\n", fld[i], fld_in[i]); */
            if (fld[i] != fld_in[i])
                return G2C_ERROR;
        }
    }
    printf("ok!\n");
    printf("SUCCESS!\n");
    return 0;
}
