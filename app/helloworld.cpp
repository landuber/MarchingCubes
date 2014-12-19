#include "sample.hpp"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <glog/logging.h>
#include <iostream>
#include <pcl/io/ply_io.h>
#include <memory>
namespace fs = boost::filesystem;

using namespace sample;


int main(int argc, char** argv) {
  ProgressiveSamplingWindow window(10);
  window.print();
}
