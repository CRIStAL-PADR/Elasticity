#include <gtest/gtest.h>
#include <Elasticity/FiniteElement[Edge].h>
#include <Elasticity/FiniteElement[Triangle].h>
#include <Elasticity/FiniteElement[Quad].h>
#include <Elasticity/FiniteElement[Tetrahedron].h>
#include <Elasticity/FiniteElement[Hexahedron].h>

namespace elasticity
{

template <class ElementType, class DataTypes>
void testSumWeights(const sofa::Real_t<DataTypes> expected)
{
    using FE = FiniteElement<ElementType, DataTypes>;

    SReal weightSum = 0;
    for (const auto& [q, w] : FE::quadraturePoints())
    {
        weightSum += w;
    }

    EXPECT_DOUBLE_EQ(weightSum, expected);
}

TEST(FiniteElement, edge1dWeights)
{
    testSumWeights<sofa::geometry::Edge, sofa::defaulttype::Vec1Types>(2);
}
TEST(FiniteElement, edge2dWeights)
{
    testSumWeights<sofa::geometry::Edge, sofa::defaulttype::Vec2Types>(2);
}
TEST(FiniteElement, edge3dWeights)
{
    testSumWeights<sofa::geometry::Edge, sofa::defaulttype::Vec3Types>(2);
}

TEST(FiniteElement, triangle2dWeights)
{
    testSumWeights<sofa::geometry::Triangle, sofa::defaulttype::Vec2Types>(0.5);
}
TEST(FiniteElement, triangle3dWeights)
{
    testSumWeights<sofa::geometry::Triangle, sofa::defaulttype::Vec3Types>(0.5);
}

TEST(FiniteElement, quad2dWeights)
{
    testSumWeights<sofa::geometry::Quad, sofa::defaulttype::Vec2Types>(4);
}
TEST(FiniteElement, quad3dWeights)
{
    testSumWeights<sofa::geometry::Quad, sofa::defaulttype::Vec3Types>(4);
}

TEST(FiniteElement, tetra3dWeights)
{
    testSumWeights<sofa::geometry::Tetrahedron, sofa::defaulttype::Vec3Types>(1 / 6.);
}

TEST(FiniteElement, hexa3dWeights)
{
    testSumWeights<sofa::geometry::Hexahedron, sofa::defaulttype::Vec3Types>(8);
}


template <class ElementType, class DataTypes>
void testGradientShapeFunctions(const sofa::type::Vec<FiniteElement<ElementType, DataTypes>::ElementDimension, sofa::Real_t<DataTypes>>& evaluationPoint)
{
    using FE = FiniteElement<ElementType, DataTypes>;
    static constexpr sofa::type::Vec<FE::ElementDimension, sofa::Real_t<DataTypes>> zero;

    const auto N = FE::gradientShapeFunctions(evaluationPoint);

    sofa::type::Vec<FE::NumberOfNodesInElement, SReal> ones;
    std::fill(ones.begin(), ones.end(), 1);

    const auto sum = N.transposed() * ones; //compute the sum of the gradients of all shape functions
    EXPECT_EQ(sum, zero);
}

TEST(FiniteElement, edge1dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec1Types>(sofa::type::Vec1(0.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec1Types>(sofa::type::Vec1(1.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec1Types>(sofa::type::Vec1(-1.));
}

TEST(FiniteElement, edge2dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec2Types>(sofa::type::Vec1(0.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec2Types>(sofa::type::Vec1(1.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec2Types>(sofa::type::Vec1(-1.));
}

TEST(FiniteElement, edge3dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec3Types>(sofa::type::Vec1(0.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec3Types>(sofa::type::Vec1(1.));
    testGradientShapeFunctions<sofa::geometry::Edge, sofa::defaulttype::Vec3Types>(sofa::type::Vec1(-1.));
}

TEST(FiniteElement, triangle2dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Triangle, sofa::defaulttype::Vec2Types>(sofa::type::Vec2(0., 0.));
    testGradientShapeFunctions<sofa::geometry::Triangle, sofa::defaulttype::Vec2Types>(sofa::type::Vec2(1., 1.));
}

TEST(FiniteElement, triangle3dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Triangle, sofa::defaulttype::Vec3Types>(sofa::type::Vec2(0., 0.));
    testGradientShapeFunctions<sofa::geometry::Triangle, sofa::defaulttype::Vec3Types>(sofa::type::Vec2(1., 1.));
}

TEST(FiniteElement, quad2dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Quad, sofa::defaulttype::Vec2Types>(sofa::type::Vec2(0., 0.));
    testGradientShapeFunctions<sofa::geometry::Quad, sofa::defaulttype::Vec2Types>(sofa::type::Vec2(1., 1.));
}

TEST(FiniteElement, quad3dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Quad, sofa::defaulttype::Vec3Types>(sofa::type::Vec2(0., 0.));
    testGradientShapeFunctions<sofa::geometry::Quad, sofa::defaulttype::Vec3Types>(sofa::type::Vec2(1., 1.));
}

TEST(FiniteElement, tetra3dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Tetrahedron, sofa::defaulttype::Vec3Types>(sofa::type::Vec3(0., 0., 0.));
    testGradientShapeFunctions<sofa::geometry::Tetrahedron, sofa::defaulttype::Vec3Types>(sofa::type::Vec3(1., 1., 1.));
}

TEST(FiniteElement, hexa3dGradientShapeFunctions)
{
    testGradientShapeFunctions<sofa::geometry::Hexahedron, sofa::defaulttype::Vec3Types>(sofa::type::Vec3(0., 0., 0.));
    testGradientShapeFunctions<sofa::geometry::Hexahedron, sofa::defaulttype::Vec3Types>(sofa::type::Vec3(1., 1., 1.));
}



}
