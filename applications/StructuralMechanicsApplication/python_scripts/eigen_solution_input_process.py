import KratosMultiphysics
import KratosMultiphysics.HDF5Application as KratosHDF5
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication

def Factory(settings, Model):
    if not isinstance(settings, KratosMultiphysics.Parameters):
        raise Exception("expected input shall be a Parameters object, encapsulating a json string")
    return EigenSolutionInputProcess(Model, settings["Parameters"])

class EigenSolutionInputProcess(KratosMultiphysics.Process):
    """A process for writing eigenvalue and eigenvector results."""

    def __init__(self, Model, settings):
        KratosMultiphysics.Process.__init__(self)
        default_settings = KratosMultiphysics.Parameters("""
            {
                "model_part_name" : "PLEASE_SPECIFY_MODEL_PART",
                "file_settings" : {
                },
                "prefix" : "/EigenResults"
            }
            """)
        self.settings = settings.Clone()
        self.settings.ValidateAndAssignDefaults(default_settings)
        self._model_part = Model[self.settings["model_part_name"].GetString()]

    def ExecuteInitialize(self):
        hdf5_file = self._GetFile()
        prefix = self.settings["prefix"].GetString()
        KratosHDF5.ReadDataValueContainer(hdf5_file, prefix, self._model_part.ProcessInfo)
        nodal_io_settings = KratosMultiphysics.Parameters("""
            {
                "list_of_variables": ["EIGENVECTOR_MATRIX"],
                "prefix" : ""
            }
            """)
        nodal_io_settings["prefix"].SetString(prefix)
        non_historical_nodal_io = KratosHDF5.HDF5NonHistoricalNodalValueIO(nodal_io_settings, hdf5_file)
        non_historical_nodal_io.ReadNodalResults(self._model_part.Nodes, self._model_part.GetCommunicator())


    # def ExecuteFinalize(self):
    #     hdf5_file = self._GetFile()
    #     prefix = self.settings["prefix"].GetString()
    #     KratosHDF5.WriteDataValueContainer(hdf5_file, prefix, self._model_part.ProcessInfo)
    #     nodal_io_settings = KratosMultiphysics.Parameters("""
    #         {
    #             "list_of_variables": ["EIGENVECTOR_MATRIX"],
    #             "prefix" : ""
    #         }
    #         """)
    #     nodal_io_settings["prefix"].SetString(prefix)
    #     non_historical_nodal_io = KratosHDF5.HDF5NonHistoricalNodalValueIO(nodal_io_settings, hdf5_file)
    #     non_historical_nodal_io.WriteNodalResults(self._model_part.Nodes)

    def _GetFile(self):
        return KratosHDF5.HDF5FileSerial(self.settings["file_settings"])
