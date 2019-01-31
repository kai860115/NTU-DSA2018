#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int &r, const int &c) //constructor
{
   row = r;
   col = c;
   array = new double *[r];
   for (size_t i = 0; i != r; i++)
   {
      array[i] = new double[c];
   }
}

Matrix::Matrix(const Matrix &rhs) //copy constructor
{
   row = rhs.row;
   col = rhs.col;
   array = new double *[row];
   for (size_t i = 0; i != row; i++)
   {
      array[i] = new double[col];
   }
   for (size_t i = 0; i != row; i++)
   {
      for (size_t j = 0; j != col; j++)
      {
         array[i][j] = rhs.array[i][j];
      }
   }
}

Matrix::~Matrix() //destructor
{
   for (size_t i = 0; i != row; i++)
      delete[] array[i];
   delete[] array;
}

double *&Matrix::operator[](const int &idx) const
{
   return array[idx];
}

Matrix Matrix::operator=(const Matrix &rhs) // assignment constructor
{
   for (size_t i = 0; i != row; i++)
      delete[] array[i];
   delete[] array;
   row = rhs.row;
   col = rhs.col;
   array = new double *[row];
   for (size_t i = 0; i != row; i++)
   {
      array[i] = new double[col];
   }
   for (size_t i = 0; i != row; i++)
   {
      for (size_t j = 0; j != col; j++)
      {
         array[i][j] = rhs.array[i][j];
      }
   }
   return *this;
}

Matrix Matrix::operator-() const
{
   Matrix m(*this);
   for (size_t i = 0; i != row; i++)
   {
      for (size_t j = 0; j != col; j++)
      {
         m.array[i][j] *= -1;
      }
   }
   return m;
}

Matrix Matrix::operator+() const
{
   return Matrix(*this);
}

Matrix Matrix::operator-(const Matrix &rhs) const
{
   Matrix m(*this);
   if (col != rhs.col)
      printf("Error: col dofferent!");
   else if (row != rhs.row)
      printf("Error: row different!");
   else
   {
      for (size_t i = 0; i != row; i++)
      {
         for (size_t j = 0; j != col; j++)
         {
            m.array[i][j] -= rhs.array[i][j];
         }
      }
   }
   return m;
}

Matrix Matrix::operator+(const Matrix &rhs) const
{
   Matrix m(*this);
   if (col != rhs.col)
      printf("Error: col dofferent!");
   else if (row != rhs.row)
      printf("Error: row different!");
   else
   {
      for (size_t i = 0; i != row; i++)
      {
         for (size_t j = 0; j != col; j++)
         {
            m.array[i][j] += rhs.array[i][j];
         }
      }
   }
   return m;
}

Matrix Matrix::operator*(const Matrix &rhs) const
{
   if (col != rhs.row)
   {
      printf("Error: col of left matrix != row of right matrix!");
      return Matrix(*this);
   }

   else
   {
      Matrix m(row, rhs.col);
      for (size_t i = 0; i != row; i++)
      {
         for (size_t j = 0; j != rhs.col; j++)
         {
            m[i][j] = 0;
            for (size_t k = 0; k != col; k++)
               m[i][j] += array[i][k] * rhs[k][j];
         }
      }
      return m;
   }
}

Matrix Matrix::operator/(const Matrix &rhs) const
{
   return Matrix((*this) * (rhs.inverse()));
}

Matrix Matrix::inverse() const
{
   if (row == col)
   {
      Matrix ml(*this);
      Matrix mr(row, col);
      for (size_t i = 0; i != row; i++)
         for (size_t j = 0; j != col; j++)
            mr[i][j] = 0;
      for (size_t i = 0; i != row; i++)
         mr[i][i] = 1;

      for (size_t i = 0; i != row; i++)
      {
         if (ml[i][i] == 0)
         {
            for (size_t k = i; k != row; k++)
            {
               if (ml[k][i] != 0)
               {
                  for (size_t j = 0; j != row; j++)
                  {
                     double tmpl = ml[k][j];
                     double tmpr = mr[k][j];
                     ml[k][j] = ml[i][j];
                     mr[k][j] = mr[i][j];
                     ml[i][j] = tmpl;
                     mr[i][j] = tmpr;
                  }
                  break;
               }
            }
         }
         double t = ml[i][i];
         for (size_t j = 0; j != col; j++)
         {
            mr[i][j] /= t;
            ml[i][j] /= t;
         }
         for (size_t k = i + 1; k != row; k++)
         {
            if (ml[k][i] != 0)
            {
               t = ml[k][i] / ml[i][i];
               for (size_t j = 0; j != row; j++)
               {
                  ml[k][j] -= ml[i][j] * t;
                  mr[k][j] -= mr[i][j] * t;
               }
            }
         }
      }
      for (int i = row - 1; i >= 0; i--)
      {
         for (int j = i - 1; j >= 0; j--)
         {
            double t = ml[j][i] / ml[i][i];
            for (size_t k = 0; k != row; k++)
            {
               ml[j][k] -= t * ml[i][k];
               mr[j][k] -= t * mr[i][k];
            }
         }
      }
      return mr;
   }
   else
   {
      printf("Error: row != col");
      return Matrix(*this);
   }
}

void Matrix::read(const char *fn)
{
   int r, c;
   FILE *fp = fopen(fn, "r");
   if (fp == NULL)
   {
      printf("read file [%s] error\n", fn);
      exit(0);
   }
   fscanf(fp, "%d%d", &r, &c);
   Matrix tmp(r, c);
   for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
         fscanf(fp, "%lf", &tmp.array[i][j]);
   fclose(fp);
   *this = tmp;
}

void Matrix::write(const char *fn)
{
   FILE *fp = fopen(fn, "w");
   if (fp == NULL)
   {
      printf("write file [%s] error\n", fn);
      exit(0);
   }
   fprintf(fp, "%d %d\n", row, col);
   for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
         fprintf(fp, "%lf%c", array[i][j], " \n"[j == col - 1]);
   fclose(fp);
}

void Matrix::print() const
{
   for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
         printf("%lf%c", array[i][j], " \n"[j == col - 1]);
}
