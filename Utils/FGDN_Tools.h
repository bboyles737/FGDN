#ifndef FGDN_TOOLS_H
#define FGDN_TOOLS_H

#include <string>
#include <vector>

const double PI = 3.14159265358979323846;

std::vector<std::string> split(const std::string& s, char delimiter);

int capAmount(int amt, int minVal, int maxVal);

double yds_to_m(double yds);
double m_to_yds(double m);
double ms_to_kts(double ms);
double kts_to_ms(double kts);
double deg_to_rad(double degrees);
double rad_to_deg(double radians);

double normDegrees(double degrees);


#endif // FGDN_TOOLS_H
