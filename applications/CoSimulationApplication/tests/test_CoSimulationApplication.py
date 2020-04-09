# Import Kratos "wrapper" for unittests
import KratosMultiphysics
import KratosMultiphysics.KratosUnittest as KratosUnittest

from KratosMultiphysics.CoSimulationApplication.co_simulation_tools import UsingPyKratos
using_pykratos = UsingPyKratos()

try:
    import numpy
    numpy_available = True
except:
    numpy_available = False

from co_simulation_test_factory import TestSmallCoSimulationCases
from co_simulation_test_factory import TestCoSimulationCases
from test_mok_fsi import TestMokFSI
from test_function_callback_utility import TestGenericCallFunction
from test_ping_pong_coupling import TestPingPong
from test_co_sim_io_dummy_solvers import TestCoSimIODummySolvers

if numpy_available:
    from test_coupling_interface_data import TestCouplingInterfaceData
    from test_data_transfer_operators import TestDataTransferOperators
    from test_coupling_operations import TestScalingOperation
    from test_flower_coupling import TestFLOWerCoupling
    from test_sdof_solver import TestSdofSolver
    from test_sdof_static_solver import TestSdofStaticSolver
    from test_convergence_criteria import TestConvergenceCriteria
    from test_convergence_criteria import TestConvergenceCriteriaWrapper
    from test_convergence_accelerators import TestConvergenceAcceleratorWrapper
    from test_co_simulation_coupled_solver import TestCoupledSolverGetSolver

if not using_pykratos:
    from test_cosim_EMPIRE_API import TestCoSim_EMPIRE_API
    from test_co_sim_io_kratos_python_exposure import TestCoSimIOKratosPythonExposure
    import run_cpp_unit_tests


def AssembleTestSuites():
    ''' Populates the test suites to run.

    Populates the test suites to run. At least, it should populate the suites:
    "small", "nighlty" and "all"

    Return
    ------

    suites: A dictionary of suites
        The set of suites with its test_cases added.
    '''
    suites = KratosUnittest.KratosSuites
    ################################################################################
    smallSuite = suites['small'] # These tests are executed by the continuous integration tool
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestGenericCallFunction]))
    if numpy_available:
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCouplingInterfaceData]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestDataTransferOperators]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestScalingOperation]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestSdofSolver]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestSdofStaticSolver]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestConvergenceCriteria]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestConvergenceCriteriaWrapper]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCoupledSolverGetSolver]))
    if not using_pykratos:
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCoSim_EMPIRE_API]))
    if not using_pykratos and numpy_available:
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCoSimIOKratosPythonExposure]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestPingPong]))
        smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestConvergenceAcceleratorWrapper]))


    ################################################################################
    nightSuite = suites['nightly'] # These tests are executed in the nightly build
    nightSuite.addTest(TestMokFSI('test_mok_fsi_mvqn'))
    nightSuite.addTest(TestMokFSI('test_mok_fsi_aitken'))
    nightSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestSmallCoSimulationCases]))

    nightSuite.addTests(smallSuite)

    ################################################################################
    # For very long tests that should not be in nighly and you can use to validate
    validationSuite = suites['validation']
    validationSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCoSimulationCases]))
    validationSuite.addTest(TestMokFSI('test_mok_fsi_mvqn_external_structure'))
    if not using_pykratos and numpy_available:
        validationSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestFLOWerCoupling]))
        validationSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TestCoSimIODummySolvers]))

    ################################################################################
    # Create a test suit that contains all the tests:
    allSuite = suites['all']
    allSuite.addTests(nightSuite) # already contains the smallSuite
    allSuite.addTests(validationSuite)

    return suites


if __name__ == '__main__':
    if not using_pykratos:
        KratosMultiphysics.Logger.PrintInfo("Unittests", "\nRunning cpp unit tests ...")
        run_cpp_unit_tests.run()
        KratosMultiphysics.Logger.PrintInfo("Unittests", "Finished running cpp unit tests!")

    KratosMultiphysics.Logger.PrintInfo("Unittests", "\nRunning python tests ...")
    KratosUnittest.runTests(AssembleTestSuites())
    KratosMultiphysics.Logger.PrintInfo("Unittests", "Finished python tests!")
