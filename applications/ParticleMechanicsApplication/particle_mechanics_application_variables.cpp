//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Bodhinanda Chandra
//
//


#include "particle_mechanics_application_variables.h"

namespace Kratos
{
    // Unused variables
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( NODAL_INTERNAL_FORCE )

    // Element
    KRATOS_CREATE_VARIABLE( int, MP_MATERIAL_ID )
    KRATOS_CREATE_VARIABLE( int, PARTICLES_PER_ELEMENT )
    KRATOS_CREATE_VARIABLE( double, MP_MASS )
    KRATOS_CREATE_VARIABLE( double, MP_DENSITY )
    KRATOS_CREATE_VARIABLE( double, MP_VOLUME )
    KRATOS_CREATE_VARIABLE( double, MP_POTENTIAL_ENERGY )
    KRATOS_CREATE_VARIABLE( double, MP_KINETIC_ENERGY )
    KRATOS_CREATE_VARIABLE( double, MP_STRAIN_ENERGY )
    KRATOS_CREATE_VARIABLE( double, MP_TOTAL_ENERGY )
    KRATOS_CREATE_VARIABLE( double, MP_PRESSURE )
    KRATOS_CREATE_VARIABLE( double, PRESSURE_REACTION )
    KRATOS_CREATE_VARIABLE( double, MP_DELTA_PLASTIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, MP_DELTA_PLASTIC_VOLUMETRIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, MP_DELTA_PLASTIC_DEVIATORIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, MP_EQUIVALENT_PLASTIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, MP_ACCUMULATED_PLASTIC_VOLUMETRIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, MP_ACCUMULATED_PLASTIC_DEVIATORIC_STRAIN )
    KRATOS_CREATE_VARIABLE( double, NODAL_MPRESSURE )

    // Constitutive Law
    KRATOS_CREATE_VARIABLE( ConstitutiveLaw::Pointer, CONSTITUTIVE_LAW_POINTER )
    // CL: Solid
    KRATOS_CREATE_VARIABLE( double, RAYLEIGH_ALPHA )
    KRATOS_CREATE_VARIABLE( double, RAYLEIGH_BETA )
    // CL: Mohr Coulomb
    KRATOS_CREATE_VARIABLE( double, COHESION )
    KRATOS_CREATE_VARIABLE( double, INTERNAL_DILATANCY_ANGLE )
    // CL: Mohr Coulomb Strain Softening
    KRATOS_CREATE_VARIABLE( double, INTERNAL_FRICTION_ANGLE_RESIDUAL )
    KRATOS_CREATE_VARIABLE( double, COHESION_RESIDUAL )
    KRATOS_CREATE_VARIABLE( double, INTERNAL_DILATANCY_ANGLE_RESIDUAL )
    KRATOS_CREATE_VARIABLE( double, SHAPE_FUNCTION_BETA )

    // Nodal DOFs
    // Conditions
    //KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( IMPOSED_DISPLACEMENT )
    // Nodal load variables
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(POINT_LOAD)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LINE_LOAD)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(SURFACE_LOAD)

    // MP element variable
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( MP_COORD )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( MP_DISPLACEMENT )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( MP_VELOCITY )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( MP_ACCELERATION )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( MP_VOLUME_ACCELERATION )
    KRATOS_CREATE_VARIABLE( Vector, MP_CAUCHY_STRESS_VECTOR )
    KRATOS_CREATE_VARIABLE( Vector, MP_ALMANSI_STRAIN_VECTOR )

    // Grid node variable
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( NODAL_MOMENTUM)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( NODAL_INERTIA)

}