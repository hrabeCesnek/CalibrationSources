#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLine.h"
//#include "TTree.h"
#include <TCanvas.h>

#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;

int main(int argc, char *argv[]) {
  TCanvas *c1 = new TCanvas("c1","test", 600,600);
  //FILE *fp = fopen("/home/dannezlomnyj/Documents/Programming/CalibrationSources/ReadCP/linux-build-files/data/1625173205.txt","r");
  ifstream f("/home/dannezlomnyj/Documents/Programming/CalibrationSources/ReadCP/linux-build-files/data/1625173205.txt");

string str;
//Int_t n = 0;
Float_t time;
Float_t voltage;
std::vector<Float_t> times; //= new vector<int>;
std::vector<Float_t>  voltages;//= new vector<double>;
while (getline(f,str))
{
  sscanf(str.c_str(),"%f %f",&time,&voltage);
  std::cout << voltage << '\n';
  times.push_back(time);
  voltages.push_back((-1)*voltage); //invert back
}

Float_t average_voltage = accumulate( voltages.begin(), voltages.end(), 0.0)/voltages.size();




TH1F *voltageHistogram_1 = new TH1F("voltHist","voltHist",1000,0,average_voltage);


    for(int j = 0; j < voltages.size(); j++) //traca
		{

    voltageHistogram_1->Fill(voltages.at(j));
    }
    voltageHistogram_1->Fit("gaus");

    Float_t Vminimum = voltageHistogram_1->GetFunction("gaus")->GetParameter(1);

    TH1F *voltageHistogram_2 = new TH1F("voltHist","voltHist",1000,average_voltage,*max_element(voltages.begin(), voltages.end()));

        for(int j = 0; j < voltages.size(); j++) //traca
    		{

        voltageHistogram_2->Fill(voltages.at(j));
        }
        voltageHistogram_2->Fit("gaus");

    Float_t Vmaximum = voltageHistogram_2->GetFunction("gaus")->GetParameter(1);

TGraph* gr = new TGraph((Int_t)(times.size()),(times.data()),(voltages.data()));
    //voltageHistogram_1->Draw("AC*");
  gr->Draw("AC*");

  TLine *line = new TLine(0,average_voltage,40000,average_voltage);
    line->SetLineColor(kRed);
    line->Draw();

  TLine *lineMin = new TLine(0,Vminimum,40000,Vminimum);
    lineMin->SetLineColor(kRed);
    lineMin->Draw();

  TLine *lineMax = new TLine(0,Vmaximum,40000,Vmaximum);
    lineMax->SetLineColor(kRed);
    lineMax->Draw();

	c1->SaveAs("PWM.png");

	delete c1;
	return 0;
}
