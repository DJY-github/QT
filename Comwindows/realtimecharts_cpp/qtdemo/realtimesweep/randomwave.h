///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RANDOMWAVE_HDR
#define RANDOMWAVE_HDR

#include <QThread>

//
// A Random series generator using the random walk method
//
class RandomWave : public QThread
{
Q_OBJECT
public:

    typedef void DataHandler(void *param, double elapsedTime, double series0, double series1);

    RandomWave(DataHandler *handler, void *param);
    virtual ~RandomWave();

    // stop the thread
    void stop();

protected :
    // The thread of the random series generator
    void run();

private :

    // Disable copying and assignment
    RandomWave & operator=(const RandomWave&);
    RandomWave(const RandomWave&);

    // Flag to stop the flag
    bool stopThread;

    // The callback function to handle the generated data
	DataHandler *handler;
	void *param;
};

#endif

