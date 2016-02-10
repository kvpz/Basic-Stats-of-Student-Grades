
/*
  Kevin Perez
  2/8/16
  GradesDriver.cpp
  
  This program calculates: max, min, median, Q1, Q2, mean, mode, and 
  standard deviation of the provided values.
  
  runs perfectly on cygwin64 using g++ -std=c++11 -Wall -Wextra GradesDriver.cpp

*/
#include <iostream>
#include <fstream>
#include <math.h> /* pow() */

double max(const double*, const double*);  // out of both exams
double testMax(const double* test); // only one exam 
double min(const double *test);
double median(const double *test);
double Q1(const double *test);
double Q3(const double *test);
double mean(const double *test);
void mode(const double *test);
double stdev(const double *test);
void sort(double * test);


const int amountOfGrades = 1000;

int main(int argc, char * argv[])
{
  std::ifstream infile;
  std::istream * instream = &std::cin;
  double midterm[amountOfGrades];
  double final[amountOfGrades];
  double id[amountOfGrades];
  
  if(argc > 1)
  {
    infile.open(argv[1]);
    if(infile.fail()) return 0;
    instream = &infile;
  
  double temp = 0;
  int itr = 1;
  int index = 0;
  while(*instream >> temp)
  {
    unsigned int remainder = itr % 3;
    if(index == 0)
    {
      switch(remainder)
	{
      case 0:  final[index] = temp;
	++index;
	break;
      case 1:  midterm[index] = temp;
        break;
      case 2:  id[index] = temp;
        break;
	}
    }
    else
    {
	switch(remainder)
	{
	  case 0: final[index] = temp;
	    ++index;
	    break;
	case 1: id[index] = temp;
	  break;
	case 2: midterm[index] = temp;
	  break;
	} // switch
    } // if-else
    ++itr;
  } // while
  } //  if

  infile.close();
  //sorting is necessary for everything but max() and min()
  sort(midterm);
  sort(final);
  // Basic stats on Midterm grades
  std::cout << "Midterm Stats:" << std::endl;
  std::cout << "Max: " << testMax(midterm) << std::endl;
  std::cout << "Min: " << min(midterm) << std::endl;
  std::cout << "Median: " << median(midterm) << std::endl;
  std::cout << "Q1: " << Q1(midterm) << std::endl;
  std::cout << "Q3: " << Q3(midterm) << std::endl;
  std::cout << "Mean: " << mean(midterm) << std::endl;
  std::cout << "Mode: "; mode(midterm); std::cout << std::endl;
  std::cout << "Standard Deviation: " << stdev(midterm) << std::endl;

  // Basic Stats on Final grades
  std::cout << "\n\nFinal stats: " << std::endl;
  std::cout << "Max: " << testMax(final) << std::endl;
  std::cout << "Min: " << min(final) << std::endl;
  std::cout << "Median: " << median(final) << std::endl;
  std::cout << "Q1: " << Q1(final) << std::endl;
  std::cout << "Q3: " << Q3(final) << std::endl;
  std::cout << "Mean: " << mean(final) << std::endl;
  std::cout << "Mode: "; mode(final); std::cout << std::endl;
  std::cout << "Standard Deviation: " << stdev(final) << std::endl;
  
  return 0;
}

/* Definitions */


// Highest grade out of both midterm and final
double max(const double *mid, const double *fin)
{
  double max = 0;
  double diff = 0;
  
  for(int i = 0; i < amountOfGrades; ++i)
  { 
    diff = mid[i] - fin[i];
    if(!diff && max < mid[i])  max = mid[i];
    if(diff && max < mid[i])   max = mid[i];
    if(diff && max < fin[i])   max = fin[i];
  } // for
  return max;
}

double testMax(const double* test)
{
  double max = 0;
  double diff = 0;  // false when 0, true otherwise (in conditional statements
  for(int i = 0; i < amountOfGrades; ++i)
  { 
    diff = max - test[i];
    if(diff && max < test[i])
    {
      max = test[i];
    }
  } // for
  return max;
}

double min(const double *test)
{
  double min = 100;
  for(int i = 0; i < amountOfGrades; ++i)
  {
    if(min > test[i])  min = test[i];
  }
  return min;
}


double median(const double *test)
{
  int middleElement = amountOfGrades/2;
  if(amountOfGrades % 2) // if 2 middle elements (i.e. even amountOfGrades)
  {
    return (test[middleElement] + test[middleElement + 1])/2;
  }
  else
  {
    return test[middleElement];
  }
}

/*
  Returns the first Quantile
 */
double Q1(const double *test)
{
  int middleElement = amountOfGrades/2;
  if(amountOfGrades % 2)
  {
    middleElement = middleElement/2;
    return test[middleElement];
  }
  else
  {
    middleElement = middleElement/2;
    return (test[middleElement] + test[middleElement+1])/2;
  }
}

/*
  Returns the third quantile
 */
double Q3(const double *test)
{
  int middleElement = amountOfGrades/2;
  if(amountOfGrades % 2)
  {
    middleElement = middleElement + middleElement/2;
    return test[middleElement];
  }
  else
  {
    middleElement = middleElement + middleElement/2;
    return (test[middleElement] + test[middleElement+1])/2;
  }
}

/*
  Returns the mean (average) after computation
 */
double mean(const double* test)
{
  double sumOfGrades = 0;
  for(int i = 0; i < amountOfGrades; ++i)
    sumOfGrades += test[i];
  return sumOfGrades/amountOfGrades;
}

/*
  This function will output the mode of the given test scores.
  Remember, a mode can be a set of more than one number, each 
  occuring the same amount of times, which is a higher frequency
  than any of the other grades.
 */
void mode(const double* test)
{
  unsigned int amountOfModes = 20;
  double * currentMode = new double[amountOfModes]; // 1 or more mode allowed
  double previous = test[0];
 
  int occurances = 1;  // element determining occurances of potential mode
  int maxOccurance = 1;
  int j = 0;  // used for currentMode
  for(int i = 1; i < amountOfGrades; ++i)
  {
    if(previous != test[i]) // current grade is not previous
    {
      if(occurances > maxOccurance)
      {
	delete [] currentMode;
	currentMode = new double[amountOfModes];
	j = 0;
	maxOccurance = occurances;
	currentMode[j] = test[i-1];
	++j;
      }
      else if(occurances == maxOccurance)
      {
	currentMode[j] = test[i-1];
	++j;
      } // else-if
      occurances = 0; 
    } // outer if
    
    ++occurances; // couning occurances of current grade test[i]
    previous = test[i];
  } // for
   
  // printing the mode for the test grades
  for(int i = 0; currentMode[i]; ++i)
    std::cout << currentMode[i] << ' ';
}

/*
  Standard Deviation: sqrt(E[X^2]-(EX)^2) where EX is the mean
 */
double stdev(const double* test)
{
  double mean_ = mean(test);
  double sum = 0;
  for(int i = 0; i < amountOfGrades; ++i)
  {
    sum += pow(test[i]-mean_,2);
  }
  sum = sum/amountOfGrades;
  return sqrt(sum);
}

/*
  This sorts (using bubble sort) the grades of the test passed to 
  the function. Note reference argument. 
 */
void sort(double *test)
{
  double temp = 0;
  int newn = 0;
  int n = amountOfGrades;

  while(newn < amountOfGrades)
  {
    for(int i = 1; i < n; ++i)
    {
      if(test[i-1] > test[i])
      {
	temp = test[i-1];
	test[i-1] = test[i];
	test[i] = temp;
      } // if
    }// outer for
    ++newn;
  } // while
}
