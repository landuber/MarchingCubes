#include <cmath>
#include <iostream>

#include <boost/filesystem.hpp>
#include <glog/logging.h>
#include <pcl/io/ply_io.h>
#include <opencv2/photo/photo.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "sample.hpp"

using namespace std;
using namespace cv;
namespace fs = boost:: filesystem;


namespace sample {

      ProgressiveSamplingWindow::ProgressiveSamplingWindow(size_t radius) {
        this->radius = radius;
      }

      size_t ProgressiveSamplingWindow::get_radius () const {
        return this->radius;
      }

      void ProgressiveSamplingWindow::print() const {
        cout << this->radius;
      }
}
