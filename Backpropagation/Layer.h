#pragma once
#include "Neuron.h"

class Layer
{
public:
	Layer(){}
	~Layer(){}

	void printLayer() const{}

	std::vector<Neuron>& getListOfNeurons() { return listOfNeurons; }
	void setListOfNeurons(const std::vector<Neuron>& listOfNeurons) 
	{ 
		this->listOfNeurons = listOfNeurons; 
	}

	size_t getNumberOfNeuronsInLayer() const{ return numberOfNeuronInLayer; }
	void setNumberOfNeuronsInLayer(int numberOfNeuronInLayer) { this->numberOfNeuronInLayer = numberOfNeuronInLayer; }

protected:
	std::vector<Neuron> listOfNeurons;
	size_t numberOfNeuronInLayer;
};
