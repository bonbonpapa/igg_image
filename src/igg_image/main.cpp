#include <iostream>
#include "image.h"
using std::cout;
using std::endl;

int main() {
    std::string file_name = "../data/lena.ascii.pgm";
    std::string new_file = "../data/new.ascii.pgm";
    std::string scaled_file = "../data/scaled.ascii.pgm";
    std::string scaleu_file = "../data/scaleu.ascii.pgm";
    std::vector<float> histogram;
    int total_px = 0;
    igg::Image image(512, 512);
    image.FillFromPgm(file_name);
    image.WriteToPgm(new_file);
    histogram = image.ComputeHistogram(255);

    for(auto && x: histogram)
    {
        cout << x << endl;
        total_px += x;

    }
    cout << "Totoal pixel of the image: " << total_px << endl;

    image.DownScale(2, scaled_file); 
    image.UpScale(2, scaleu_file);
    
    return 0;
}