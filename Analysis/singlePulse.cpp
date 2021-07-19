#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLine.h"
//#include "TTree.h"
#include <TCanvas.h>
#include "TMultiGraph.h"
#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;


#define no_deriv 2


class Pulse {
public:
    Pulse(string file)
        {
          //program for pulse analysis
          
        }

    Float_t getSize() const
        { return vec.size(); }

    // ... more things...
private:
    Float_t height;
    Float_t lowLevel;
    Float_t rise_time;
    Float_t drop_time;
    Float_t slope;
}
