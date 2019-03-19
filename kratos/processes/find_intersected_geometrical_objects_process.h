//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                     Kratos default license: kratos/license.txt
//
//  Main authors:    Vicente Mataix Ferrandiz
//

#if !defined(KRATOS_FIND_INTERSECTED_GEOMETRICAL_OBJECTS_PROCESS_H_INCLUDED )
#define  KRATOS_FIND_INTERSECTED_GEOMETRICAL_OBJECTS_PROCESS_H_INCLUDED

// System includes
#include <string>
#include <iostream>

// External includes

// Project includes
#include "processes/process.h"
#include "containers/model.h"
#include "includes/kratos_parameters.h"
#include "spatial_containers/octree_binary.h"

namespace Kratos
{
namespace Internals {
    /**
     * @class DistanceSpatialContainersConfigure
     * @ingroup KratosCore
     * @brief This class contains the tools related with the distance spatial container cell data
     * @details The CellNodeData is defined as an internal class
     * @tparam TEntity The type of geometrical entity considered (if conditions or elements)
     * @author Pooyan Dadvand
     */
    template<class TEntity = Element>
    class DistanceSpatialContainersConfigure
    {
    public:
        /**
         * @class CellNodeData
         * @ingroup KratosCore
         * @brief This class contains the cell node data
         * @author Pooyan Dadvand
         */
        class CellNodeData
        {
            double mDistance;
            double mCoordinates[3];
            std::size_t mId;
        public:
            double& Distance() { return mDistance; }
            double& X() { return mCoordinates[0]; }
            double& Y() { return mCoordinates[1]; }
            double& Z() { return mCoordinates[2]; }
            double& Coordinate(int i) { return mCoordinates[i]; }
            std::size_t& Id() { return mId; }
        };

        ///@}
        ///@name  Enum's
        ///@{

        enum {
            Dimension = 3,
            DIMENSION = 3,
            MAX_LEVEL = 12,
            MIN_LEVEL = 2    // this cannot be less than 2!!!
        };

        ///@}
        ///@name Type Definitions
        ///@{

        /// Definition of the index type
        typedef std::size_t IndexType;

        /// Definition of the point type
        typedef Point PointType;

        /// Definition of the distance iterator type
        typedef std::vector<double>::iterator DistanceIteratorType;

        /// Definition of the entity container type
        typedef PointerVectorSet<TEntity, IndexedObject> EntityContainerType;

        /// Definition of the container type
        typedef typename EntityContainerType::ContainerType ContainerType;

        /// Defintion of the pointer type
        typedef typename ContainerType::value_type PointerType;

        /// Definition of the ietartor type
        typedef typename ContainerType::iterator IteratorType;

        /// Definition of the node type
        typedef Node<3> NodeType;

        /// Definition of the geometry type
        typedef Geometry<NodeType> GeometryType;

        /// Definition of the cell node data
        typedef CellNodeData cell_node_data_type;

        /// Definition of the cell data type
        typedef std::vector<CellNodeData*> data_type;

        /// The definition of the pointer type
        typedef PointerType pointer_type;

        /// Definition of the pointer type iterator
        typedef typename std::vector<PointerType>::iterator PointerTypeIterator;

        /// Pointer definition of DistanceSpatialContainersConfigure
        KRATOS_CLASS_POINTER_DEFINITION(DistanceSpatialContainersConfigure);

        ///@}
        ///@name Life Cycle
        ///@{

        /// Default constructor.
        DistanceSpatialContainersConfigure() {}

        /// Destructor.
        virtual ~DistanceSpatialContainersConfigure() {}


        ///@}
        ///@name Operators
        ///@{


        ///@}
        ///@name Operations
        ///@{

        /**
         * @brief This method allocates the cell data
         */
        static data_type* AllocateData() {
            return new data_type(27, (CellNodeData*)NULL);
        }

        /**
         * @brief This method copies the data from a cell
         * @param pSource The data cell to be copied
         * @param pDestination The data cell where to copy
         */
        static void CopyData(
            data_type* pSource,
            data_type* pDestination
            )
        {
            *pDestination = *pSource;
        }

        /**
         * @brief This method deletes the data from a cell data
         * @param pData The data cell to be deleted
         */
        static void DeleteData(data_type* pData) {
            delete pData;
        }

        /**
         * @brief This method computes the bounding box of an object
         * @param pObject The pointer to the object
         * @param rLowPoint The lowest point of the box
         * @param rHighPoint The highest point of the box
         */
        static inline void CalculateBoundingBox(
            const PointerType& pObject,
            PointType& rLowPoint,
            PointType& rHighPoint
            )
        {
            // Getting the geoemtry
            auto& r_geometry = pObject->GetGeometry();

            // Initializing the highest and lowest point
            rHighPoint = r_geometry.GetPoint(0);
            rLowPoint = r_geometry.GetPoint(0);

            // Iterating over the nodes
            for (IndexType point = 1; point< r_geometry.PointsNumber(); ++point) {
                const auto& r_point = r_geometry.GetPoint(point);
                for (IndexType i = 0; i < 3; ++i) {
                    rLowPoint[i] = (rLowPoint[i]  >  r_point[i]) ? r_point[i] : rLowPoint[i];
                    rHighPoint[i] = (rHighPoint[i] <  r_point[i]) ? r_point[i] : rHighPoint[i];
                }
            }
        }

        /**
         * @brief This method computes the bounding box of an object (using C arrays)
         * @param pObject The pointer to the object
         * @param rLowPoint The lowest point of the box
         * @param rHighPoint The highest point of the box
         */
        static inline void GetBoundingBox(
            const PointerType pObject,
            double* rLowPoint,
            double* rHighPoint
            )
        {
            // Getting the geoemtry
            auto& r_geometry = pObject->GetGeometry();

            // Initializing the highest and lowest point
            for (IndexType i = 0; i<3; ++i) {
                rLowPoint[i] = r_geometry.GetPoint(0)[i];
                rHighPoint[i] = r_geometry.GetPoint(0)[i];
            }

            // Iterating over the nodes
            for (IndexType point = 1; point< r_geometry.PointsNumber(); ++point) {
                const auto& r_point = r_geometry.GetPoint(point);
                for (IndexType i = 0; i < 3; ++i) {
                    rLowPoint[i] = (rLowPoint[i]  >  r_point[i]) ? r_point[i] : rLowPoint[i];
                    rHighPoint[i] = (rHighPoint[i] <  r_point[i]) ? r_point[i] : rHighPoint[i];
                }
            }
        }

        /**
         * @brief This method computes if there is an intersection between two objects
         * @param pObj1 The pointer to the first object
         * @param pObj2 The pointer to the second object
         * @return True if there is an intersection
         */
        static inline bool Intersection(
            const PointerType& pObj1,
            const PointerType& pObj2
            )
        {
            GeometryType& r_geom_1 = pObj1->GetGeometry();
            GeometryType& r_geom_2 = pObj2->GetGeometry();
            return r_geom_1.HasIntersection(r_geom_2);
        }

        /**
         * @brief This computes the intersection between an object and a box
         * @param pObject The pointer to the object
         * @param rLowPoint The lowest point of the box
         * @param rHighPoint The highest point of the box
         * @return True if there is an intersection
         */
        static inline bool IntersectionBox(
            const PointerType& pObject,
            const PointType& rLowPoint,
            const PointType& rHighPoint
            )
        {
            return pObject->GetGeometry().HasIntersection(rLowPoint, rHighPoint);
        }

        /**
         * @brief This method checks if the objects intersects the low and hight points provided
         * @param pObject The pointer to the object of interest
         * @param Tolerance The tolerance considered
         * @param rLowPoint The lowest point of the box
         * @param rHighPoint The highest point of the box
         */
        static inline bool IsIntersected(
            const PointerType pObject,
            double Tolerance,
            const double* rLowPoint,
            const double* rHighPoint
            )
        {
            PointType low_point(rLowPoint[0] - Tolerance, rLowPoint[1] - Tolerance, rLowPoint[2] - Tolerance);
            PointType high_point(rHighPoint[0] + Tolerance, rHighPoint[1] + Tolerance, rHighPoint[2] + Tolerance);

            KRATOS_ERROR << "Not Implemented method" << std::endl;
//             return HasIntersection(pObject->GetGeometry(), low_point, high_point);
        }

        ///@}
        ///@name Input and output
        ///@{

        /// Turn back information as a string.
        virtual std::string Info() const
        {
            return " Spatial Containers Configure";
        }

        /// Print information about this object.
        virtual void PrintInfo(std::ostream& rOStream) const {}

        /// Print object's data.
        virtual void PrintData(std::ostream& rOStream) const {}

        ///@}

    protected:

    private:

        /// Assignment operator.
        DistanceSpatialContainersConfigure& operator=(DistanceSpatialContainersConfigure const& rOther);

        /// Copy constructor.
        DistanceSpatialContainersConfigure(DistanceSpatialContainersConfigure const& rOther);


    }; // Class DistanceSpatialContainersConfigure

} // manespace Internals

///@addtogroup KratosCore
///@{

///@name Kratos Classes
///@{

/**
 * @class FindIntersectedGeometricalObjectsProcess
 * @ingroup KratosCore
 * @brief This class takes two modelparts and marks the intersected ones with SELECTED flag.
 * @details It creates a spatial datastructure and search for interaction. It also provides some helper methods for derived classes to check individual element or condition interesections.
 * @tparam TEntity The type of geometrical entity considered (if conditions or elements)
 * @todo Add possibility to use conditions with elements and vice versa (add second template argument)
 * @author Pooyan Dadvand
*/
template<class TEntity = Element>
class KRATOS_API(KRATOS_CORE) FindIntersectedGeometricalObjectsProcess
    : public Process
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of FindIntersectedGeometricalObjectsProcess
    KRATOS_CLASS_POINTER_DEFINITION(FindIntersectedGeometricalObjectsProcess);

    /// Octree definitions
    using ConfigurationType = Internals::DistanceSpatialContainersConfigure<TEntity>;
    using CellType = OctreeBinaryCell<ConfigurationType>;
    using OctreeType = OctreeBinary<CellType>;
    using CellNodeDataType = typename ConfigurationType::cell_node_data_type;
    typedef std::vector<typename OctreeType::cell_type*> OtreeCellVectorType;

    /// Definition of the index type
    typedef std::size_t IndexType;

    /// Definition of the size type
    typedef std::size_t SizeType;

    /// Definition of the point type
    typedef Point PointType;

    /// Definition of the node type
    using NodeType = Node<3>;

    /// Definition of the geometry type
    using GeometryType = Geometry<NodeType>;

    /// Definition of the entity container type
    typedef PointerVectorSet<TEntity, IndexedObject> EntityContainerType;

    ///@}
    ///@name Life Cycle
    ///@{

    /**
     * @brief Default constructor.
     * @details Removed
     */
    FindIntersectedGeometricalObjectsProcess() = delete;

    /**
     * @brief Constructor to be used.
     * @param rPart1 First model part (the one to compute the intersection)
     * @param rPart2 Second model part (the "skin" model part)
     */
    FindIntersectedGeometricalObjectsProcess(
        ModelPart& rPart1,
        ModelPart& rPart2
        );

    /**
     * @brief Constructor to be used. (with model and Parameters)
     * @param rModel The model containing all model parts
     * @param ThisParameters The configuration parameters
     */
    FindIntersectedGeometricalObjectsProcess(
        Model& rModel,
        Parameters ThisParameters
        );

    /// Copy constructor.
    FindIntersectedGeometricalObjectsProcess(FindIntersectedGeometricalObjectsProcess const& rOther) = delete;

    /// Destructor.
    ~FindIntersectedGeometricalObjectsProcess() override {}

    ///@name Member Variables
    ///@{

    std::vector<PointerVector<GeometricalObject>> mIntersectedObjects; /// The list of intersected objects

    ///@}
    ///@name Operations
    ///@{

    /**
     * @brief This function is designed for being called at the beginning of the computations right after reading the model and the groups
     * @todo This should be moved to ExecuteInitialize (base class of Process)
     */
    virtual void Initialize();

    /**
     * @brief This method finds the intersected objects with the skin
     * @param rResults The vector containing the intersected objects with the skin
     */
    virtual void FindIntersectedSkinObjects(std::vector<PointerVector<GeometricalObject>>& rResults);

    /**
     * @brief This method finds different intersections
     */
    virtual void FindIntersections();

    /**
     * @brief This method returns the intersections
     * @return The vector containing the intersections found
     */
    virtual std::vector<PointerVector<GeometricalObject>>& GetIntersections();

    /**
     * @brief Returns the first model part
     * @return The first model part
     */
    virtual ModelPart& GetModelPart1();

    /**
     * @brief Returns the second model part
     * @return The second model part
     */
    virtual ModelPart& GetModelPart2();

    /**
     * @brief This method returns the Octree conatined in the class
     * @return The octree contained in this process
     */
    virtual OctreeBinary<OctreeBinaryCell<ConfigurationType>>* GetOctreePointer();

    /**
     * @brief This clears the database
     * @warning This conflicts with flags Clear
     */
    virtual void Clear();

    /**
     * @brief Execute method is used to execute the Process algorithms.
     */
    void Execute() override;

    /**
     * @brief this function is designed for being called at the beginning of the computations right after reading the model and the groups
     */
    void ExecuteInitialize() override;

    /**
     * @brief This method indetifies near entities and marks if intersected
     * @param pEntity The pointer to the entity of interest
     * @param rLeaves The Octree cells vectors
     */
    virtual void IdentifyNearEntitiesAndCheckEntityForIntersection(
        typename TEntity::Pointer pEntity,
        OtreeCellVectorType& rLeaves
        );

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const override {
        return "FindIntersectedGeometricalObjectsProcess";
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override {
        rOStream << Info();
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const override  {

    }

    ///@}
protected:
    ///@name Protected static Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    ModelPart& mrModelPart1;          /// First model part
    ModelPart& mrModelPart2;          /// Second model part
    OctreeType mOctree;               /// The octree structucture that performs the search
    Parameters mThisParameters;       /// The configuration parameters

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{

    /**
     * @brief This method sets the Octree bounding box
     */
    virtual void SetOctreeBoundingBox();

    /**
     * @brief This method marks if intersected
     * @param rEntity1 The entity of interest
     * @param rLeaves The Octree cells vectors
     */
    virtual void MarkIfIntersected(
        TEntity& rEntity1,
        OtreeCellVectorType& rLeaves
        );

    /**
     * @brief This method check if there is an intersection between two geometries
     * @param rFirstGeometry The first geometry
     * @param rSecondGeometry The second geometry
     */
    virtual bool HasIntersection(
        GeometryType& rFirstGeometry,
        GeometryType& rSecondGeometry
        );

    /**
     * @brief This method check if there is an intersection between two geometries in 2D
     * @param rFirstGeometry The first geometry
     * @param rSecondGeometry The second geometry
     */
    virtual bool HasIntersection2D(
        GeometryType& rFirstGeometry,
        GeometryType& rSecondGeometry
        );

    /**
     * @brief This method check if there is an intersection between two geometries in 3D
     * @param rFirstGeometry The first geometry
     * @param rSecondGeometry The second geometry
     */
    virtual bool HasIntersection3D(
        GeometryType& rFirstGeometry,
        GeometryType& rSecondGeometry
        );

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
    ///@name Private Operations
    ///@{

    /**
     * @brief Returns the current working space dimension
     * @return The current working space dimension
     */
    std::size_t WorkingSpaceDimension();

    /**
     * @brief This method generates a new Octree class
     */
    void GenerateOctree();

    /**
     * @brief This method generates a new Octree class (elements)
     */
    void GenerateOctreeElements();

    /**
     * @brief This method generates a new Octree class (conditions)
     */
    void GenerateOctreeConditions();

    /**
     * @brief This method finds intected skin objects
     * @param rEntity1 The entity of interest
     * @param rLeaves The Octree cells vectors
     * @param rResults The expected results
     */
    void FindIntersectedSkinObjects(
        TEntity& rEntity1,
        OtreeCellVectorType& rLeaves,
        PointerVector<GeometricalObject>& rResults
        );

    /**
     * @brief This method provides the defaults parameters to avoid conflicts between the different constructors
     */
    Parameters GetDefaultParameters();

    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    FindIntersectedGeometricalObjectsProcess& operator=(FindIntersectedGeometricalObjectsProcess const& rOther);


    ///@}

}; // Class FindIntersectedGeometricalObjectsProcess

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function
template<class TEntity = Element>
inline std::istream& operator >> (std::istream& rIStream,
                FindIntersectedGeometricalObjectsProcess<TEntity>& rThis);

/// output stream function
template<class TEntity = Element>
inline std::ostream& operator << (std::ostream& rOStream,
                const FindIntersectedGeometricalObjectsProcess<TEntity>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_FIND_INTERSECTED_GEOMETRICAL_OBJECTS_PROCESS_H_INCLUDED  defined
