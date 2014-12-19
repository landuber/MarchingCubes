#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <cstddef>
#include <cstring>
#include <vector>

namespace sample {

  class ProgressiveSamplingWindow {

  public:
    ProgressiveSamplingWindow(size_t radius);
    size_t get_radius () const;
    void print() const;
  private:
    size_t radius;
  };
}
