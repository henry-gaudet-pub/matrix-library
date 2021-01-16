#include "matrix.h"

void test_transpose()
{
    // test empty matrices
    codesample::matrix<int> m1;
    codesample::matrix<int> m2;
    if (m1.transpose() != m1)
    {
        throw std::runtime_error("empty matrix transpose 1");
    }
    if (m1.transpose() != m2)
    {
        throw std::runtime_error("empty matrix transpose 2");
    }

    // test n != m matrices
    codesample::matrix<int> m3{{1,2,3}};
    codesample::matrix<int> m4{{1}, {2}, {3}};
    codesample::matrix<int> m5{{10}, {2}, {3}};
    codesample::matrix<int> m6{{1,2,3}, {4,5,6}};
    codesample::matrix<int> m6_T{{1,4}, {2,5}, {3,6}};

    if (m3.transpose() != m4)
    {
        throw std::runtime_error("{{1,2,3}} != {{1}, {2}, {3}}");
    }

    m3[0][0] = 10;

    if (m3.transpose() != m5)
    {
        throw std::runtime_error("{{10,2,3}} != {{10}, {2}, {3}}");
    }

    if (m6.transpose() != m6_T)
    {
        throw std::runtime_error("{{1,2,3}, {4,5,6}} != {{1,4}, {2,5}, {3,6}}");
    }

    // test square matrices
    codesample::matrix<int> m7(10, 10);
    codesample::matrix<int> m7_T(10, 10);
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            m7[i][j] = (i*10) + j;
            m7_T[j][i] = (i*10) + j;
        }
    }

    if (m7.transpose() != m7_T)
    {
        throw std::runtime_error("square matrix 1");
    }
}

void test_multiply()
{
    codesample::matrix<int> m0;
    codesample::matrix<int> m1{{1,2,3}};
    codesample::matrix<int> m2{{1}, {2}, {3}};
    codesample::matrix<int> m3{{1,2,3}, {4,5,6}, {7,8,9}};
    codesample::matrix<int> result1{{228}};
    codesample::matrix<int> result2{{1,2,3}, {2,4,6}, {3,6,9}};

    // test multiplying by empty matrix should throw std::out_of_range
    try
    {
        auto result = m0 * m1;
        throw std::runtime_error("multiply by 0");
    }
    catch (std::out_of_range &r)
    {
    }

    // test chain multiplication
    auto m4 = m1 * m3 * m2;
    if (m4 != result1)
    {
        std::cout << "expected:\n" << result1 << "but was:\n" << m4 << std::endl;
        throw std::runtime_error("multiply 1");
    }

    auto m5 = m1.multiply(m3).multiply(m2);
    if (m5 != result1)
    {
        std::cout << "expected:\n" << result1 << "but was:\n" << m5 << std::endl;
        throw std::runtime_error("multiply 2");
    }

    // test multiplication
    auto m6 = m2 * m1;
    if (m6 != result2)
    {
        std::cout << "expected:\n" << result2 << "but was:\n" << m6 << std::endl;
        throw std::runtime_error("multiply 3");
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Testing transpose... ";
    try
    {
        test_transpose();
        std::cout << "passed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "failed: " << e.what() << std::endl;
    }

    std::cout << "Testing multiply... ";
    try
    {
        test_multiply();
        std::cout << "passed" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "failed: " << e.what() << std::endl;
    }

    return 0;
}

