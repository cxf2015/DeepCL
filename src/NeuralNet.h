// Copyright Hugh Perkins 2014 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <vector>

#include "Layer.h"
#include "NeuralNetMould.h"
#include "EpochMaker.h"
#include "ConvolutionalLayer.h"
#include "InputLayer.h"
//#include "FullyConnectedLayer.h"

class OpenCLHelper;
//class FullyConnectedMaker;
class ConvolutionalMaker;
class LayerMaker;

#define VIRTUAL virtual
#define STATIC static

class NeuralNet {
public:
    std::vector< Layer *> layers;
    OpenCLHelper *cl;

    // [[[cog
    // import cog_addheaders
    // cog_addheaders.add()
    // ]]]
    // classname: NeuralNet
    // cppfile: NeuralNet.cpp

    NeuralNet( int numPlanes, int boardSize );
    ~NeuralNet();
    OpenCLHelper *getCl();
    STATIC NeuralNetMould *maker();
    ConvolutionalMaker *convolutionalMaker();
    SquareLossMaker *squareLossMaker();
    CrossEntropyLossMaker *crossEntropyLossMaker();
    SoftMaxMaker *softMaxLossMaker();
    void initWeights( int layerIndex, float *weights, float *biasWeights );
    void initWeights( int layerIndex, float *weights );
    void initBiasWeights( int layerIndex, float *weights );
    void printWeightsAsCode();
    void printBiasWeightsAsCode();
    float calcLoss(float const *expectedValues );
    EpochMaker *epochMaker();
    InputLayer *getFirstLayer();
    Layer *getLastLayer();
    Layer *addLayer( LayerMaker *maker );
    void setBatchSize( int batchSize );
    float doEpoch( float learningRate, int batchSize, int numImages, float const* images, float const *expectedResults );
    float doEpochWithCalcTrainingAccuracy( float learningRate, int batchSize, int numImages, float const* images, float const *expectedResults, int const *labels, int *p_totalCorrect );
    void propagate( float const*images);
    void backProp( float learningRate, float const *expectedResults);
    void learnBatch( float learningRate, float const*images, float const *expectedResults );
    int getNumLayers();
    float const *getResults( int layer ) const;
    int getInputCubeSize() const;
    int getOutputCubeSize() const;
    float const *getResults() const;
    void print();
    void printWeights();
    void printOutput();

    // [[[end]]]
};
