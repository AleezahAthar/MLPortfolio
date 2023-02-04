#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std; 

//function to find the sum of the numbers in a vector 
double findSum(vector<double> a){
    double sum=0.0; //create and initialize a vector to hold the sum
    //for loop to iterate through the vector and add each one to sum
    for(int i=0; i<a.size() ;i++){
        sum+=a[i];
    }
    //return sum
    return sum;
}

//function to find the mean of the numbers in a vector 
double findMean(vector<double> a){
    //create a variable called mean 
    //use to the findSum function and divide by the size of the vector to get the mean
    double mean=findSum(a)/a.size();
    //return the mean
    return mean;
}

//function to find the median of a vector
double findMedian(vector<double> a){
    //create a variable to hold the median and size of the vector
    double median; 
    int sizeOfVector=a.size();
    //sort the vector from beginning to end
    sort(a.begin(), a.end());
    //check if the vector is even or odd
    if(sizeOfVector%2==0){
        //if the vector is even the median is the average of the middle two elements 
        median=(a[sizeOfVector/2]+a[(sizeOfVector/2)-1])/2.0;

    }else{
        //if the vector is odd the median is the element at the middle. 
        median=a[sizeOfVector/2];
    }
    //return the median found
    return median; 
}

//function to find the range of a vector 
double findRange(vector<double> a){
    //create variables to hold the range, minimum and maximum. 
    double range, min, max; 
    //set the min and max to be the first element in the array
    min=max=a[0]; 
    //create a for loop to iterate through the vector and find the min and max
    for(int i=0; i<a.size(); i++){
        if(a[i]<min) min=a[i]; 
        else if(a[i]>max) max=a[i];
    }
    range=max-min; //calculate the range
    return range; //return the range 
}
//function that calls the findSum, findMean, findMedian, findRange functions and displays the results 
void print_stats(vector<double> a){
    cout<<"The sum of the numeric vector is "; 
    cout<<findSum(a);
    cout<<"\nThe mean of the numeric vector is "; 
    cout<<findMean(a);
    cout<<"\nThe median of the numeric vector is "; 
    cout<<findMedian(a);
    cout<<"\nThe range of the numeric vector is "; 
    cout<<findRange(a);
}
//function to calculate the covariance between two vectors. 
double covar(vector<double> a, vector<double> b){
    //create double variables to hold the covariance, numerator and denominator
    double covariance, numerator=0.0, denominator; 
    //create variables and call the findMean to get the mean of vectors a and b 
    double meanOfA=findMean(a);
    double meanOfB=findMean(b);
    //for loop to iterate through the vector, find the difference between each vector and mean and add them 
    for(int i=0; i<a.size(); i++){
        numerator+=(a[i]-meanOfA)*(b[i]-meanOfB);
    }
    //the denominator will be n-1
    denominator=a.size()-1;
    covariance=numerator/denominator; //calculate the covariance
    return covariance; //return the covariance 
}
//function to calculate the correlation between two vectors. 
double cor(vector<double> a, vector<double> b){
    //create variable called cov which calls the covariance function
    double cov=covar(a,b);
    //create variables and call the findMean to get the mean of vectors a and b 
    double meanOfA=findMean(a);
    double meanOfB=findMean(b);
    //initialize variance numerators to be 0
    double varianceOfA_Numerator=0.0;
    double varianceOfB_Numerator=0.0;
    //for loop to find the difference between each value and the mean and add them
    for(int i=0; i<a.size();i++){
        varianceOfA_Numerator+=((a[i]-meanOfA)*(a[i]-meanOfA));
        varianceOfB_Numerator+=((b[i]-meanOfB)*(b[i]-meanOfB));
    }
    //calculate sigma
    double sigmaOfA=sqrt(varianceOfA_Numerator/(a.size()-1));
    double sigmaOfB=sqrt(varianceOfB_Numerator/(b.size()-1));
    //calculate correlation
    double cor=cov/(sigmaOfA*sigmaOfB);
    return cor;//return correlation

    
}
//main function
int main(int argc, char** argv){
    ifstream inFS; //input file stream
    string line;
    string rm_in, medv_in; 
    const int MAX_LEN=1000; 
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN); 

    //Try to open file 
    cout<<"Opening file Boston.csv"<<endl;

    inFS.open("Boston.csv"); 
    if(!inFS.is_open()){
        cout<<"Couldn't open file Boston.csv"<<endl; 
        return 1; //1 indicated error
    }

    //Can now use inFS stream line cin stream
    //Boston.csv should contain two doubles 

    cout << "Reading line 1" << endl;
    getline(inFS, line); 

    //echo heading 
    cout<<"heading: " << line << endl;

    int numObservations=0; 
    while(inFS.good()){
        getline(inFS, rm_in, ','); 
        getline(inFS, medv_in, '\n'); 

        rm.at(numObservations)= stof(rm_in);
        medv.at(numObservations)= stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout<<"New length is "<<rm.size()<<endl;
    cout<<"Closing file Boston.csv"<<endl; 
    inFS.close(); 
    cout<<"Number of records: "<<numObservations<<endl; 
    cout<<"Stats for rm"<<endl; 
    print_stats(rm); 
    cout<<"\nStats for medv"<<endl; 
    print_stats(medv);
    cout<<"\nCovariance = "<<covar(rm,medv)<<endl;
    cout<<"Correlation = "<<cor(rm,medv)<<endl;
    cout<<"Program terminated."; 
    return 0;    
}

