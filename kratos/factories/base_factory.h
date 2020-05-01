//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Vicente Mataix Ferrandiz
//

#if !defined(KRATOS_BASE_FACTORY_H_INCLUDED )
#define  KRATOS_BASE_FACTORY_H_INCLUDED

// System includes

// External includes

// Project includes
#include "includes/define.h"
#include "includes/kratos_parameters.h"
#include "includes/kratos_components.h"
#include "includes/shared_pointers.h"
#include "linear_solvers/linear_solver.h"
#include "solving_strategies/schemes/scheme.h"
#include "solving_strategies/strategies/solving_strategy.h"
#include "solving_strategies/builder_and_solvers/builder_and_solver.h"
#include "solving_strategies/convergencecriterias/convergence_criteria.h"
#include "spaces/ublas_space.h"

namespace Kratos
{
///@name Type Definitions
///@{

typedef TUblasSparseSpace<double> SparseSpaceType;
typedef TUblasDenseSpace<double> LocalSpaceType;
typedef LinearSolver<SparseSpaceType, LocalSpaceType> LinearSolverType;

///@}
///@name Kratos Classes
///@{

/**
 * @class BaseFactoryMethods
 * @ingroup KratosCore
 * @brief Here we define some common methods
 * @details Defines the base class factory methods
 * @author Vicente Mataix Ferrandiz
 */
class BaseFactoryMethods
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of BaseFactoryMethods
    KRATOS_CLASS_POINTER_DEFINITION(BaseFactoryMethods);

    ///@}
    ///@name Life Cycle
    ///@{

    /** Constructor.
     */
    explicit BaseFactoryMethods(){}

    /** Destructor.
     */
    virtual ~BaseFactoryMethods(){}

    ///@}
    ///@name Operations
    ///@{

    /**
     * @brief This method checks if the linear class is registered
     * @param rClassName The nanme of the class
     * @return True if registered, false otherwise
     */
    virtual bool Has(const std::string& rClassName) const
    {
        KRATOS_ERROR << "Methods must be implemented in the base class" << std::endl;
        return false;
    }

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    virtual std::string Info() const
    {
        return "BaseFactoryMethods";
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << this->Info() << std::endl;
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const
    {
//         rOStream << this->Info() << std::endl;
    }
};

/**
 * @class BaseFactory
 * @ingroup KratosCore
 * @brief Here we add the functions needed for the registration of class
 * @details Defines the base class factory
 * @author Vicente Mataix Ferrandiz
 * @tparam TClass The class to create the factory
 * @tparam TAuxiliarClass The auxiliar class to create the factory
 */
template<typename TClass, typename TAuxiliarClass = TClass>
class BaseFactory
    : public BaseFactoryMethods
{
public:
    ///@name Type Definitions
    ///@{

    /// The definition of the custom class
    typedef BaseFactory<TClass, TAuxiliarClass> FactoryType;

    /// The definition of the class
    typedef TClass ClassType;

    /// The definition of the auxiliar class
    typedef TAuxiliarClass AuxiliarClassType;

    /// Pointer definition of BaseFactory
    KRATOS_CLASS_POINTER_DEFINITION(BaseFactory);

    ///@}
    ///@name Life Cycle
    ///@{

    /** Constructor.
     */
    explicit BaseFactory(){}

    /** Destructor.
     */
    virtual ~BaseFactory(){}

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    /**
     * @brief This method checks if the linear class is registered
     * @param rClassName The nanme of the class
     * @return True if registered, false otherwise
     */
    bool Has(const std::string& rClassName) const override
    {
        return KratosComponents<ClassType>::Has( rClassName );
    }

    /**
     * @brief This method creates a new class
     * @param rModel The model containing the problem
     * @param Settings The settings of the factory
     * @return The pointer to the class of interest
     */
    template<typename = std::enable_if<std::is_same<TAuxiliarClass, TClass>::value>>
    typename ClassType::Pointer Create(Kratos::Parameters Settings) const
    {
        const std::string& r_name = Settings["name"].GetString();
        KRATOS_ERROR_IF_NOT(Has( r_name )) << "Trying to construct a class with type name= " << r_name << std::endl <<
                                            "Which does not exist. The list of available options (for currently loaded applications) is: " << std::endl <<
                                            KratosComponents<ClassType>() << std::endl;
        const ClassType& aux = KratosComponents<ClassType>::Get( r_name );
        return aux.Create(Settings);
    }

    /**
     * @brief This method creates a new class
     * @param rModel The model containing the problem
     * @param Settings The settings of the factory
     * @return The pointer to the class of interest
     */
    template<typename = std::enable_if<std::is_same<TAuxiliarClass, Model>::value>>
    typename ClassType::Pointer Create(Model& rModel, Kratos::Parameters Settings) const
    {
        const std::string& r_name = Settings["name"].GetString();
        KRATOS_ERROR_IF_NOT(Has( r_name )) << "Trying to construct a class with type name= " << r_name << std::endl <<
                                            "Which does not exist. The list of available options (for currently loaded applications) is: " << std::endl <<
                                            KratosComponents<ClassType>() << std::endl;
        const ClassType& aux = KratosComponents<ClassType>::Get( r_name );
        return aux.Create(rModel, Settings);
    }

    /**
     * @brief This method creates a new class
     * @param rModelPart The model part containing the problem
     * @param Settings The settings of the factory
     * @return The pointer to the class of interest
     */
    template<typename = std::enable_if<std::is_same<TAuxiliarClass, ModelPart>::value>>
    typename ClassType::Pointer Create(ModelPart& rModelPart, Kratos::Parameters Settings) const
    {
        const std::string& r_name = Settings["name"].GetString();
        KRATOS_ERROR_IF_NOT(Has( r_name )) << "Trying to construct a class with type name= " << r_name << std::endl <<
                                            "Which does not exist. The list of available options (for currently loaded applications) is: " << std::endl <<
                                            KratosComponents<ClassType>() << std::endl;
        const ClassType& aux = KratosComponents<ClassType>::Get( r_name );
        return aux.Create(rModelPart, Settings);
    }

    /**
     * @brief This method creates a new class
     * @param pLinearSolver The pointer to the linear solver
     * @param Settings The settings of the factory
     * @return The pointer to the class of interest
     */
    template<typename = std::enable_if<std::is_same<TAuxiliarClass, LinearSolverType>::value>>
    typename ClassType::Pointer Create(typename LinearSolverType::Pointer pLinearSolver, Kratos::Parameters Settings) const
    {
        const std::string& r_name = Settings["name"].GetString();
        KRATOS_ERROR_IF_NOT(Has( r_name )) << "Trying to construct a class with type name= " << r_name << std::endl <<
                                            "Which does not exist. The list of available options (for currently loaded applications) is: " << std::endl <<
                                            KratosComponents<ClassType>() << std::endl;
        const ClassType& aux = KratosComponents<ClassType>::Get( r_name );
        return aux.Create(pLinearSolver, Settings);
    }

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const override
    {
        return "BaseFactory";
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << this->Info() << std::endl;
        const auto factory_components = KratosComponents<FactoryType>::GetComponents();
        for (const auto& r_comp : factory_components) {
            rOStream << "\t" << r_comp.first << std::endl;
        }
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const override
    {
//         rOStream << this->Info() << std::endl;
//         const auto factory_components = KratosComponents<FactoryType>::GetComponents();
//         for (const auto& r_comp : factory_components) {
//             rOStream << "\t" << r_comp.first << std::endl;
//         }
    }

    ///@}
};

///@}
///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

/// output stream function
template<class TClass, typename TAuxiliarClass>
inline std::ostream& operator << (std::ostream& rOStream,
                                  const BaseFactory<TClass, TAuxiliarClass>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}

///@}

typedef SolvingStrategy<SparseSpaceType, LocalSpaceType, LinearSolverType> SolvingStrategyType;
typedef BuilderAndSolver<SparseSpaceType, LocalSpaceType, LinearSolverType> BuilderAndSolverType;
typedef Scheme<SparseSpaceType,LocalSpaceType> SchemeType;
typedef ConvergenceCriteria<SparseSpaceType,LocalSpaceType> ConvergenceCriteriaType;

KRATOS_API_EXTERN template class KRATOS_API(KRATOS_CORE) KratosComponents<SolvingStrategyType>;

#ifdef KRATOS_REGISTER_STRATEGY
#undef KRATOS_REGISTER_STRATEGY
#endif
#define KRATOS_REGISTER_STRATEGY(name, reference) \
    KratosComponents<SolvingStrategyType>::Add(name, reference);

KRATOS_API_EXTERN template class KRATOS_API(KRATOS_CORE) KratosComponents<BuilderAndSolverType>;

#ifdef KRATOS_REGISTER_BUILDER_AND_SOLVER
#undef KRATOS_REGISTER_BUILDER_AND_SOLVER
#endif
#define KRATOS_REGISTER_BUILDER_AND_SOLVER(name, reference) \
    KratosComponents<BuilderAndSolverType>::Add(name, reference);

KRATOS_API_EXTERN template class KRATOS_API(KRATOS_CORE) KratosComponents<SchemeType>;

#ifdef KRATOS_REGISTER_SCHEME
#undef KRATOS_REGISTER_SCHEME
#endif
#define KRATOS_REGISTER_SCHEME(name, reference) \
    KratosComponents<SchemeType>::Add(name, reference);

KRATOS_API_EXTERN template class KRATOS_API(KRATOS_CORE) KratosComponents<ConvergenceCriteriaType>;

#ifdef KRATOS_REGISTER_CONVERGENCE_CRITERIA
#undef KRATOS_REGISTER_CONVERGENCE_CRITERIA
#endif
#define KRATOS_REGISTER_CONVERGENCE_CRITERIA(name, reference) \
    KratosComponents<ConvergenceCriteriaType>::Add(name, reference);

}  // namespace Kratos.

#endif // KRATOS_BASE_FACTORY_H_INCLUDED  defined
