#pragma once

class NeuralNetTest
{
public:
	NeuralNetTest();
	~NeuralNetTest();

	void testBackpropagation();

private:

};

NeuralNetTest::NeuralNetTest()
{
}

NeuralNetTest::~NeuralNetTest()
{
}



inline void NeuralNetTest::testBackpropagation()
{
	NeuralNet testNet;
	testNet.initNet(2, 1, 3, 2);
	std::cout << "-------------BACKPROPAGATION INET NET----------------" << std::endl;
	testNet.printNet(testNet);
	NeuralNet trainedNet;
	testNet.setTrainSet(std::vector<std::vector<double>>() = {
		{ 1.0, 1.0, 0.73 },{ 1.0, 1.0, 0.81 },{ 1.0, 1.0, 0.86 },
		{ 1.0, 1.0, 0.95 },{ 1.0, 0.0, 0.45 },{ 1.0, 1.0, 0.70 },
		{ 1.0, 0.0, 0.51 },{ 1.0, 1.0, 0.89 },{ 1.0, 1.0, 0.79 },{ 1.0, 0.0, 0.54 } 
		});
	testNet.setRealMatrixOutputSet(std::vector<std::vector<double>>()= { 
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 1.0, 0.0 },
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 0.0, 1.0 },
		{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 }
		});
	testNet.setMaxEpochs(1000);
	testNet.setTargetError(0.002);
	testNet.setLearningRate(0.1);
	testNet.setTrainType(TrainingTypesENUM::BACKPROPAGATION);
	testNet.setActivationFnc(ActivationFncENUM::SIGLOG);
	testNet.setActivationFncOutputLayer(ActivationFncENUM::LINEAR);

	trainedNet = testNet.trainNet(testNet);
	std::cout << std::endl;
	std::cout << "-------------BACKPROPAGATION TRAINED NET----------------" << std::endl;
	testNet.printNet(trainedNet);
}
