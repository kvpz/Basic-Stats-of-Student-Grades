
/*
  Kevin Perez
  2/8/16
  
  This program calculates: max, min, median, Q1, Q2, mean, mode, and 
  standard deviation of the provided values.

*/
#include <iostream>
#include <fstream>
#include <set>
//#include <algorithm> // sort

double max(const double*, const double*);  // out of both exams
double testMax(const double* test); // only one exam 
double min(const double *test);
double median(const double *test);
double Q1(const double *test);
double Q3(const double *test);
double mean(const double *test);
double mode(const double *test);
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
  double maximum = testMax(midterm);
  double minimum = min(midterm);
  std::cout << "Max is: " << maximum << std::endl;
  std::cout << "Min is: " << minimum << std::endl;
  sort(midterm);
  sort(final);
  std::cout << "midterm median: " << median(midterm) << std::endl;
  std::cout << "final median: " << median(final) << std::endl;
  std::cout << "Q1 for midterm: " << Q1(midterm) << std::endl;
  std::cout << "Q3 for midterm: " << Q3(midterm) << std::endl;
  std::cout << "Mean for midterm: " << mean(midterm) << std::endl;
  mode(midterm);
  return 0;
}

/* Definitions */
// Note: they have not been optimized (i.e. better ways to write these)

// Highest grade out of both midterm and final
double max(const double *mid, const double *fin)
{
  double max = 0;
  double diff = 0;
  
  for(int i = 0; i < 1000; ++i)
    { // cond: max < 100 would improve computation
    diff = mid[i] - fin[i];
    if(!diff && max < mid[i])
      max = mid[i];
    if(diff && max < mid[i])
      max = mid[i];
    if(diff && max < fin[i])
      max = fin[i];
  }
  return max;
}

double testMax(const double* test)
{
  double max = 0;
  double diff = 0;  // false when 0, true otherwise (in conditional statements
  for(int i = 0; i < 1000; ++i)
    { // cond: max < 100 would improve computation
      diff = max - test[i];
      if(diff && max < test[i])
	{
	  max = test[i];
	}
    }
  return max;
  
}

double min(const double *test)
{
  double min = 100;
  for(int i = 0; i < amountOfGrades; ++i)
  {
    if(min > test[i])
      min = test[i];
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

double mean(const double* test)
{
  double sumOfGrades = 0;
  for(int i = 0; i < amountOfGrades; ++i)
    sumOfGrades += test[i];
  return sumOfGrades/amountOfGrades;
}


double mode(const double* test)
{
  int amountOfModes = 10;
  double * currentMode = new double[amountOfModes];
  double * freq = new double[amountOfModes];
  double previous = 0;
  //int grade = 0;  // value of element of potential mode 
  int occurances = 0;  // element determining occurances of potential mode
  int occurances_prev = 0;
  int maxOccurances = 0;
  int j = 0;  // used for currentMode
  for(int i = 0; i < amountOfGrades; ++i)
  {
    if(previous != test[i] && occurances >= maxOccurances) // current grade is not previous
    {
      maxOccurances = occurances;
      currentMode[j] = test[i];
      ++j;
      std::cout << test[i-1]
    }
      occurances = 0;
  } // for
    ++occurances;

    std::cout << "The mode is: ";
    for(int i = 0; i < amountOfModes; ++i)
      std::cout << currentMode[i] << ' ';
    
}


double stdev(const double* test)
{

}


void sort(double *test)
{
  double temp = 0;
  int k = 0;
  bool swapped = false;
  int newn = 0;
  int n = amountOfGrades;

while(newn < 1000)
{
  for(int i = 1; i < n; ++i)
  {
    if(test[i-1] > test[i])
    {
      temp = test[i-1];
      test[i-1] = test[i];
      test[i] = temp;
      swapped = true;
    } // if
  }// outer for
  ++newn;
} // while
  
}
