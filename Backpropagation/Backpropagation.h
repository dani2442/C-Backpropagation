#pragma once

class Backpropagation:public Training
{
public:
	Backpropagation();
	~Backpropagation();

	NeuralNet& train(NeuralNet& n);

protected:
	NeuralNet& forward(NeuralNet& n, size_t row);
	NeuralNet& backpropagation(NeuralNet& n, size_t row);
private:
};

Backpropagation::Backpropagation(): Training()
{
}

Backpropagation::~Backpropagation()
{
}

inline NeuralNet & Backpropagation::train(NeuralNet & n)
{
	int epoch = 0;
	setMse(1.0);
	while (getMse() > n.getTargetError()) {
		if (epoch >= n.getMaxEpochs())break;
		size_t rows = n.getTrainSet().size();
		double sumErrors = 0.0;

		for (size_t rows_i = 0; rows_i < rows; rows_i++) {
			n = forward(n, rows_i);
			n = backpropagation(n, rows_i);
			sumErrors = sumErrors + n.getErrorMean();
		}
		setMse(sumErrors / rows);
		std::cout << getMse()<<std::endl;
		epoch++;
	}
	std::cout << "Number of epochs: " << epoch << std::endl;
	return n;
}

inline NeuralNet & Backpropagation::forward(NeuralNet & n, size_t row)
{
	std::vector<HiddenLayer> listOfHiddenLayer = n.getListOfHiddenLayer();
	double estimatedOutput = 0.0;
	double realOutput = 0.0;
	double sumError = 0.0;

	if (listOfHiddenLayer.size() >0 ) {
		int hiddenLayer_i = 0;
		for(std::vector<HiddenLayer>::iterator hiddenLayer=listOfHiddenLayer.begin();hiddenLayer!=listOfHiddenLayer.end();hiddenLayer++){
			size_t numberOfNeuronsInLayer = hiddenLayer->getNumberOfNeuronsInLayer();
			for(std::vector<Neuron>::iterator neuron=hiddenLayer->getListOfNeurons().begin();neuron!=hiddenLayer->getListOfNeurons().end();neuron++){
				double netValueOut = 0.0;
				if (neuron->getListOfWeightIn().size() > 0) {
					double netValue = 0.0;
					for (size_t layer_j = 0; layer_j < numberOfNeuronsInLayer - 1; layer_j++) {
						double hiddenWeightIn = neuron->getListOfWeightIn()[layer_j];
						netValue = netValue + hiddenWeightIn * n.getTrainSet()[row][layer_j];
					}
					// Output hidden layer (1)
					netValueOut = (this->*activationFnc[n.getActivationFnc()])(netValue);
					neuron->setOutputValue(netValueOut);
				}
				else {
					neuron->setOutputValue(1.0);
				}
			}
			n.setHiddenLayer(*hiddenLayer);//////// Important to know whether hiddenLayer is a copy of the last element of listOfHiddenLayer
			// Output hidden layer (2)
			for (size_t outLayer_i = 0; outLayer_i < n.getOutputLayer().getNumberOfNeuronsInLayer(); outLayer_i++) {
				double netValue = 0.0;
				double netValueOut = 0.0;
				for (Neuron neuron : hiddenLayer->getListOfNeurons()) {
					double hiddenWeightOut = neuron.getListOfWeightOut()[outLayer_i];
					netValue = netValue + hiddenWeightOut * neuron.getOutputValue();
				}
				netValueOut = (this->*activationFnc[n.getActivationFncOutputLayer()])(netValue);
				n.getOutputLayer().getListOfNeurons()[outLayer_i].setOutputValue(netValueOut);

				// Error
				estimatedOutput = netValueOut;
				realOutput = n.getRealMatrixOutputSet()[row][outLayer_i];
				double error = realOutput - estimatedOutput;
				n.getOutputLayer().getListOfNeurons()[outLayer_i].setError(error);
				sumError += pow(error, 2);
			}
			// Error mean
			double errorMean = sumError / n.getOutputLayer().getNumberOfNeuronsInLayer();
			n.setErrorMean(errorMean);
			n.getListOfHiddenLayer()[hiddenLayer_i].setListOfNeurons(hiddenLayer->getListOfNeurons());
			hiddenLayer_i++;
		}
	}
	return n;
}

inline NeuralNet & Backpropagation::backpropagation(NeuralNet & n, size_t row)
{
	std::vector<Neuron>& outputLayer = n.getOutputLayer().getListOfNeurons();
	std::vector<Neuron>& hiddenLayer = n.getListOfHiddenLayer()[0].getListOfNeurons();

	double error = 0.0;
	double netValue = 0.0;
	double sensibility = 0.0;
	// Sensibility output layer
	for(std::vector<Neuron>::iterator it=outputLayer.begin();it!=outputLayer.end();it++){
		error = it->getError();
		netValue = it->getOutputValue();
		sensibility = error*(this->*derivateActivationFnc[n.getActivationFncOutputLayer()])(netValue);
		it->setSensibility(sensibility);
	}
	n.getOutputLayer().setListOfNeurons(outputLayer);
	// Sensibility hidden layer
	for (std::vector<Neuron>::iterator it = hiddenLayer.begin(); it != hiddenLayer.end(); it++) {
		sensibility = 0.0;
		if (it->getListOfWeightIn().size() > 0) {
			std::vector<double>listOfWeightOut = it->getListOfWeightOut();
			double tempSensiblity = 0.0;
			for (size_t i = 0; i < listOfWeightOut.size(); i++)
				tempSensiblity += listOfWeightOut[i] * outputLayer[i].getSensibility();
			sensibility = (this->*derivateActivationFnc[n.getActivationFnc()])(it->getOutputValue())*tempSensiblity;
			it->setSensibility(sensibility);
		}
	}
	n.getListOfHiddenLayer()[0].setListOfNeurons(hiddenLayer);///////////////

	// Fix weights (teach) [output layer to hidden layer]
	for (size_t outLayer_i = 0; outLayer_i < n.getOutputLayer().getNumberOfNeuronsInLayer(); outLayer_i++) {
		for (std::vector<Neuron>::iterator it = hiddenLayer.begin(); it != hiddenLayer.end(); it++) {
			double newWeight = it->getListOfWeightOut()[outLayer_i] + (n.getLearningRate()*outputLayer[outLayer_i].getSensibility()*it->getOutputValue());
			it->getListOfWeightOut()[outLayer_i] = newWeight;
		}
	}
	n.getOutputLayer().setListOfNeurons(outputLayer);////////////////
	// Fix weights (teach) [output layer to input layer]
	for (std::vector<Neuron>::iterator it = hiddenLayer.begin(); it != hiddenLayer.end(); it++) {
		std::vector<double> hiddenLayerInputWeights = it->getListOfWeightIn();
		if (hiddenLayerInputWeights.size() > 0) {
			double newWeight = 0.0;
			for (size_t i = 0; i < n.getInputLayer().getNumberOfNeuronsInLayer(); i++) {
				newWeight = hiddenLayerInputWeights[i] + (n.getLearningRate()*it->getSensibility()*n.getTrainSet()[row][i]);
				it->getListOfWeightIn()[i] = newWeight;
			}
		}
	}
	n.getListOfHiddenLayer()[0].setListOfNeurons(hiddenLayer);
	return n;
}
