#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLine.h"
//#include "TTree.h"
#include <TCanvas.h>
#include "TMultiGraph.h"
#include <iostream>
#include <fstream>
#include <numeric>
#include <dirent.h>
#include <sys/types.h>
#include "singlePulse.h"


#include <sstream>
#include <locale>
#include <iomanip>


using namespace std;

#define pathToFiles "/home/dannezlomnyj/Dropbox/Bakalarka/MeasuredData/SourceCalibration/"








vector<string> getFiles(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   vector<string>  fileNames;

   if (dir == NULL) {
      return fileNames;
   }
   while ((entry = readdir(dir)) != NULL) {
    if ( !strcmp( entry->d_name, "."  )) continue;
    if ( !strcmp( entry->d_name, ".." )) continue;
    if ( !(strstr( entry->d_name, ".csv" ))) continue;
    fileNames.push_back(entry->d_name);
    sort( fileNames.begin(), fileNames.end() );

   }
   closedir(dir);

   return fileNames;
}

int main(int argc, char *argv[]) {

  vector<string>  fileNames;
  //vector<double> Unix_dates;
  vector<double> timestamps;
  vector<double>  heights;
  vector<double>  heights_errors;
  vector<double>  rise_times;
  vector<double>  slopes;
  vector<double>  slopes_errors;
  vector<double> drop_times;
  vector<Pulse>  pulses;
  vector<double>  Source_voltages;
  vector<double>  PMT_temperature;
  vector<double>  Power;

fileNames = getFiles(pathToFiles);
cout << "start"<< endl;
time_t first_Time;
bool set = false;
//cout << fileNames.size()<< endl;
for(auto& name : fileNames){
  std::cout << name << '\n';
  if(name.find("osci_") == 0){
  string name_2 = name;
  name_2.erase (name_2.end()-4, name_2.end()); //erase .csv
  name_2.erase (name_2.begin(), name_2.begin() + 5); //erase osci_
  //std::cout << name_2 << '\n';
  std::tm t = {};
  std::istringstream ss(name_2);
  ss >> std::get_time(&t, "%Y%m%d_%H%M");
  time_t timestamp = timegm(&t);
  if(!set){
    first_Time = timestamp;
    set = true;
  }
  //std::cout << (Float_t)(timestamp) << '\n';
  pulses.emplace_back(pathToFiles+name);
  timestamps.push_back(difftime(timestamp,first_Time));
}



}

for(auto& tms : timestamps){

  std::cout << tms << '\n';
}


for(auto& a : pulses){
  std::cout << a.rise_time << '\n';
  rise_times.push_back(a.rise_time);
  std::cout << a.height << '\n';
  heights.push_back((double)(a.height - a.lowLevel));
  std::cout << a.height_error << '\n';
  heights_errors.push_back((double)(a.height_error + a.lowLevel_error));
  std::cout << a.slope << '\n';
  slopes.push_back(a.slope);
  std::cout << a.slope_error << '\n';
  slopes_errors.push_back(a.slope_error);
  std::cout << a.drop_time << '\n';
  drop_times.push_back(a.drop_time);

}
/*for(auto& a : pulses){
  std::cout << a.height << '\n';


}

for(auto& a : pulses){
  std::cout << a.slope << '\n';


}*/

auto c1 = new TCanvas("c1","Height of pulses",200,10,700,500);

auto hg = new TGraphErrors((Int_t)heights.size(),timestamps.data(),heights.data(),0,heights_errors.data());
hg->SetTitle("Heights");
hg->SetMarkerColor(4);
hg->SetMarkerStyle(21);
hg->Draw("A*");

c1->SaveAs("Height.png");

auto sg = new TGraphErrors((Int_t)slopes.size(),timestamps.data(),slopes.data(),0,slopes_errors.data());

sg->SetTitle("slopes");
sg->SetMarkerColor(4);
sg->SetMarkerStyle(21);
sg->Draw("A*");
c1->SaveAs("Slope.png");

auto rg = new TGraphErrors((Int_t)rise_times.size(),timestamps.data(),rise_times.data(),0,0);

rg->SetTitle("rise times");
rg->SetMarkerColor(4);
rg->SetMarkerStyle(21);
rg->Draw("A*");
c1->SaveAs("rise.png");

auto dg = new TGraphErrors((Int_t)drop_times.size(),timestamps.data(),drop_times.data(),0,0);

dg->SetTitle("drop times");
dg->SetMarkerColor(4);
dg->SetMarkerStyle(21);
dg->Draw("A*");
c1->SaveAs("drop.png");
/*Pulse MyPulses("/home/dannezlomnyj/Documents/Programming/CalibrationSources/ReadCP/linux-build-files/data/1625162405.txt");
cout << "here it comes:"<<MyPulses.height << endl;
cout << "here it comes:"<<MyPulses.height_error << endl;
cout << "here it comes:"<<MyPulses.lowLevel << endl;
cout << "here it comes:"<<MyPulses.lowLevel_error << endl;
cout << "here it comes:"<<MyPulses.rise_time << endl;
cout << "here it comes:"<<MyPulses.rise_time_error << endl;
cout << "here it comes:"<<MyPulses.slope << endl;
cout << "here it comes:"<<MyPulses.slope_error << endl;
cout << "here it comes:"<<MyPulses.drop_time << endl;
cout << "here it comes:"<<MyPulses.drop_time_error << endl;
return 0;*/
}
