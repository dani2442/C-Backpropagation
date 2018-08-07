#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>


class Neuron
{
public:
	Neuron();
	~Neuron();

	double initNeuron() { return ((double)rand() / (RAND_MAX)); }

	 std::vector<double>& getListOfWeightIn() { return listOfWeightIn; } // ListOfWeightIn
	void setListOfWeightIn(const std::vector<double>& listOfWeightIn) { this->listOfWeightIn = listOfWeightIn; }
	
	 std::vector<double>& getListOfWeightOut() { return listOfWeightOut; } // ListOfWeightOut
	void setListOfWeightOut(const std::vector<double>& listOfWeightOut) { this->listOfWeightOut = listOfWeightOut; }

	 double getOutputValue() { return outputValue; } // OutputValue
	void setOutputValue(const double outputValue) { this->outputValue = outputValue; }

	 double getError() { return error; } // Error
	void setError(const double error) { this->error = error; }

	 double getSensibility() { return sensibility; }// Sensibility
	void setSensibility(const double sensibility) { this->sensibility = sensibility; }


private:
	std::vector<double> listOfWeightIn;
	std::vector<double> listOfWeightOut;
	double outputValue;
	double error;
	double sensibility;
};

inline Neuron::Neuron()
{
}

inline Neuron::~Neuron()
{
}
