#include "FGDN_Tools.h"

double yds_to_m(double yds)   { return yds * 0.9144;  }
double m_to_yds(double m)     { return m * 1.09361;   }
double ms_to_kts(double ms)   { return ms * 1.94384;  }
double kts_to_ms(double kts)  { return kts * 0.514444;}
double deg_to_rad(double degrees) { return degrees * 0.01745; }
double rad_to_deg(double radians) { return radians * 57.2958; }


double normDegrees(double degrees) {
    while (degrees < 0.0) degrees += 360.0;
    while (degrees > 360.0) degrees -= 360.0;
    return degrees;
}
