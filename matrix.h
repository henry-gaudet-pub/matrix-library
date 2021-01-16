/**
 * @file matrix.h
 * @author henry gaudet (henrygaudet88@gmail.com)
 * @brief A simple matrix library
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

/**
 * @brief Main library namespace
 * 
 */
namespace codesample
{
    /**
     * @brief Exception thrown when vector dimensions don't match for 
     * the requested operation
     * 
     */
    class invalid_dimension : public std::exception
    {
      private:
        std::string message;

      public:
        /**
         * @brief Construct a new invalid dimension exception with a custom message
         * 
         * @param msg The custom message
         */
        invalid_dimension(const char * msg)
        : message(msg)
        {
        }

        /**
         * @brief Construct a new invalid dimension exception with the vector sizes
         * 
         * @param s1 Size of vector 1
         * @param s2 Size of vector 2
         */
        invalid_dimension(size_t s1, size_t s2)
        : message("Invalid vector dimensions: "
                  + std::to_string(s1) + " != " + std::to_string(s2))
        {
        }

        const char * what() const throw()
        {
            return message.c_str();
        }
    };

    /**
     * @brief Computes the dot product of two vectors
     * 
     * @tparam T The type of data to compute the dot product on.
     * Must support addition (operator+) and multiplication (operator*)
     * @param v1 The first vector
     * @param v2 The second vector
     * @return T The computed dot product
     */
    template <class T>
    static T dot(const std::vector<T> &v1, const std::vector<T> &v2) 
    {
        if (v1.size() != v2.size())
        {
            throw invalid_dimension(v1.size(), v2.size());
        }

        T result = T();
        for (size_t i = 0; i < v1.size(); i++)
        {
            result += (v1.at(i) * v2.at(i));
        }

        return result;
    }

    /**
     * @brief A class representing a 2-dimensional matrix of objects
     * 
     * @tparam T The type of data in this matrix.
     * Must support addition (operator+), multiplication (operator*), and stream extraction (opertaor<<)
     */
    template<class T>
    class matrix
    {
      private:
        std::vector<std::vector<T>> _data;
        std::list<matrix<T>> _cache;

      public:
       /**
        * @brief Construct a new matrix object
        * 
        */
        matrix() = default;

        /**
         * @brief Construct a new mxn matrix
         * 
         * @param rows The number of rows
         * @param cols The number of columns
         * @param value The default value to populate the matrix with
         */
        matrix(size_t rows, size_t cols, T value = T())
        {
            std::vector<T> row;
            row.reserve(cols);
            for (size_t j = 0; j < cols; j++)
            {
                row.insert(row.end(), value);
            }

            _data.reserve(rows);
            for (size_t i = 0; i < rows; i++)
            {
                _data.insert(_data.end(), row);
            }
        }

        /**
         * @brief Construct a new matrix object from an initializer list
         * 
         * @param new_data The values to populate the matrix with
         */
        matrix(std::initializer_list<std::initializer_list<T>> new_data)
        {
            _data.reserve(new_data.size());
            for (auto &row : new_data)
            {
                _data.push_back(row);
            }
        }

        /**
         * @brief Construct a new matrix object from a 2-dimensional vector
         * 
         * @param new_data The values to populate the matrix with
         */
        matrix(std::vector<std::vector<T>> &new_data)
        : _data(new_data)
        {
        }

        /**
         * @brief Gets the number of rows in this matrix
         * 
         * @return size_t The number of rows in this matrix
         */
        size_t rows() const
        {
            return _data.size();
        }

        /**
         * @brief Gets the number of columns in this matrix
         * 
         * @return size_t The number of columns in this matrix
         */
        size_t cols() const
        {
            return _data.size() > 0 ? _data.at(0).size() : 0;
        }

        /**
         * @brief Computes the transpose of this matrix and caches it
         * 
         * @return matrix<T> The transpose of this matrix
         */
        matrix<T> transpose()
        {
            if (_cache.size() > 0)
            {
                // transpose already computed so return
                // previous result
                return _cache.front();
            }

            if (_data.size() > 0)
            {
                // compute the transpose
                matrix<T> m_T(cols(), rows());
                for (size_t i = 0; i < _data.at(0).size(); i++)
                {
                    for (size_t j = 0; j < _data.size(); j++)
                    {
                        m_T[i][j] = _data[j][i];
                    }
                }
                _cache.push_front(m_T);
                return _cache.front();
            }

            // this matrix is of size 0 so just return
            return *this;
        }

        /**
         * @brief Computes the product of two matrices
         * 
         * @param m1 The first matrix
         * @param m2 The second matrix
         * @return matrix<T> The computed matrix product
         */
        static matrix<T> multiply(matrix<T> &m1, matrix<T> &m2)
        {
            if (m1.rows() == 0 || m2.rows() == 0)
            {
                throw std::out_of_range("Can't multiply matrix of size 0!");
            }

            matrix<T> result(m1.rows(), m2.cols());
            for (size_t i = 0; i < m1.rows(); i++)
            {
                for (size_t j = 0; j < m2.cols(); j++)
                {
                    result[i][j] = dot(m1[i], m2.transpose()[j]);
                }
            }
            return result;
        }

        /**
         * @brief Compute the product of this matrix with another
         * 
         * @param other The other matrix to multiply agains
         * @return matrix<T> The computed matrix product
         */
        matrix<T> multiply(matrix<T> &other)
        {
            return multiply(*this, other);
        }

        /**
         * @brief Print the contents of this matrix to the specified ostream.
         * The items in this matrix must support the stream extraction operation (operator<<).
         * @param out the ostream to print this matrix to
         */
        void print(std::ostream &out = std::cout) const
        {
            for (auto row : _data)
            {
                for (auto item : row)
                {
                    out << item << " ";
                }
                out << std::endl;
            }
        }

        /**
         * @brief Compute the product of this matrix with another
         * 
         * @param other The other matrix to multiply agains
         * @return matrix<T> The computed matrix product
         */
        matrix<T> operator* (matrix<T> &other)
        {
            return multiply(*this, other);
        }

        /**
         * @brief Returns the row vector at the requested index
         * 
         * @param i The index of the requested row in this matrix
         * @return const std::vector<T>& The requested row in this matrix
         */
        const std::vector<T> &operator[](size_t i) const
        {
            return _data.at(i);
        }

        /**
         * @brief Modifies the row vector at the requested index
         * 
         * @param i The index of the requested row in this matrix
         * @return std::vector<T>& The requested row in this matrix
         */
        std::vector<T> &operator[](size_t i)
        {
            _cache.clear();      // matix has changed so cached transpose is invalid
            return _data[i];
        }

        /**
         * @brief Calculates whether this matrix is not equal to another
         * 
         * @param rhs The other matrix to compare this to
         * @return true If the other matrix is not equal to this one
         * @return false If the other matrix is equal to this one
         */
        bool operator!= (const matrix<T> &rhs)
        {
            if (rows() != rhs.rows() || cols() != rhs.cols())
            {
                return true;
            }

            for (size_t i = 0; i < rows(); i++)
            {
                for (size_t j = 0; j < cols(); j++)
                {
                    if (_data [i][j] != rhs[i][j])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        /**
         * @brief Calculates whether this matrix is equal to another
         * 
         * @param rhs The other matrix to compare this to
         * @return true If the other matrix is equal to this one
         * @return false If the other matrix is not equal to this one
         */
        bool operator== (const matrix<T> &rhs)
        {
            return !(*this != rhs);
        }
    };

    /**
     * @brief Matrix stream extraction operator
     * 
     * @tparam T The type of data in the matrix. Must support stream extraction
     * @param os The ostream to print the matrix onto
     * @param m The patrix to print
     * @return std::ostream& The modified ostream
     */
    template <class T>
    std::ostream &operator<<(std::ostream &os, const matrix<T> &m)
    {
        m.print(os);
        return os;
    }
}

#endif
