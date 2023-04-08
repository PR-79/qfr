#include "CircuitOptimizer.hpp"
#include "QuantumComputation.hpp"
#include "dd/FunctionalityConstruction.hpp"
#include "dd/Simulation.hpp"

#include "gtest/gtest.h"

TEST(DDReduceOperator, DDReduceTranspose_Test1) {
    // Unitary matrix
    const auto inputMatrix = dd::CMat {{dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {-dd::SQRT2_2, dd::SQRT2_2, 0, 0},
                                        {0, 0, dd::SQRT2_2, -dd::SQRT2_2},
                                        {0, 0, dd::SQRT2_2, dd::SQRT2_2}};

    const dd::QubitCount nrQubits = 2;
    const auto ddo = std::make_unique<dd::Package<>>(nrQubits);

    dd::mEdge regular_dd = ddo->makeDDFromMatrix(inputMatrix);
    std::cout << "-----------------------------" << std::endl;
    // std::cout << "redconstructed matrix of regular dd:" << std::endl;
    // ddo->printMatrix(regular_dd);
    // std::cout << std::endl;
    auto regular_matrix = ddo->getMatrix(regular_dd);
    EXPECT_EQ(inputMatrix, regular_matrix);

    const auto reduced_dd = ddo->reduceTranspose(regular_dd);
    // TODO: extend other print mat function in package class
    // std::cout << "redconstructed matrix of reduced dd:" << std::endl;
    // ddo->printMatrix(reduced_dd);
    // std::cout << std::endl;
    auto reduced_dd_matrix = ddo->getMatrix(reduced_dd);
    EXPECT_EQ(inputMatrix, reduced_dd_matrix);

    auto num_nodes_reduced_dd = ddo->size(reduced_dd);
    EXPECT_EQ(3, num_nodes_reduced_dd);

    std::ostringstream oss{};
    std::string reduced_dd_reference = "1\n0.70710678118654757\n0 0 (-1 1) (-1 -1) (-1 1) (-1 1)\n1 1 (0 1T) () () (0 1)\n";
    dd::serialize(reduced_dd, oss, false);
    auto serialized_reduced_dd = oss.str();
    std::cout << "serialized reduced dd:" << std::endl << serialized_reduced_dd;
    EXPECT_EQ(reduced_dd_reference, serialized_reduced_dd);

    std::cout << "-----------------------------" << std::endl;

}



