# Importing the Kratos Library
import KratosMultiphysics

# Import applications
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication

# Import base class file
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_solver import MechanicalSolver

def CreateSolver(model, custom_settings):
    return ExplicitMechanicalSolver(model, custom_settings)

class ExplicitMechanicalSolver(MechanicalSolver):
    """The structural mechanics explicit dynamic solver.

    This class creates the mechanical solvers for explicit dynamic analysis.

    See structural_mechanics_solver.py for more information.
    """
    def __init__(self, model, custom_settings):
        # Construct the base solver.
        super().__init__(model, custom_settings)
        # Lumped mass-matrix is necessary for explicit analysis
        self.main_model_part.ProcessInfo[KratosMultiphysics.COMPUTE_LUMPED_MASS_MATRIX] = True
        self.delta_time_refresh_counter = self.settings["delta_time_refresh"].GetInt()
        KratosMultiphysics.Logger.PrintInfo("::[ExplicitMechanicalSolver]:: Construction finished")

    @classmethod
    def GetDefaultParameters(cls):
        this_defaults = KratosMultiphysics.Parameters("""{
            "time_integration_method"    : "explicit",
            "scheme_type"                : "central_differences",
            "time_step_prediction_level" : 0,
            "delta_time_refresh"         : 1000,
            "max_delta_time"             : 1.0e0,
            "fraction_delta_time"        : 0.333333333333333333333333333333333333,
            "rayleigh_alpha"             : 0.0,
            "rayleigh_beta"              : 0.0,
            "theta_1"                    : 0.0,
            "theta_2"                    : 0.0,
            "diagonal_critical_damping"  : false,
            "xi_damping"                 : 0.0,
            "l2_tolerance"               : 1.0e-3
        }""")
        this_defaults.AddMissingParameters(super().GetDefaultParameters())
        return this_defaults

    def AddVariables(self):
        super().AddVariables()
        self._add_dynamic_variables()

        scheme_type = self.settings["scheme_type"].GetString()
        if(scheme_type == "central_differences"):
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.MIDDLE_VELOCITY)
            if (self.settings["rotation_dofs"].GetBool()):
                self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.MIDDLE_ANGULAR_VELOCITY)
        if(scheme_type == "multi_stage"):
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.FRACTIONAL_ACCELERATION)
            if (self.settings["rotation_dofs"].GetBool()):
                self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.FRACTIONAL_ANGULAR_ACCELERATION)
        if(scheme_type == "forward_euler_fic" or scheme_type == "symplectic_euler" or scheme_type == "velocity_verlet"):
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.NODAL_DISPLACEMENT_STIFFNESS)
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.NODAL_INERTIA)
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.NODAL_INITIAL_DISPLACEMENT)
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.NODAL_ROTATION_DAMPING)

        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NODAL_MASS)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.FORCE_RESIDUAL)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.RESIDUAL_VECTOR)

        if (self.settings["rotation_dofs"].GetBool()):
            self.main_model_part.AddNodalSolutionStepVariable(StructuralMechanicsApplication.NODAL_INERTIA)
            self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.MOMENT_RESIDUAL)

        KratosMultiphysics.Logger.PrintInfo("::[ExplicitMechanicalSolver]:: Variables ADDED")

    def AddDofs(self):
        super().AddDofs()
        self._add_dynamic_dofs()
        KratosMultiphysics.Logger.PrintInfo("::[ExplicitMechanicalSolver]:: DOF's ADDED")

    def ComputeDeltaTime(self):
        if self.settings["time_step_prediction_level"].GetInt() > 1:
            if self.delta_time_refresh_counter >= self.settings["delta_time_refresh"].GetInt():
                self.delta_time = StructuralMechanicsApplication.CalculateDeltaTime(self.GetComputingModelPart(), self.delta_time_settings)
                self.delta_time_refresh_counter = 0
            else:
                self.delta_time_refresh_counter += 1
        #TODO
        # time = self.main_model_part.ProcessInfo[KratosMultiphysics.TIME]
        # if time <= 250.0:
        #     self.delta_time = 0.0071+0.0055716*time
        #     self.main_model_part.ProcessInfo.SetValue(KratosMultiphysics.DELTA_TIME, self.delta_time)
        #     alpha = 0.339408*time
        #     beta = 1.414-0.001696*time
        #     self.main_model_part.ProcessInfo.SetValue(StructuralMechanicsApplication.RAYLEIGH_ALPHA, alpha)
        #     self.main_model_part.ProcessInfo.SetValue(StructuralMechanicsApplication.RAYLEIGH_BETA, beta)
        # else:
        #     self.delta_time = self.settings["time_stepping"]["time_step"].GetDouble()
        #     self.main_model_part.ProcessInfo.SetValue(KratosMultiphysics.DELTA_TIME, self.settings["time_stepping"]["time_step"].GetDouble())
        #     self.main_model_part.ProcessInfo.SetValue(StructuralMechanicsApplication.RAYLEIGH_ALPHA, self.settings["rayleigh_alpha"].GetDouble())
        #     self.main_model_part.ProcessInfo.SetValue(StructuralMechanicsApplication.RAYLEIGH_BETA, self.settings["rayleigh_beta"].GetDouble())
        return self.delta_time

    def Initialize(self):
        # Using the base Initialize
        super().Initialize()

        # Initilize delta_time
        self.delta_time_settings = KratosMultiphysics.Parameters("""{}""")
        self.delta_time_settings.AddValue("time_step_prediction_level", self.settings["time_step_prediction_level"])
        self.delta_time_settings.AddValue("max_delta_time", self.settings["max_delta_time"])
        if self.settings["time_step_prediction_level"].GetInt() > 0:
            self.delta_time = StructuralMechanicsApplication.CalculateDeltaTime(self.GetComputingModelPart(), self.delta_time_settings)
        else:
            self.delta_time = self.settings["time_stepping"]["time_step"].GetDouble()

    #### Specific internal functions ####
    def _create_solution_scheme(self):
        scheme_type = self.settings["scheme_type"].GetString()
        # print(scheme_type)
        # paraaa

        # Setting the Rayleigh damping parameters
        process_info = self.main_model_part.ProcessInfo
        # process_info[StructuralMechanicsApplication.RAYLEIGH_ALPHA] = self.settings["rayleigh_alpha"].GetDouble()
        # process_info[StructuralMechanicsApplication.RAYLEIGH_BETA] = self.settings["rayleigh_beta"].GetDouble()
        process_info.SetValue(StructuralMechanicsApplication.RAYLEIGH_ALPHA, self.settings["rayleigh_alpha"].GetDouble())
        process_info.SetValue(StructuralMechanicsApplication.RAYLEIGH_BETA, self.settings["rayleigh_beta"].GetDouble())
        process_info.SetValue(StructuralMechanicsApplication.THETA_1, self.settings["theta_1"].GetDouble())
        process_info.SetValue(StructuralMechanicsApplication.THETA_2, self.settings["theta_2"].GetDouble())
        use_rayleigh_damping = True
        if self.settings["diagonal_critical_damping"].GetBool() == True:
            use_rayleigh_damping = False
        process_info.SetValue(StructuralMechanicsApplication.USE_CONSISTENT_MASS_MATRIX, use_rayleigh_damping)
        process_info.SetValue(StructuralMechanicsApplication.XI_DAMPING, self.settings["xi_damping"].GetDouble())
        process_info.SetValue(StructuralMechanicsApplication.SERIAL_PARALLEL_EQUILIBRIUM_TOLERANCE, self.settings["l2_tolerance"].GetDouble())
        process_info.SetValue(KratosMultiphysics.DELTA_TIME, self.settings["time_stepping"]["time_step"].GetDouble())
        # self.main_model_part.ProcessInfo[KratosMultiphysics.DELTA_TIME] = self.settings["time_stepping"]["time_step"].GetDouble()

        # Setting the time integration schemes
        if(scheme_type == "central_differences"):
            mechanical_scheme = StructuralMechanicsApplication.ExplicitCentralDifferencesScheme(self.settings["max_delta_time"].GetDouble(),
                                                                             self.settings["fraction_delta_time"].GetDouble(),
                                                                             self.settings["time_step_prediction_level"].GetDouble())
        elif(scheme_type == "multi_stage"):
            mechanical_scheme = StructuralMechanicsApplication.ExplicitMultiStageKimScheme(self.settings["fraction_delta_time"].GetDouble())
        elif(scheme_type == "forward_euler_fic"):
            mechanical_scheme = StructuralMechanicsApplication.ExplicitForwardEulerFICScheme()
        elif(scheme_type == "symplectic_euler"):
            mechanical_scheme = StructuralMechanicsApplication.ExplicitSymplecticEulerScheme()
        elif(scheme_type == "velocity_verlet"):
            mechanical_scheme = StructuralMechanicsApplication.ExplicitVelocityVerletScheme()
        else:
            err_msg =  "The requested scheme type \"" + scheme_type + "\" is not available!\n"
            err_msg += "Available options are: \"central_differences\", \"multi_stage\", \"forward_euler_fic\""
            raise Exception(err_msg)
        return mechanical_scheme

    def _create_mechanical_solution_strategy(self):
        computing_model_part = self.GetComputingModelPart()
        mechanical_scheme = self.get_solution_scheme()

        mechanical_solution_strategy = StructuralMechanicsApplication.MechanicalExplicitStrategy(computing_model_part,
                                            mechanical_scheme,
                                            self.settings["compute_reactions"].GetBool(),
                                            self.settings["reform_dofs_at_each_step"].GetBool(),
                                            self.settings["move_mesh_flag"].GetBool())

        mechanical_solution_strategy.SetRebuildLevel(0)
        return mechanical_solution_strategy

    #### Private functions ####

