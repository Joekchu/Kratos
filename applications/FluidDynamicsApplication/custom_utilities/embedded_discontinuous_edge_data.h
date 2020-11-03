//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Ruben Zorrilla
//

#if !defined(KRATOS_EMBEDDED_DISCONTINUOUS_EDGE_DATA_H)
#define KRATOS_EMBEDDED_DISCONTINUOUS_EDGE_DATA_H

#include "fluid_dynamics_application_variables.h"
#include "custom_utilities/fluid_element_data.h"
#include "custom_utilities/embedded_discontinuous_data.h"

namespace Kratos {

///@addtogroup FluidDynamicsApplication
///@{

///@name Kratos classes
///@{

template< class TFluidData >
class EmbeddedDiscontinuousEdgeData : public EmbeddedDiscontinuousData<TFluidData>
{
public:

///@name Type Definitions
///@{

using typename TFluidData::NodalScalarData;
using typename TFluidData::NodalVectorData;

typedef array_1d<double, (TFluidData::Dim - 1) * 3> EdgeScalarData;

using typename EmbeddedDiscontinuousData<TFluidData>::ShapeFunctionsGradientsType;
using typename EmbeddedDiscontinuousData<TFluidData>::InterfaceNormalsType;

///@}
///@name Public Members
///@{

EdgeScalarData EdgeDistances;
size_t NumPositiveEdges;

///@}
///@name Public Operations
///@{

/**
 * @brief Discontinuous embedded formulation data container initialization
 * This method initializes the discontinuous embedded formulation data container. This implies to intialize
 * the base formulation data container as well as to get the elemental distances from the elemental variable
 * ELEMENTAL_DISTANCES and to get the ELEMENTAL_EDGE_DISTANCES
 * (note that this requires the ELEMENTAL_DISTANCES and ELEMENTAL_EDGE_DISTANCES to be set before this operation).
 * @see CalculateDiscontinuousEdgeDistanceToSkinProcess
 * @param rElement reference to the element that owns the data container
 * @param rProcessInfo reference to the current ProcessInfo container
 */
void Initialize(
    const Element& rElement,
    const ProcessInfo& rProcessInfo) override
{
    EmbeddedDiscontinuousData<TFluidData>::Initialize(rElement, rProcessInfo);
    //this->FillFromElementData(EdgeDistances, ELEMENTAL_EDGE_DISTANCES, rElement);  //INFO: no matching method tin fluid_element_data
    EdgeDistances = rElement.GetValue(ELEMENTAL_EDGE_DISTANCES);

    NumPositiveEdges = 0;
}

/**
 * @brief Discontinous embedded formulation data container check
 * Simple discontinuous embedded formulation data container check. The base formulation data container is
 * checked as well. Returns 0 if the check process succeeds.
 * @param rElement reference to the element that owns the data container
 * @param rProcessInfo reference to the current ProcessInfo container
 * @return int returns 0 if the check process succeeds
 */
static int Check(
    const Element& rElement,
    const ProcessInfo& rProcessInfo)
{
    KRATOS_CHECK_VARIABLE_KEY(SLIP_LENGTH);
    KRATOS_CHECK_VARIABLE_KEY(PENALTY_COEFFICIENT);
    KRATOS_CHECK_VARIABLE_KEY(ELEMENTAL_DISTANCES);
    KRATOS_CHECK_VARIABLE_KEY(ELEMENTAL_EDGE_DISTANCES);

    int out = TFluidData::Check(rElement,rProcessInfo);
    return out;
}

/** TODO: what is the definition of incised we consider?? min 2 edges in 3D?
 * @brief Checks if the current element is incised (not intersected completely)
 * Checks if the current element is incised by checking the number of positive distance edges.
 * @return true if the element is incised
 * @return false if the element is not incised
 */
bool IsIncised()
{
    return (NumPositiveEdges > 0);
}

///@}

};

///@}

///@}

}

#endif