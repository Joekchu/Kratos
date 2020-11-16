from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7
# Importing the Kratos Library
import KratosMultiphysics
from KratosMultiphysics import eigen_solver_factory

import KratosMultiphysics.IgaApplication as IGA


def Factory(settings, model):
    if not isinstance(settings, KratosMultiphysics.Parameters):
        raise Exception("Expected input shall be a Parameters object, encapsulating a json string")
    return NitscheSupportStabilizationParameterProcess(model, settings["Parameters"])

class NitscheSupportStabilizationParameterProcess(KratosMultiphysics.Process):

    """This class is used in order to compute automatically the Nitsche support stabilization parameters 

    Only the member variables listed below should be accessed directly.

    Public member variables:
    Model -- the container of the different model parts.
    settings -- Kratos parameters containing the settings.
    """

    def __init__(self, model, params):
        """ The default constructor of the class

        Keyword arguments:
        self -- It signifies an instance of a class.
        model -- the container of the different model parts.
        params -- Kratos parameters containing solver settings.
        """

        KratosMultiphysics.Process.__init__(self)

        ## Settings string in json format
        default_parameters = KratosMultiphysics.Parameters("""{
            "model_part_condition_name" : "",
            "model_part_element_name"   : "",
            "write_on_properties"       : true,
            "eigen_values_vector"       : [0.0],
            "eigen_system_settings" : {
                    "solver_type"           : "feast",
                    "echo_level"            : 0,
                    "tolerance"             : 1e-10,
                    "symmetric"             : true,
                    "e_min"                 : 0.0,
                    "e_max"                 : 1.0e9,
                    "number_of_eigenvalues" : 10,
                    "subspace_size"         : 10
            },
            "number_of_weak_DBC" : 2
        }""")

        ## Overwrite the default settings with user-provided parameters
        self.params = params
        self.params.RecursivelyValidateAndAssignDefaults(default_parameters)

        self.new_model = KratosMultiphysics.Model()
        self.model_part = self.new_model.CreateModelPart("new_model_part")

        self.model_part_condition = model[self.params["model_part_condition_name"].GetString()] 
        for cond in self.model_part_condition.Conditions:
           self.model_part.AddCondition(cond)

        self.model_part_element = model[self.params["model_part_element_name"].GetString()]
        for elem in self.model_part_element.Elements:
            self.model_part.AddElement(elem, 0)

    def ExecuteInitializeSolutionStep(self):
        """ This method is executed before starting the loop

        Keyword arguments:
        self -- It signifies an instance of a class.
        """

        # We get the model parts which divide the problem
        current_process_info = self.model_part.ProcessInfo

        # We compute the eigen values
        KratosMultiphysics.Logger.PrintInfo("::[MechanicalSolver]::", "EIGENVALUE_VECTOR not previously computed. Computing automatically, take care")
        eigen_linear_solver = eigen_solver_factory.ConstructSolver(self.params["eigen_system_settings"])
        builder_and_solver = KratosMultiphysics.ResidualBasedBlockBuilderAndSolver(eigen_linear_solver)
        eigen_scheme = IGA.EigensolverNitscheDynamicScheme()

        eigen_solver = IGA.EigensolverSupportNitscheStrategy(self.model_part, eigen_scheme, builder_and_solver)

        eigen_solver.Solve()
        eigenvalue_vector = current_process_info.GetValue(IGA.EIGENVALUE_VECTOR)

        # We compute the new stabilization parameter
        new_stabilization_parameter = eigenvalue_vector[eigenvalue_vector.Size()-1]*4**self.params["number_of_weak_DBC"].GetInt()

        # We set the values
        if self.params["write_on_properties"].GetBool():
            for prop in self.model_part_condition.Properties:
                prop.SetValue(IGA.NITSCHE_STABILIZATION_PARAMETER, new_stabilization_parameter)
                
        else:
            current_process_info.SetValue(IGA.NITSCHE_STABILIZATION_PARAMETER, new_stabilization_parameter)
        
        # set BUILD_LEVEL to 2 for the next step (calculateall)
        self.model_part_condition.ProcessInfo.SetValue(IGA.BUILD_LEVEL,3)
