/*
 * File:   PrincipalVariation.h
 *
 */

#ifndef PRINCIPAL_VARIATION_H
#define PRINCIPAL_VARIATION_H

#include "Types.h"
#include "Constants.h"
#include "Move.h"


// PV table
extern Move_t pv_table[MAX_PLY * MAX_PLY];
extern int pv_length[MAX_PLY];

void reset_pv_table();

#endif /* PRINCIPAL_VARIATION_H */
