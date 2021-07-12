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


#define no_deriv 3








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

  const Float_t Down_bound = 0.2* Vmaximum;
  const Float_t Up_bound = 0.9 * Vmaximum;

  cout << "down bound:" <<Down_bound << endl;
  cout << "up bound:" <<Up_bound << endl;

  vector<vector<Float_t>> rising_times; //= new vector<int>;
  vector<vector<Float_t>>  rising_voltages;//= new vector<double>;
  vector<vector<Float_t>> falling_times; //= new vector<int>;
  vector<vector<Float_t>>  falling__voltages;//= new vector<double>;

  vector<Float_t> temp_times;
  vector<Float_t> temp_voltages;


  Int_t d_no_pos, d_no_neg;
  Float_t actual_voltage, actual_voltage_2, old_voltage = 0;
  Int_t no_rises = 0;
  for (size_t i = 0; i < times.size() -6; i++)  { //only to 6 before end
    actual_voltage = voltages.at(i);
    if(actual_voltage > Down_bound && actual_voltage < Up_bound){


                      //check for positive derivative
      d_no_pos = 0;
      //old_voltage = 0;
      if (actual_voltage < (0.5 *Vmaximum)) {


        actual_voltage_2 = actual_voltage;
        old_voltage = actual_voltage_2;
        while((actual_voltage_2 - old_voltage) >= 0){
          if (!(actual_voltage_2 > Down_bound && actual_voltage_2 < Up_bound)){
            d_no_pos = 0;
            break;
          }
          old_voltage = actual_voltage_2;
          d_no_pos++;
          actual_voltage_2 = voltages.at(i+d_no_pos);
          if(d_no_pos > no_deriv){
            break;

          }
        }
      }
      //old_voltage = 0;
              //check for negative derivative
      d_no_neg = 0;
      if (actual_voltage > (0.5 *Vmaximum)) {
      actual_voltage_2 = actual_voltage;
      old_voltage = actual_voltage_2;
      while((actual_voltage_2 - old_voltage) <= 0){
        if (!(actual_voltage_2 > Down_bound && actual_voltage_2 < Up_bound)){
          d_no_neg = 0;
          break;
        }
        old_voltage = actual_voltage_2;
        d_no_neg++;
        actual_voltage_2 = voltages.at(i+d_no_neg);
        if(d_no_neg > no_deriv){
          break;

        }
      }
    }
      Int_t j = 0;
      if(d_no_pos > no_deriv){

        cout << "new positive series" << endl;

        temp_times.clear();
        temp_voltages.clear();
        //actual_voltage_2 = 0;
        actual_voltage_2 = voltages.at(i);
        while(actual_voltage_2 < Up_bound){

          temp_voltages.push_back(actual_voltage_2);
          temp_times.push_back(times.at(i+j));
          cout << actual_voltage_2 << endl;

          j++;
          actual_voltage_2 = voltages.at(i+j);
        }
        rising_times.push_back(temp_times);
        rising_voltages.push_back(temp_voltages);

      }


      else if(d_no_neg > no_deriv){

        cout << "new negative series" << endl;

        temp_times.clear();
        temp_voltages.clear();
        //actual_voltage_2 = 0;*******
        actual_voltage_2 = voltages.at(i);


        while(actual_voltage_2 > Down_bound){

        temp_voltages.push_back(actual_voltage_2);
        temp_times.push_back(times.at(i+j));
        cout << actual_voltage_2 << endl;


        j++;
        actual_voltage_2 = voltages.at(i+j);
        }
        falling_times.push_back(temp_times);
        falling__voltages.push_back(temp_voltages);


      }

      /*if((actual_voltage - old_voltage) > 0 && no_rises < 3){
      no_rises++;
      rising_times.push_back(times.at(i));
      rising_voltages.push_back(actual_voltage);
      }
      else if(no_rises < 3){
      no_rises = 0;

      }
      else if(no_rises >= 3){



      }*/
      i += j;
  }
  }

  for (auto& itRow : rising_voltages)
    {
        std::cout << "cells = ";

        for (auto& itCell : itRow)
        {
            std::cout << itCell << " ";
        }
        std::cout << std::endl;
    }

	c1->SaveAs("PWM.png");

	delete c1;
	return 0;
}
