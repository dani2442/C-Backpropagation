#pragma once


class Training
{
public:
	Training();
	~Training();

	NeuralNet& train(NeuralNet&);
	void printTrainedNetResult(NeuralNet& trainedNet);

	

private:

	std::vector<Neuron> teachNeuronsOfLayer(size_t, size_t, NeuralNet&, double);
	double calcNewWeight(TrainingTypesENUM, double , NeuralNet, double, double, double);

	double fncStep(double n) { return (n >= 0) ? 1.0 : 0.0; }
	double fncLinear(double n) { return n; }
	double fncSigLog(double n) { return 1.0 / (1.0 + exp(-n)); }
	double fncHyperTan(double n) { return tanh(n); }

	double derivateFncLinear(double n) { return 1.0; }
	double derivateFncSigLog(double n) { return n * (1.0 - n); }
	double derivativeFncHyperTan(double n) { return 1.0 / pow(cosh(n), 2); }

	int epochs=0;
	double error=0;
	double mse=0;

protected:
	typedef double(Training::*fptr)(double);
	fptr activationFnc[4] = { &Training::fncLinear,&Training::fncSigLog,&Training::fncHyperTan, &Training::fncStep };
	fptr derivateActivationFnc[3] = { &Training::derivateFncLinear,&Training::derivateFncSigLog,&Training::derivativeFncHyperTan };

public:
	// Getters and Setters
	 int getEpochs() { return epochs; }
	void setEpochs(int epochs) { this->epochs = epochs; }

	 double getError() { return error; }
	void setError(double error) { this->error = error; }

	 double getMse()  { return mse; }
	void setMse(double mse) { this->mse = mse; }
};

Training::Training()
{
}

Training::~Training()
{
}

inline NeuralNet & Training::train(NeuralNet& n)
{
	std::vector<double>inputWeightIn;
	
	size_t rows = n.getTrainSet().size();
	size_t cols = n.getTrainSet()[0].size();
	while (this->getEpochs() < n.getMaxEpochs()) {
		double estimatedOutput = 0.0;
		double realOutput = 0.0;

		for (size_t i = 0; i < rows; i++) {
			double netValue = 0.0;

			for (size_t j = 0; j < cols; j++) {
				inputWeightIn = n.getInputLayer().getListOfNeurons()[j].getListOfWeightIn();
				double inputWeight = inputWeightIn[0];
				netValue = netValue + inputWeight * n.getTrainSet()[i][j];
			}
			estimatedOutput =(this->*activationFnc[n.getActivationFnc()])(netValue);
			realOutput = n.getRealOutputSet()[i];
			this->setError(realOutput - estimatedOutput);

			if (abs(this->getError()) > n.getTargetError()) {
				InputLayer inputLayer;
				inputLayer.setListOfNeurons(this->teachNeuronsOfLayer(cols, i, n, netValue));
				n.setInputLayer(inputLayer);
			}
		}
		this->setMse(pow(realOutput - estimatedOutput, 2));
		n.getListOfMSE().push_back(this->getMse());

		this->setEpochs(this->getEpochs() + 1);
	}
	n.setTrainingError(this->getError());
	return n;
}

inline void Training::printTrainedNetResult(NeuralNet & trainedNet)
{
	size_t rows = sizeof(trainedNet.getTrainSet())/sizeof(trainedNet.getTrainSet()[0]);
	size_t cols = sizeof(trainedNet.getTrainSet()[0]) / sizeof(double);

	std::vector<double> inputWeightIn;
	for (size_t i = 0; i < rows; i++) {
		double netValue = 0.0;
		for (size_t j = 0; j < cols; j++) {
			inputWeightIn = trainedNet.getInputLayer().getListOfNeurons()[j].getListOfWeightIn();
			double inputWeight = inputWeightIn[0];
			netValue = netValue + inputWeight * trainedNet.getTrainSet()[i][j];

			std::cout << trainedNet.getTrainSet()[i][j] << "\t";
		}
		double estimatedOutput = (this->*activationFnc[trainedNet.getActivationFnc()])(netValue);

		std::cout << " NET OUTPUT: " << estimatedOutput << "\t";
		std::cout << " REAL IUTPUT: " << trainedNet.getRealOutputSet()[i] << "\t";
		double error = estimatedOutput - trainedNet.getRealOutputSet()[i];
		std::cout << " ERROR: " << error << std::endl;
	}
}

inline std::vector<Neuron> Training::teachNeuronsOfLayer(size_t numberOfInputNeurons, size_t line, NeuralNet &n, double netValue)
{
	std::vector<Neuron> listOfNeurons;
	std::vector<double> inputWeightsInNew;
	std::vector<double> inputWeightsInOld;

	for (size_t j = 0; j < numberOfInputNeurons; j++) {
		inputWeightsInOld = n.getInputLayer().getListOfNeurons()[j].getListOfWeightIn();
		double inputWeightOld = inputWeightsInOld[0];

		inputWeightsInNew.push_back(this->calcNewWeight(n.getTrainType(), inputWeightOld, n, this->getError(), n.getTrainSet()[line][j], netValue));

		Neuron neuron;
		neuron.setListOfWeightIn(inputWeightsInNew);
		listOfNeurons.push_back(neuron);
		inputWeightsInNew.clear();
	}
	return listOfNeurons;
}

inline double Training::calcNewWeight(TrainingTypesENUM trainType, double inputWeightOld, NeuralNet n, double error, double trainSample, double netValue)
{
	switch (trainType) {
	case TrainingTypesENUM::PERCEPTRON:
		return inputWeightOld + n.getLearningRate() * error * trainSample;
	case TrainingTypesENUM::ADALINE:
		return inputWeightOld + n.getLearningRate() * error * trainSample * (this->*derivateActivationFnc[n.getActivationFnc()])(netValue);
	default:
		std::cout << "Error - Training::calcNewWeight";
		return NULL;
	}
	
}




