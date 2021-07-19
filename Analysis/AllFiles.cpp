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
#include <dirent.h>
#include <sys/types.h>

using namespace std;

#define pathToFiles "/home/dannezlomnyj/Documents/Programming/CalibrationSources/ReadCP/linux-build-files/data/"





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
    if ( !(strstr( entry->d_name, ".txt" ))) continue;
    fileNames.push_back(entry->d_name);

   }
   closedir(dir);

   return fileNames;
}

int main(int argc, char *argv[]) {

  vector<string>  fileNames;
  vector<Float_t> Unix_dates;
  vector<Float_t>  heights;
  vector<Float_t>  rise_times;
  vector<Float_t>  drop_times;

fileNames = getFiles(pathToFiles);

for(auto& name : fileNames){

  std::cout << name << '\n';

}
return 0;
}
