#ifndef MYDEFS
#define MYDEFS
#define M_PI           3.14159265358979323846  /* pi */
//const int wndWidth = 1280;
//const int wndHeight = 720;
//const float ratio_w = 16.0;
//const float ratio_h = 9.0;
const int det_width = 960;
const int det_height = 540;
const int vnect_resize_width = 560;
const int vnect_resize_height = 315;
const float base_vof = 45.0;
const int one_euro_filter_frequency = 2;
// In the Demo, the author give the range of the 3D location, I normalized
// it according it
const int vnect_3d_range[] = {-700, 700, -800, 800, -700, 700};

const int mappingToVnect[] = { 1,16,14,5,6,7,11,12,13,2,3,4,8,9,10 };
const int mappingFromVnect[] = {-1,0,9,10,11,3,4,5,12,13,14,6,7,8,2,-1,1};
#endif
