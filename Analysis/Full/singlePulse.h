// singlePulse.h
//#include <TCanvas.h>
//#include <iostream>
using namespace std;

    class Pulse
    {
    public:
        Pulse(string fl);
        void SetConditions(string fl);
        //TCanvas *canvas_1;
        //TCanvas *canvas_2;
        //TCanvas *canvas_3;
        Float_t height;
        Float_t height_error;
        Float_t lowLevel;
        Float_t lowLevel_error;
        Float_t rise_time;
        Float_t rise_time_error;
        Float_t drop_time;
        Float_t drop_time_error;
        Float_t slope;
        Float_t slope_error;


        double power;
        double power_error;
        double PMT_temperature;
        double PMT_temperature_error;
        double Source_voltage;
        double Source_voltage_error;


    };
