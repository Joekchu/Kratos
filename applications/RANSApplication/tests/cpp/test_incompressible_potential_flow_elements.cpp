//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya
//

// System includes

// External includes

// Project includes
#include "containers/model.h"
#include "testing/testing.h"

// Application includes
#include "custom_utilities/test_utilities.h"
#include "includes/cfd_variables.h"
#include "rans_application_variables.h"

namespace Kratos
{
namespace Testing
{
namespace
{
ModelPart& RansIncompressiblePotentialFlowVelocity2D3N_SetUp(
    Model& rModel)
{
    const auto add_variables_function = [](ModelPart& rModelPart) {
        rModelPart.AddNodalSolutionStepVariable(VELOCITY_POTENTIAL);
    };

    using namespace RansApplicationTestUtilities;

    auto& r_model_part = CreateScalarVariableTestModelPart(
        rModel, "RansIncompressiblePotentialFlowVelocity2D3N",
        "LineCondition2D2N", add_variables_function, VELOCITY_POTENTIAL, 1);

    // set nodal historical variables
    RandomFillNodalHistoricalVariable(r_model_part, VELOCITY_POTENTIAL, -10.0, 10.0);

    return r_model_part;
}

ModelPart& RansIncompressiblePotentialFlowPressure2D3N_SetUp(
    Model& rModel)
{
    const auto add_variables_function = [](ModelPart& rModelPart) {
        rModelPart.AddNodalSolutionStepVariable(VELOCITY_POTENTIAL);
        rModelPart.AddNodalSolutionStepVariable(PRESSURE_POTENTIAL);
        rModelPart.AddNodalSolutionStepVariable(DENSITY);
    };

    using namespace RansApplicationTestUtilities;

    auto& r_model_part = CreateScalarVariableTestModelPart(
        rModel, "RansIncompressiblePotentialFlowPressure2D3N",
        "LineCondition2D2N", add_variables_function, PRESSURE_POTENTIAL, 1);

    // set nodal historical variables
    RandomFillNodalHistoricalVariable(r_model_part, DENSITY, 2.0, 2.0);
    RandomFillNodalHistoricalVariable(r_model_part, VELOCITY_POTENTIAL, -10.0, 10.0);
    RandomFillNodalHistoricalVariable(r_model_part, PRESSURE_POTENTIAL, -10.0, 10.0);

    return r_model_part;
}

} // namespace

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowVelocity2D3N_EquationIdVector, KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowVelocity2D3N_SetUp(model);

    // Test:
    RansApplicationTestUtilities::TestEquationIdVector<ModelPart::ElementsContainerType>(r_model_part);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowVelocity2D3N_GetDofList, KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowVelocity2D3N_SetUp(model);

    // Test:
    RansApplicationTestUtilities::TestGetDofList<ModelPart::ElementsContainerType>(
        r_model_part, VELOCITY_POTENTIAL);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowVelocity2D3N_CalculateLocalSystem,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowVelocity2D3N_SetUp(model);

    // Test:
    Matrix LHS, ref_LHS(3, 3, 0.0);
    Vector RHS, ref_RHS(3);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateLocalSystem(
        LHS, RHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_RHS[0] = 1.0022880998012695e-01;
    ref_RHS[1] = -5.2221505981325205e+00;
    ref_RHS[2] = 5.1219217881523935e+00;
    ref_LHS(0, 0) = 5.0000000000000000e-01;
    ref_LHS(0, 1) = -5.0000000000000000e-01;
    ref_LHS(1, 0) = -5.0000000000000000e-01;
    ref_LHS(1, 1) = 1.0000000000000000e+00;
    ref_LHS(1, 2) = -5.0000000000000000e-01;
    ref_LHS(2, 1) = -5.0000000000000000e-01;
    ref_LHS(2, 2) = 5.0000000000000000e-01;

    KRATOS_CHECK_VECTOR_NEAR(RHS, ref_RHS, 1e-12);
    KRATOS_CHECK_MATRIX_NEAR(LHS, ref_LHS, 1e-12);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowVelocity2D3N_CalculateLeftHandSide,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowVelocity2D3N_SetUp(model);

    // Test:
    Matrix LHS, ref_LHS(3, 3, 0.0);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateLeftHandSide(
        LHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_LHS(0, 0) = 5.0000000000000000e-01;
    ref_LHS(0, 1) = -5.0000000000000000e-01;
    ref_LHS(1, 0) = -5.0000000000000000e-01;
    ref_LHS(1, 1) = 1.0000000000000000e+00;
    ref_LHS(1, 2) = -5.0000000000000000e-01;
    ref_LHS(2, 1) = -5.0000000000000000e-01;
    ref_LHS(2, 2) = 5.0000000000000000e-01;

    KRATOS_CHECK_MATRIX_NEAR(LHS, ref_LHS, 1e-12);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowVelocity2D3N_CalculateRightHandSide,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowVelocity2D3N_SetUp(model);

    // Test:
    Vector RHS, ref_RHS(3);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateRightHandSide(
        RHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_RHS[0] = 1.0022880998012695e-01;
    ref_RHS[1] = -5.2221505981325205e+00;
    ref_RHS[2] = 5.1219217881523935e+00;

    KRATOS_CHECK_VECTOR_NEAR(RHS, ref_RHS, 1e-12);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowPressure2D3N_EquationIdVector, KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowPressure2D3N_SetUp(model);

    // Test:
    RansApplicationTestUtilities::TestEquationIdVector<ModelPart::ElementsContainerType>(r_model_part);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowPressure2D3N_GetDofList, KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowPressure2D3N_SetUp(model);

    // Test:
    RansApplicationTestUtilities::TestGetDofList<ModelPart::ElementsContainerType>(
        r_model_part, PRESSURE_POTENTIAL);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowPressure2D3N_CalculateLocalSystem,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowPressure2D3N_SetUp(model);

    // Test:
    Matrix LHS, ref_LHS(3, 3, 0.0);
    Vector RHS, ref_RHS(3);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateLocalSystem(
        LHS, RHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_RHS[0] = -4.9568124092657282e+00;
    ref_RHS[1] = 1.0765410550465759e-01;
    ref_RHS[2] = 4.8491583037610697e+00;
    ref_LHS(0, 0) = 5.0000000000000000e-01;
    ref_LHS(0, 1) = -5.0000000000000000e-01;
    ref_LHS(1, 0) = -5.0000000000000000e-01;
    ref_LHS(1, 1) = 1.0000000000000000e+00;
    ref_LHS(1, 2) = -5.0000000000000000e-01;
    ref_LHS(2, 1) = -5.0000000000000000e-01;
    ref_LHS(2, 2) = 5.0000000000000000e-01;

    KRATOS_CHECK_VECTOR_NEAR(RHS, ref_RHS, 1e-12);
    KRATOS_CHECK_MATRIX_NEAR(LHS, ref_LHS, 1e-12);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowPressure2D3N_CalculateLeftHandSide,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowPressure2D3N_SetUp(model);

    // Test:
    Matrix LHS, ref_LHS(3, 3, 0.0);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateLeftHandSide(
        LHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_LHS(0, 0) = 5.0000000000000000e-01;
    ref_LHS(0, 1) = -5.0000000000000000e-01;
    ref_LHS(1, 0) = -5.0000000000000000e-01;
    ref_LHS(1, 1) = 1.0000000000000000e+00;
    ref_LHS(1, 2) = -5.0000000000000000e-01;
    ref_LHS(2, 1) = -5.0000000000000000e-01;
    ref_LHS(2, 2) = 5.0000000000000000e-01;

    KRATOS_CHECK_MATRIX_NEAR(LHS, ref_LHS, 1e-12);
}

KRATOS_TEST_CASE_IN_SUITE(RansIncompressiblePotentialFlowPressure2D3N_CalculateRightHandSide,
                          KratosRansFastSuite)
{
    // Setup:
    Model model;
    auto& r_model_part = RansIncompressiblePotentialFlowPressure2D3N_SetUp(model);

    // Test:
    Vector RHS, ref_RHS(3);
    auto& r_element = r_model_part.Elements().front();
    r_element.CalculateRightHandSide(
        RHS, static_cast<const ProcessInfo&>(r_model_part.GetProcessInfo()));

    // setting reference values
    ref_RHS[0] = -4.9568124092657282e+00;
    ref_RHS[1] = 1.0765410550465759e-01;
    ref_RHS[2] = 4.8491583037610697e+00;

    KRATOS_CHECK_VECTOR_NEAR(RHS, ref_RHS, 1e-12);
}
} // namespace Testing
} // namespace Kratos.
