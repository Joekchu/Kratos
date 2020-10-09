//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license:
//kratos/license.txt
//
//  Main authors:    Ignasi de Pouplana
//
//

#if !defined(KRATOS_EXPLICIT_FORWARD_EULER_FIC_SCHEME_HPP_INCLUDED)
#define KRATOS_EXPLICIT_FORWARD_EULER_FIC_SCHEME_HPP_INCLUDED

/* System includes */
#include <fstream>

/* External includes */

/* Project includes */
#include "solving_strategies/schemes/scheme.h"
#include "utilities/variable_utils.h"
#include "custom_utilities/explicit_integration_utilities.h"

namespace Kratos {

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}

///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * @class ExplicitForwardEulerFICScheme
 * @ingroup StructuralMechanicsApplciation
 * @brief An explicit forward euler scheme with a split of the inertial term
 * @author Ignasi de Pouplana
 */
template <class TSparseSpace,
          class TDenseSpace //= DenseSpace<double>
          >
class ExplicitForwardEulerFICScheme
    : public Scheme<TSparseSpace, TDenseSpace> {

public:
    ///@name Type Definitions
    ///@{

    /// The definition of the base type
    typedef Scheme<TSparseSpace, TDenseSpace> BaseType;

    /// Some definitions related with the base class
    typedef typename BaseType::DofsArrayType DofsArrayType;
    typedef typename BaseType::TSystemMatrixType TSystemMatrixType;
    typedef typename BaseType::TSystemVectorType TSystemVectorType;
    typedef typename BaseType::LocalSystemVectorType LocalSystemVectorType;

    /// The arrays of elements and nodes
    typedef ModelPart::ElementsContainerType ElementsArrayType;
    typedef ModelPart::NodesContainerType NodesArrayType;

    /// Definition of the size type
    typedef std::size_t SizeType;

    /// Definition of the index type
    typedef std::size_t IndexType;

    /// Definition fo the node iterator
    typedef typename ModelPart::NodeIterator NodeIterator;

    /// The definition of the numerical limit
    static constexpr double numerical_limit = std::numeric_limits<double>::epsilon();

    /// Counted pointer of ExplicitForwardEulerFICScheme
    KRATOS_CLASS_POINTER_DEFINITION(ExplicitForwardEulerFICScheme);

    ///@}
    ///@name Life Cycle
    ///@{

    /**
     * @brief Default constructor.
     * @details The ExplicitForwardEulerFICScheme method
     */
    ExplicitForwardEulerFICScheme()
        : Scheme<TSparseSpace, TDenseSpace>() {}

    /** Destructor.
    */
    virtual ~ExplicitForwardEulerFICScheme() {}

    ///@}
    ///@name Operators
    ///@{

    /**
     * @brief This function is designed to be called once to perform all the checks needed
     * on the input provided.
     * @details Checks can be "expensive" as the function is designed
     * to catch user's errors.
     * @param rModelPart The model of the problem to solve
     * @return Zero means  all ok
     */
    int Check(const ModelPart& rModelPart) const override
    {
        KRATOS_TRY;

        BaseType::Check(rModelPart);

        KRATOS_ERROR_IF(rModelPart.GetBufferSize() < 2) << "Insufficient buffer size for Forward Euler Scheme. It has to be >= 2" << std::endl;

        KRATOS_ERROR_IF_NOT(rModelPart.GetProcessInfo().Has(DOMAIN_SIZE)) << "DOMAIN_SIZE not defined on ProcessInfo. Please define" << std::endl;

        return 0;

        KRATOS_CATCH("");
    }

    /**
     * @brief This is the place to initialize the Scheme. This is intended to be called just once when the strategy is initialized
     * @param rModelPart The model of the problem to solve
     */
    void Initialize(ModelPart& rModelPart) override
    {
        KRATOS_TRY

        const ProcessInfo& r_current_process_info = rModelPart.GetProcessInfo();

        // Preparing the time values for the first step (where time = initial_time +
        // dt)
        // mTime.Current = r_current_process_info[TIME] + r_current_process_info[DELTA_TIME];
        mDeltaTime = r_current_process_info[DELTA_TIME];

        /// Working in 2D/3D (the definition of DOMAIN_SIZE is check in the Check method)
        const SizeType dim = r_current_process_info[DOMAIN_SIZE];

        // Initialize scheme
        if (!BaseType::SchemeIsInitialized())
            InitializeExplicitScheme(rModelPart, dim);
        else
            SchemeCustomInitialization(rModelPart, dim);

        BaseType::SetSchemeIsInitialized();

        KRATOS_CATCH("")
    }

    /**
     * @brief It initializes time step solution. Only for reasons if the time step solution is restarted
     * @param rModelPart The model of the problem to solve
     * @param rA LHS matrix
     * @param rDx Incremental update of primary variables
     * @param rb RHS Vector
     * @todo I cannot find the formula for the higher orders with variable time step. I tried to deduce by myself but the result was very unstable
     */
    void InitializeSolutionStep(
        ModelPart& rModelPart,
        TSystemMatrixType& rA,
        TSystemVectorType& rDx,
        TSystemVectorType& rb
        ) override
    {
        KRATOS_TRY

        BaseType::InitializeSolutionStep(rModelPart, rA, rDx, rb);

        InitializeResidual(rModelPart);
        KRATOS_CATCH("")
    }

    /**
     * @brief It initializes the non-linear iteration
     * @param rModelPart The model of the problem to solve
     * @param rA LHS matrix
     * @param rDx Incremental update of primary variables
     * @param rb RHS Vector
     * @todo I cannot find the formula for the higher orders with variable time step. I tried to deduce by myself but the result was very unstable
     */
    void InitializeNonLinIteration(
        ModelPart& rModelPart,
        TSystemMatrixType& rA,
        TSystemVectorType& rDx,
        TSystemVectorType& rb
        ) override
    {
        KRATOS_TRY;

        const ProcessInfo& r_current_process_info = rModelPart.GetProcessInfo();

        const auto it_elem_begin = rModelPart.ElementsBegin();
        #pragma omp parallel for schedule(guided,512)
        for(int i=0; i<static_cast<int>(rModelPart.Elements().size()); ++i) {
            auto it_elem = it_elem_begin + i;
            it_elem->InitializeNonLinearIteration(r_current_process_info);
        }

        const auto it_cond_begin = rModelPart.ConditionsBegin();
        #pragma omp parallel for schedule(guided,512)
        for(int i=0; i<static_cast<int>(rModelPart.Conditions().size()); ++i) {
            auto it_elem = it_cond_begin + i;
            it_elem->InitializeNonLinearIteration(r_current_process_info);
        }

        KRATOS_CATCH( "" );
    }

    /**
     * @brief This method initializes the residual in the nodes of the model part
     * @param rModelPart The model of the problem to solve
     */
    virtual void InitializeResidual(ModelPart& rModelPart)
    {
        KRATOS_TRY

        // The array of nodes
        NodesArrayType& r_nodes = rModelPart.Nodes();

        // Auxiliar values
        const array_1d<double, 3> zero_array = ZeroVector(3);
        // Initializing the variables
        VariableUtils().SetVariable(FORCE_RESIDUAL, zero_array,r_nodes);
        // VariableUtils().SetVariable(NODAL_INERTIA, zero_array,r_nodes);

        KRATOS_CATCH("")
    }

    /**
     * @brief This method initializes some rutines related with the explicit scheme
     * @param rModelPart The model of the problem to solve
     * @param DomainSize The current dimention of the problem
     */
    virtual void InitializeExplicitScheme(
        ModelPart& rModelPart,
        const SizeType DomainSize = 3
        )
    {
        KRATOS_TRY

        /// The array of ndoes
        NodesArrayType& r_nodes = rModelPart.Nodes();

        // The first iterator of the array of nodes
        const auto it_node_begin = rModelPart.NodesBegin();

        /// Initialise the database of the nodes
        #pragma omp parallel for schedule(guided,512)
        for (int i = 0; i < static_cast<int>(r_nodes.size()); ++i) {
            auto it_node = (it_node_begin + i);
            it_node->SetValue(NODAL_MASS, 0.0);
            it_node->SetValue(NODAL_DISPLACEMENT_DAMPING, 0.0);
            array_1d<double, 3>& r_current_aux_velocity = it_node->FastGetSolutionStepValue(NODAL_DISPLACEMENT_STIFFNESS);
            // array_1d<double, 3>& r_previous_aux_velocity = it_node->FastGetSolutionStepValue(NODAL_DISPLACEMENT_STIFFNESS,1);
            array_1d<double, 3>& r_current_residual = it_node->FastGetSolutionStepValue(FORCE_RESIDUAL);
            // array_1d<double, 3>& r_current_inertial_residual = it_node->FastGetSolutionStepValue(NODAL_INERTIA);
            noalias(r_current_aux_velocity) = it_node->FastGetSolutionStepValue(VELOCITY);
            // noalias(r_previous_aux_velocity) = it_node->FastGetSolutionStepValue(VELOCITY,1);
            noalias(r_current_residual) = ZeroVector(3);
            // noalias(r_current_inertial_residual) = ZeroVector(3);
        }

        KRATOS_CATCH("")
    }


     void Predict(
        ModelPart& rModelPart,
        DofsArrayType& rDofSet,
        TSystemMatrixType& A,
        TSystemVectorType& Dx,
        TSystemVectorType& b
    ) override
    {
        KRATOS_TRY;

        this->CalculateAndAddRHS(rModelPart);

        KRATOS_CATCH("")
    }

    /**
     * @brief Performing the update of the solution
     * @param rModelPart The model of the problem to solve
     * @param rDofSet Set of all primary variables
     * @param rA LHS matrix
     * @param rDx incremental update of primary variables
     * @param rb RHS Vector
     */
    void Update(
        ModelPart& rModelPart,
        DofsArrayType& rDofSet,
        TSystemMatrixType& rA,
        TSystemVectorType& rDx,
        TSystemVectorType& rb
        ) override
    {
        KRATOS_TRY
        // The current process info
        const ProcessInfo& r_current_process_info = rModelPart.GetProcessInfo();

        // The array of nodes
        NodesArrayType& r_nodes = rModelPart.Nodes();

        /// Working in 2D/3D (the definition of DOMAIN_SIZE is check in the Check method)
        const SizeType dim = r_current_process_info[DOMAIN_SIZE];

        // Step Update
        // The first step is time =  initial_time ( 0.0) + delta time
        // mTime.Current = r_current_process_info[TIME];
        mDeltaTime = r_current_process_info[DELTA_TIME];

        // The iterator of the first node
        const auto it_node_begin = rModelPart.NodesBegin();

        // Getting dof position
        const IndexType disppos = it_node_begin->GetDofPosition(DISPLACEMENT_X);

        #pragma omp parallel for schedule(guided,512)
        for (int i = 0; i < static_cast<int>(r_nodes.size()); ++i) {
            // Current step information "N+1" (before step update).
            this->UpdateTranslationalDegreesOfFreedom(it_node_begin + i, disppos, dim);

            // TODO
            KRATOS_WATCH((it_node_begin+i)->GetValue(NODAL_DISPLACEMENT_DAMPING))
            KRATOS_WATCH((it_node_begin+i)->GetValue(NODAL_MASS))
        } // for Node parallel

        // TODO: STOP CRITERION
        this->CheckStopCriterion(rModelPart);

        KRATOS_CATCH("")
    }

    void CheckStopCriterion(ModelPart& rModelPart)
    {
        const ProcessInfo& r_current_process_info = rModelPart.GetProcessInfo();
        NodesArrayType& r_nodes = rModelPart.Nodes();
        const auto it_node_begin = rModelPart.NodesBegin();

        double l2_numerator = 0.0;
        double l2_denominator = 0.0;
        #pragma omp parallel for reduction(+:l2_numerator,l2_denominator)
        for (int i = 0; i < static_cast<int>(r_nodes.size()); ++i) {
            NodeIterator itCurrentNode = it_node_begin + i;
            const array_1d<double, 3>& r_current_displacement = itCurrentNode->FastGetSolutionStepValue(DISPLACEMENT);
            const array_1d<double, 3>& r_previous_displacement = itCurrentNode->FastGetSolutionStepValue(DISPLACEMENT,1);
            // array_1d<double, 3> r_exact_displacement;
            // noalias(r_exact_displacement) = ZeroVector(3);
            // if(itCurrentNode->Id()==1){
            //     r_exact_displacement[0] = 0.0;
            // } else if(itCurrentNode->Id()==2){
            //     r_exact_displacement[0] = 4.388134e-5;
            // } else if(itCurrentNode->Id()==3){
            //     r_exact_displacement[0] = 8.776268e-5;
            // } else if(itCurrentNode->Id()==4){
            //     r_exact_displacement[0] = 0.000131644;
            // }
            array_1d<double, 3> delta_displacement;
            noalias(delta_displacement) = r_current_displacement-r_previous_displacement;
            const double norm_2_du = inner_prod(delta_displacement,delta_displacement);
            const double norm_2_u_old = inner_prod(r_previous_displacement,r_previous_displacement);

            l2_numerator += norm_2_du;
            l2_denominator += norm_2_u_old;
        }
        if (l2_denominator > 1.0e-12) {
            double l2_error = std::sqrt(l2_numerator)/std::sqrt(l2_denominator);

            std::fstream l2_error_file;
            l2_error_file.open ("l2_error_time.txt", std::fstream::out | std::fstream::app);
            l2_error_file.precision(12);
            l2_error_file << r_current_process_info[TIME] << " " << l2_error << std::endl;
            l2_error_file.close();

            if (l2_error < r_current_process_info[SERIAL_PARALLEL_EQUILIBRIUM_TOLERANCE]) {
                KRATOS_INFO("STOP CRITERION") << "L2 Error is: " << l2_error << " . The simulation is completed at step: " << r_current_process_info[STEP] << std::endl;
                KRATOS_INFO("STOP CRITERION") << "L2 numerator is: " << std::sqrt(l2_numerator) << " . L2 denominator is: " << std::sqrt(l2_denominator) << std::endl;
                // KRATOS_ERROR << "L2 Error is: " << l2_error << " . The simulation is completed at step: " << r_current_process_info[STEP] << std::endl;
            }
        }
    }

    /**
     * @brief This method updates the translation DoF
     * @param itCurrentNode The iterator of the current node
     * @param DisplacementPosition The position of the displacement dof on the database
     * @param DomainSize The current dimention of the problem
     */
    virtual void UpdateTranslationalDegreesOfFreedom(
        NodeIterator itCurrentNode,
        const IndexType DisplacementPosition,
        const SizeType DomainSize = 3
        )
    {
        array_1d<double, 3>& r_current_aux_velocity = itCurrentNode->FastGetSolutionStepValue(NODAL_DISPLACEMENT_STIFFNESS);
        const array_1d<double, 3>& r_current_residual = itCurrentNode->FastGetSolutionStepValue(FORCE_RESIDUAL);
        const double nodal_mass = itCurrentNode->GetValue(NODAL_MASS);
        const double nodal_damping = itCurrentNode->GetValue(NODAL_DISPLACEMENT_DAMPING);
        // const array_1d<double, 3>& r_current_inertial_residual = itCurrentNode->FastGetSolutionStepValue(NODAL_INERTIA);

        // Solution of the explicit equation:
        if (nodal_mass > numerical_limit){
            // TODO: check algorithm
            // noalias(r_current_aux_velocity) += mDeltaTime * r_current_residual / nodal_mass + mDeltaTime * nodal_damping * r_current_inertial_residual / (nodal_mass * nodal_mass);
            noalias(r_current_aux_velocity) += mDeltaTime * r_current_residual / nodal_mass;
        }
        else{
            noalias(r_current_aux_velocity) = ZeroVector(3);
        }

        array_1d<double, 3>& r_current_displacement = itCurrentNode->FastGetSolutionStepValue(DISPLACEMENT);
        const array_1d<double, 3>& r_previous_displacement = itCurrentNode->FastGetSolutionStepValue(DISPLACEMENT,1);

        std::array<bool, 3> fix_displacements = {false, false, false};
        fix_displacements[0] = (itCurrentNode->GetDof(DISPLACEMENT_X, DisplacementPosition).IsFixed());
        fix_displacements[1] = (itCurrentNode->GetDof(DISPLACEMENT_Y, DisplacementPosition + 1).IsFixed());
        if (DomainSize == 3)
            fix_displacements[2] = (itCurrentNode->GetDof(DISPLACEMENT_Z, DisplacementPosition + 2).IsFixed());

        // Solution of the explicit equation:
        if (nodal_mass > numerical_limit){
            for (IndexType j = 0; j < DomainSize; j++) {
                if (fix_displacements[j] == false) {
                    r_current_displacement[j] = (mDeltaTime * r_current_aux_velocity[j] + r_previous_displacement[j]) / (1.0 + mDeltaTime * nodal_damping/nodal_mass);
                }
            }
        }
        else{
            for (IndexType j = 0; j < DomainSize; j++) {
                if (fix_displacements[j] == false) {
                    r_current_displacement[j] = 0.0;
                }
            }
        }

        const array_1d<double, 3>& r_previous_velocity = itCurrentNode->FastGetSolutionStepValue(VELOCITY,1);
        array_1d<double, 3>& r_current_velocity = itCurrentNode->FastGetSolutionStepValue(VELOCITY);
        array_1d<double, 3>& r_current_acceleration = itCurrentNode->FastGetSolutionStepValue(ACCELERATION);

        noalias(r_current_velocity) = (1.0/mDeltaTime) * (r_current_displacement - r_previous_displacement);
        noalias(r_current_acceleration) = (1.0/mDeltaTime) * (r_current_velocity - r_previous_velocity);
    }

    /**
     * @brief This method performs some custom operations to initialize the scheme
     * @param rModelPart The model of the problem to solve
     * @param DomainSize The current dimention of the problem
     */
    virtual void SchemeCustomInitialization(
        ModelPart& rModelPart,
        const SizeType DomainSize = 3
        )
    {
        KRATOS_TRY

        KRATOS_CATCH("")
    }

    /**
     * @brief This function is designed to calculate just the RHS contribution
     * @param rCurrentElement The element to compute
     * @param RHS_Contribution The RHS vector contribution
     * @param EquationId The ID's of the element degrees of freedom
     * @param rCurrentProcessInfo The current process info instance
     */
    void CalculateRHSContribution(
        Element& rCurrentElement,
        LocalSystemVectorType& RHS_Contribution,
        Element::EquationIdVectorType& EquationId,
        const ProcessInfo& rCurrentProcessInfo
        ) override
    {
        KRATOS_TRY

        this->TCalculateRHSContribution(rCurrentElement, RHS_Contribution, rCurrentProcessInfo);
        KRATOS_CATCH("")
    }

    /**
     * @brief Functions that calculates the RHS of a "condition" object
     * @param rCurrentCondition The condition to compute
     * @param RHS_Contribution The RHS vector contribution
     * @param EquationId The ID's of the condition degrees of freedom
     * @param rCurrentProcessInfo The current process info instance
     */
    void CalculateRHSContribution(
        Condition& rCurrentCondition,
        LocalSystemVectorType& RHS_Contribution,
        Element::EquationIdVectorType& EquationId,
        const ProcessInfo& rCurrentProcessInfo
        ) override
    {
        KRATOS_TRY

        this->TCalculateRHSContribution(rCurrentCondition, RHS_Contribution, rCurrentProcessInfo);

        KRATOS_CATCH("")
    }


    void CalculateAndAddRHS(ModelPart& rModelPart)
    {
        KRATOS_TRY

        const ProcessInfo& r_current_process_info = rModelPart.GetProcessInfo();
        ConditionsArrayType& r_conditions = rModelPart.Conditions();
        ElementsArrayType& r_elements = rModelPart.Elements();

        LocalSystemVectorType RHS_Contribution = LocalSystemVectorType(0);
        Element::EquationIdVectorType equation_id_vector_dummy; // Dummy

        #pragma omp parallel for firstprivate(RHS_Contribution, equation_id_vector_dummy), schedule(guided,512)
        for (int i = 0; i < static_cast<int>(r_conditions.size()); ++i) {
            auto it_cond = r_conditions.begin() + i;
            CalculateRHSContribution(*it_cond, RHS_Contribution, equation_id_vector_dummy, r_current_process_info);
        }

        #pragma omp parallel for firstprivate(RHS_Contribution, equation_id_vector_dummy), schedule(guided,512)
        for (int i = 0; i < static_cast<int>(r_elements.size()); ++i) {
            auto it_elem = r_elements.begin() + i;
            CalculateRHSContribution(*it_elem, RHS_Contribution, equation_id_vector_dummy, r_current_process_info);
        }

        KRATOS_CATCH("")
    }



    ///@}
    ///@name Operations
    ///@{

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Friends
    ///@{

    ///@}

protected:

    ///@}
    ///@name Protected Structs
    ///@{

    /**
     * @brief This struct contains the information related with the increment od time step
     */
    // struct DeltaTimeParameters {
    //     double Maximum;         // Maximum delta time
    //     double Fraction;        // Fraction of the delta time
    // };

    /**
     * @brief This struct contains the details of the time variables
     */
    // struct TimeVariables {
    //     double Current;        // n+1

    //     double Delta;          // Time step
    // };

    ///@name Protected static Member Variables
    ///@{

    // TimeVariables mTime;            /// This struct contains the details of the time variables
    // DeltaTimeParameters mDeltaTime; /// This struct contains the information related with the increment od time step
    double mDeltaTime;

    ///@}
    ///@name Protected member Variables
    ///@{

    ///@}
    ///@name Protected Operators
    ///@{

    /**
    * @brief Functions that calculates the RHS of a "TObjectType" object
    * @param rCurrentEntity The TObjectType to compute
    * @param RHS_Contribution The RHS vector contribution
    * @param rCurrentProcessInfo The current process info instance
    */
    template <typename TObjectType>
    void TCalculateRHSContribution(
        TObjectType& rCurrentEntity,
        LocalSystemVectorType& RHS_Contribution,
        const ProcessInfo& rCurrentProcessInfo
        )
    {
        rCurrentEntity.CalculateRightHandSide(RHS_Contribution, rCurrentProcessInfo);

        rCurrentEntity.AddExplicitContribution(RHS_Contribution, RESIDUAL_VECTOR, FORCE_RESIDUAL, rCurrentProcessInfo);
    }

    ///@}
    ///@name Protected Operations
    ///@{

    ///@}
    ///@name Protected  Access
    ///@{

    ///@}
    ///@name Protected Inquiry
    ///@{

    ///@}
    ///@name Protected LifeCycle
    ///@{

    ///@}

private:
    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private  Access
    ///@{

    ///@}
    ///@name Private Inquiry
    ///@{

    ///@}
    ///@name Un accessible methods
    ///@{

    ///@}

}; /* Class ExplicitForwardEulerFICScheme */

///@}

///@name Type Definitions
///@{

///@}

} /* namespace Kratos.*/

#endif /* KRATOS_EXPLICIT_FORWARD_EULER_FIC_SCHEME_HPP_INCLUDED  defined */
