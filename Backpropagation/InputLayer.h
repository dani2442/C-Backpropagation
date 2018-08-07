#pragma once
#include "Layer.h"


class InputLayer : public Layer
{
public:
	InputLayer() ;
	~InputLayer() ;

	InputLayer& initLayer(InputLayer& inputLayer);
	void printLayer( InputLayer& inputLayer) ;

	void setNumberOfNeuronsInLayer(int numberOfNeuronInLayer) { this->numberOfNeuronInLayer = numberOfNeuronInLayer+1; }
private:

};

InputLayer::InputLayer() :  Layer()
{
}

InputLayer::~InputLayer()
{
}

inline InputLayer& InputLayer::initLayer(InputLayer& inputLayer)
{
	std::vector<double> listOfWeightInTemp;
	std::vector<Neuron>listOfNeurons;

	for (size_t i = 0; i < inputLayer.getNumberOfNeuronsInLayer(); i++) {
		Neuron neuron;
		listOfWeightInTemp.push_back(neuron.initNeuron());

		neuron.setListOfWeightIn(listOfWeightInTemp);
		listOfNeurons.push_back(neuron);

		listOfWeightInTemp.clear();
	}
	inputLayer.setListOfNeurons(listOfNeurons);
	return inputLayer;
}

inline void InputLayer::printLayer(InputLayer & inputLayer) 
{
	std::cout << "### INPUT LAYER ###"<<std::endl;
	int n = 1;
	for (Neuron neuron : inputLayer.getListOfNeurons()) {
		std::cout << "Neuron #" << n << ":"<<std::endl;
		std::cout << "Input Weights:"<<std::endl;
		std::vector<double> weights = neuron.getListOfWeightIn();
		for (double weight : weights) {
			std::cout << weight << std::endl;
		}
		n++;
	}
}
