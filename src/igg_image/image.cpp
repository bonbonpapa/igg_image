#include <iostream>
#include "image.h"
#include "io_tools.h"
using std::cout;
using std::endl;

igg::Image::Image() {}
igg::Image::Image(int rows, int cols) : rows_{rows}, cols_{cols} {}
int igg::Image::rows() const
{
  return rows_;
}
int igg::Image::cols() const
{
  return cols_;
}
const int &igg::Image::at(int row, int col)
{
  return data_.at(cols_ * row + col);
}
bool igg::Image::FillFromPgm(const std::string &file_name)
{
  const igg::io_tools::ImageData imgdata = igg::io_tools::ReadFromPgm(file_name);
  rows_ = imgdata.rows;
  cols_ = imgdata.cols;
  data_ = imgdata.data;

  return true;
}

void igg::Image::WriteToPgm(const std::string &file_name)
{
  const igg::io_tools::ImageData img = {rows_, cols_, 255, data_};

  igg::io_tools::WriteToPgm(img, file_name);
}

std::vector<float> igg::Image::ComputeHistogram(int bins) const
{
  std::vector<float> histogram;
  histogram.reserve(bins);
  for (int i = 0; i < bins; ++i)
  {
    histogram.push_back(0);
  }

  for (auto px : data_)
  {
    int bin = (bins * px) / 255;
    histogram.at(bin) += 1;
  }

  return histogram;
}

void igg::Image::UpScale(int scale, const std::string &file_name)
{
  int s_cols = cols_ * scale;
  int s_rows = rows_ * scale;
  std::cout << s_cols << "  " << s_rows << std::endl;

  igg::io_tools::ImageData img;
  img.cols = s_cols;
  img.rows = s_rows;
  img.max_val = 255;

  for (int i = 0; i < s_rows; i++)
  {
    for (int j = 0; j < s_cols; j++)
    {
      img.data.push_back(this->at(i/scale, j/scale));
    }
  }

  igg::io_tools::WriteToPgm(img, file_name);
}

void igg::Image::DownScale(int scale, const std::string &file_name)
{
  int s_cols = cols_ / scale;
  int s_rows = rows_ / scale;

  std::cout << s_cols << "  " << s_rows << std::endl;

  igg::io_tools::ImageData img;
  img.cols = s_cols;
  img.rows = s_rows;
  img.max_val = 255;
  img.data.reserve(img.cols * img.rows);

  for (int i = 0; i < s_rows; i++)
  {
    for (int j = 0; j < s_cols; j++)
    {
      img.data.push_back(this->at(i * scale, j * scale));
    }
  }

  igg::io_tools::WriteToPgm(img, file_name);
}